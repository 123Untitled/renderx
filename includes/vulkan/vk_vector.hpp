/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VK_VECTOR_HEADER
#define ENGINE_VK_VECTOR_HEADER

#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vk_exception.hpp"
#include "vulkan/vk_create.hpp"
#include "vulkan/vk_destroy.hpp"
#include "vulkan/vk_shared.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- V E C T O R ---------------------------------------------------------

	template <typename T>
	class vvector final {


		// -- assertions ------------------------------------------------------

		/* check if T is a opaque handle */
		static_assert(sizeof(T) == sizeof(void*), "T must be an opaque handle");

		/* check if T is trivially copyable */
		static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = vk::vvector<T>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* constant reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* constant pointer type */
			using const_ptr  = const value_type*;

			/* size type */
			using size_type  = vk::u32;

			/* dependency type */
			using dep_type   = xns::conditional<vk::is_destroyable<T, vk::instance>, vk::instance,
							   xns::conditional<vk::is_destroyable<T, vk::device>, vk::device, void>>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			vvector(void) = delete;

			/* dependency constructor */
			vvector(const vk::shared<dep_type>& dependency)
			: _data{nullptr}, _size{0U}, _capacity{0U}, _dependency{dependency} {
			}

			/* deleted copy constructor */
			vvector(const self&) = delete;

			/* move constructor */
			vvector(self&& other) noexcept
			: _data{other._data}, _size{other._size}, _capacity{other._capacity},
			  _dependency{std::move(other._dependency)} {
				// invalidate other
				other.__init();
			}

			/* destructor */
			~vvector(void) noexcept {

				// destroy objects
				__clear();

				// deallocate memory
				self::__deallocate(_data);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy objects
				__clear();

				// deallocate memory
				self::__deallocate(_data);

				// move data
				_data       = other._data;
				_size       = other._size;
				_capacity   = other._capacity;
				_dependency = std::move(other._dependency);

				// invalidate other
				other.__init();

				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* data */
			auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* data */
			auto data(void) const noexcept -> const_ptr {
				return _data;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type index) noexcept -> mut_ref {
				return _data[index];
			}

			/* const subscript operator */
			auto operator[](const size_type index) const noexcept -> const_ref {
				return _data[index];
			}


			// -- public modifiers --------------------------------------------

			/* emplace back */
			template <typename... __params>
			auto emplace_back(__params&&... params) -> void {
				// check if capacity is reached
				if (__available() == 0U)
					// expand capacity
					__reserve(__expand());

				// construct object
				_data[_size] = vk::create(_dependency, std::forward<__params>(params)...);

				// increment size
				++_size;
			}

			/* clear */
			auto clear(void) noexcept -> void {
				// destroy objects
				__clear();
				// reset size
				_size = 0U;
			}

			/* reserve */
			auto reserve(const size_type size) -> void {
				// check if capacity is sufficient
				if (size <= _capacity)
					return;
				// call reserve implementation
				__reserve(size);
			}


		private:

			// -- private static methods --------------------------------------

			/* allocate */
			inline static auto __allocate(const size_type size) -> mut_ptr {
				// allocate memory
				return static_cast<mut_ptr>(__builtin_malloc(size * sizeof(value_type)));
			}

			/* deallocate */
			inline static auto __deallocate(mut_ptr ptr) -> void {
				// check if pointer is null
				if (ptr == nullptr)
					return;
				// deallocate memory
				__builtin_free(ptr);
			}


			// -- private methods ---------------------------------------------

			/* init */
			inline auto __init(void) noexcept {
				_data     = nullptr;
				_size     = 0U;
				_capacity = 0U;
			}

			/* available */
			inline auto __available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* clear */
			inline auto __clear(void) const noexcept -> void {

				// loop over objects
				for (size_type i = 0U; i < _size; ++i)
					vk::destroy(_dependency, _data[i]);
			}

			/* reserve */
			auto __reserve(const size_type capacity) -> void {

				// allocate new memory
				mut_ptr data = self::__allocate(capacity);

				// check if allocation failed
				if (data == nullptr)
					throw vk::exception("failed to allocate memory for vector");

				// copy objects
				__builtin_memcpy(data, _data, _size * sizeof(value_type));

				// deallocate old memory
				self::__deallocate(_data);

				// update data
				_data     = data;
				_capacity = capacity;
			}

			/* expand */
			inline auto __expand(void) const noexcept -> size_type {
				return _capacity == 0U ? 1U : _capacity * 2U;
			}



			// -- private members ---------------------------------------------

			/* data */
			mut_ptr _data;

			/* size */
			size_type _size;

			/* capacity */
			size_type _capacity;

			/* dependency */
			vk::shared<dep_type> _dependency;

	}; // class vector

} // namespace vk

#endif // ENGINE_VK_VECTOR_HEADER
