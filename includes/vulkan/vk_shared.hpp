#pragma once

#ifndef ENGINE_VULKAN_SHARED_HEADER
#define ENGINE_VULKAN_SHARED_HEADER

#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vk_utils.hpp"
#include "vulkan/vk_destroy.hpp"
#include "vulkan/vk_create.hpp"
#include "exceptions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	// -- S H A R E D ---------------------------------------------------------

	/* forward declaration */
	template <typename T>
	class shared;


	/* shared specialization */
	template <typename T> requires vk::is_destroyable<T>
	class shared<T> {


		// -- friends ---------------------------------------------------------

		/* shared as friend */
		template <typename __type>
		friend class vk::shared;

		/* make shared as friend */
		template <typename... __params>
		friend auto make_shared(__params&&...) -> vk::shared<vk::create_return<__params...>>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::shared<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline shared(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr} {
			}

			/* copy constructor */
			inline shared(const self& other) noexcept
			: _value{other._value}, _count{other._count} {
				if (_value == VK_NULL_HANDLE)
					return;
				++(*_count);
			}

			/* move constructor */
			inline shared(self&& other) noexcept
			: _value{other._value}, _count{other._count} {
				_value = VK_NULL_HANDLE;
				_count = nullptr;
			}

			/* destructor */
			~shared(void) noexcept {
				this->free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// clean up
				this->free();

				// copy value and count
				_value = other._value;
				_count = other._count;

				if (_value == VK_NULL_HANDLE)
					return *this;
				++(*_count);

				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// clean up
				this->free();

				// move value and count
				_value = other._value;
				_count = other._count;

				other._value = VK_NULL_HANDLE;
				other._count = nullptr;

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			inline operator const value_type&(void) const noexcept {
				return _value;
			}


			// -- public accessors --------------------------------------------

			/* count */
			inline auto count(void) const noexcept -> vk::u32 {
				return _count != nullptr ? *_count : 0;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* value and count constructor */
			inline shared(const value_type& value, vk::u32* count) noexcept
			: _value{value}, _count{count} {
			}


			// -- private methods ---------------------------------------------

			/* free */
			inline auto free(void) noexcept -> void {
				if (_value == VK_NULL_HANDLE)
					return;
				if (--(*_count) > 0)
					return;
				vk::destroy(_value);
				__builtin_free(_count);
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* reference count */
			vk::u32* _count;

	}; // class shared


	template <typename... __params>
	auto make_shared(__params&&... args) -> vk::shared<vk::create_return<__params...>> {

		auto value = vk::create(xns::forward<__params>(args)...);

		vk::u32* count = (vk::u32*)__builtin_malloc(sizeof(vk::u32));

		if (count == nullptr) {
			vk::destroy(value);
			throw engine::exception("failed to allocate memory");
		}

		*count = 1;

		return {value, count};
	}



	/* dual specialization */
	template <typename T>
	concept dual_managed = xns::is_one_of<T, vk::swapchain,
											 vk::pipeline,
											 vk::pipeline_layout,
											 vk::surface,
											 vk::render_pass,
											 vk::command_pool,
											 vk::debug_utils_messenger,
											 vk::semaphore,
											 vk::shader_module,
											 vk::framebuffer>;

	/* shared specialization */
	template <typename T> requires (vk::is_destroyable<vk::instance, T>
								 || vk::is_destroyable<vk::device,   T>)
	class shared<T> {


		// -- friends ---------------------------------------------------------

		/* shared as friend */
		template <typename __type>
		friend class vk::shared;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::shared<T>;

			/* value type */
			using value_type = T;

			/* dependency type */
			using dep_type = xns::conditional<vk::is_destroyable<T, vk::instance>,
												vk::instance,
												vk::device>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline shared(void) noexcept
			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependency{} {
			}

			/* members constructor */
			template <typename... __params>
			inline shared(const vk::shared<dep_type>& dependency, __params&&... args) requires (sizeof...(args) > 0)
			: _value{VK_NULL_HANDLE}, _count{nullptr}, _dependency{dependency} {

				if (dependency._value == VK_NULL_HANDLE)
					throw engine::exception("dependency has been destroyed");

				_value = vk::create(xns::forward<__params>(args)..., dependency);
				_count = (vk::u32*)__builtin_malloc(sizeof(vk::u32));

				if (_count == nullptr) {
					vk::destroy(_value, _dependency);
					throw engine::exception("failed to allocate memory");
				}

				// initialize count
				*_count = 1;
			}

			/* surface constructor NEED TO BE FIXED ! */
			inline shared(const value_type& value, const vk::shared<dep_type>& dependency)
			: _value{value}, _count{(vk::u32*)__builtin_malloc(sizeof(vk::u32))}, _dependency{dependency} {

				if (_count == nullptr) {
					vk::destroy(_value, _dependency);
					throw engine::exception("failed to allocate memory");
				}

				// initialize count
				*_count = 1;

			}

			/* copy constructor */
			inline shared(const self& other) noexcept
			: _value{other._value}, _count{other._count}, _dependency{other._dependency} {

				if (_value == VK_NULL_HANDLE)
					return;

				// increment count
				++(*_count);
			}

			/* move constructor */
			inline shared(self&& other) noexcept
			: _value{other._value}, _count{other._count}, _dependency{xns::move(other._dependency)} {

				// invalidate other
				other.__init();
			}

			/* destructor */
			~shared(void) noexcept {
				this->__free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// clean up
				this->__free();

				// copy members
				this->__copy(other);

				if (_value == VK_NULL_HANDLE)
					return *this;

				// increment count
				++(*_count);

				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// clean up
				this->__free();
				// move members
				this->__move(xns::move(other));
				// invalidate other
				other.__init();

				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* value conversion operator */
			inline operator const value_type&(void) const noexcept {
				return _value;
			}

			/* dependency conversion operator */
			inline operator const dep_type&(void) const noexcept {
				return _dependency;
			}


			// -- public accessors --------------------------------------------

			/* count */
			inline auto count(void) const noexcept -> vk::u32 {
				return _count != nullptr ? *_count : 0;
			}

			/* dependency */
			inline auto dependency(void) const noexcept -> const dep_type& {
				return _dependency;
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			inline auto __init(void) noexcept -> void {

				_value = VK_NULL_HANDLE;
				_count = nullptr;
			}

			/* copy */
			inline auto __copy(const self& other) noexcept -> void {

				_value              = other._value;
				_count              = other._count;
				_dependency.operator=(other._dependency);
			}

			/* move */
			inline auto __move(self&& other) noexcept -> void {

				_value              = other._value;
				_count              = other._count;
				_dependency.operator=(xns::move(other._dependency));
			}


			/* free */
			inline auto __free(void) noexcept -> void {

				if (_value == VK_NULL_HANDLE)
					return;

				// check for last value reference
				if (--(*_count) == 0) {
					// destroy value
					vk::destroy(_value, _dependency);
					__builtin_free(_count);
				}
			}


			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* count */
			vk::u32* _count;

			/* dependency */
			vk::shared<dep_type> _dependency;

	}; // class shared


} // namespace vk

#endif // ENGINE_VULKAN_SHARED_HEADER
