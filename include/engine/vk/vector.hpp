/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VK_VECTOR___
#define ___ENGINE_VK_VECTOR___

//#include "engine/vk/typedefs.hpp"
//#include "engine/vk/exception.hpp"

#include "engine/vk/create.hpp"
#include "engine/vk/destroy.hpp"

//#include "engine/vk/shared.hpp"
//#include "engine/vk/dependency_type.hpp"

#include "engine/vulkan/device.hpp"

#include "renderx/memory/memcpy.hpp"
#include "renderx/memory/malloc.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- V E C T O R ---------------------------------------------------------

	template <typename ___type>
	class vvector final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::vvector<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = ___type;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer         = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = vk::u32;


		private:

			// -- private members ---------------------------------------------

			/* data */
			pointer _data;

			/* size */
			size_type _size;

			/* capacity */
			size_type _capacity;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			vvector(void) noexcept
			: _data{nullptr}, _size{0U}, _capacity{0U} {
			}

			/* deleted copy constructor */
			vvector(const ___self&) = delete;

			/* move constructor */
			vvector(___self&& ___ot) noexcept
			: _data{___ot._data}, _size{___ot._size}, _capacity{___ot._capacity} {

				// invalidate other
				___ot._init();
			}

			/* destructor */
			~vvector(void) noexcept {

				// destroy objects
				___self::_clear();

				// deallocate memory
				___self::_deallocate();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self& {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy objects
				___self::_clear();

				// deallocate memory
				___self::_deallocate();

				// move data
				_data       = other._data;
				_size       = other._size;
				_capacity   = other._capacity;

				// invalidate other
				other._init();

				return *this;
			}


			// -- public accessors --------------------------------------------

			/* empty */
			auto empty(void) const noexcept -> bool {
				return _size == 0U;
			}

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* data */
			auto data(void) noexcept -> pointer {
				return _data;
			}

			/* data */
			auto data(void) const noexcept -> const_pointer {
				return _data;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type index) noexcept -> reference {
				return _data[index];
			}

			/* const subscript operator */
			auto operator[](const size_type index) const noexcept -> const_reference {
				return _data[index];
			}


			// -- public modifiers --------------------------------------------

			/* emplace back */
			template <typename... __params>
			auto emplace_back(__params&&... params) -> void {

				// check if capacity is reached
				if (___self::_available() == 0U)

					// expand capacity
					___self::_reserve(___self::_expand());

				// construct object
				_data[_size] = vk::create(vulkan::device::logical(),
										  std::forward<__params>(params)...);

				// increment size
				++_size;
			}

			/* clear */
			auto clear(void) noexcept -> void {

				// destroy objects
				___self::_clear();

				// reset size
				_size = 0U;
			}

			/* reserve */
			auto reserve(const size_type size) -> void {

				// check if capacity is sufficient
				if (size <= _capacity)
					return;

				// call reserve implementation
				___self::_reserve(size);
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto _init(void) noexcept {
				_data     = nullptr;
				_size     = 0U;
				_capacity = 0U;
			}

			/* available */
			auto _available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* clear */
			auto _clear(void) const noexcept -> void {

				// get end pointer
				pointer end = _data + _size;

				// loop over objects
				for (pointer it = _data; it != end; ++it)
					vk::destroy(vulkan::device::logical(), *it);
			}

			/* reserve */
			auto _reserve(const size_type ___cap) -> void {

				// allocate new memory
				pointer ___ndata = rx::realloc<value_type>(_data, ___cap);

				// update data
				_data     = ___ndata;
				_capacity = ___cap;
			}

			/* deallocate */
			auto _deallocate(void) noexcept -> void {

				// check if pointer is null
				if (_data == nullptr)
					return;

				// deallocate memory
				rx::free(_data);
			}

			/* expand */
			auto _expand(void) const noexcept -> size_type {
				return _capacity == 0U ? 1U : _capacity * 2U;
			}

	}; // class vector

} // namespace vk

#endif // ___ENGINE_VK_VECTOR___
