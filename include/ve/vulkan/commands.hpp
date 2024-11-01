#ifndef ___ve_vulkan_commands___
#define ___ve_vulkan_commands___

#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vk/exception.hpp"
#include "ve/vk/utils.hpp"

#include "ve/vulkan/command_buffer.hpp"

#include "ve/memory/malloc.hpp"



namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* commands */
	class command_buffer;
}


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- C O M M A N D S -----------------------------------------------------

	class commands final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::commands;


		private:

			// -- private members ---------------------------------------------

			/* pool */
			vk::command_pool _pool;

			/* level */
			vk::command_buffer_level _level;

			/* data */
			vk::command_buffer* _data;

			/* capacity */
			vk::u32 _capacity;

			/* size */
			vk::u32 _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			commands(void) = delete;

			/* command pool constructor */
			commands(const vk::command_pool& pool) noexcept
			: _pool{pool}, _level{VK_COMMAND_BUFFER_LEVEL_PRIMARY},
			  _data{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* command buffer constructor */
			commands(const vk::command_pool& pool,
					 const vk::u32& size,
					 const vk::command_buffer_level& level = VK_COMMAND_BUFFER_LEVEL_PRIMARY)
			: _pool{pool}, _level{level}, _data{nullptr}, _capacity{size}, _size{size} {

				// check if size is zero
				if (_size == 0U)
					return;

				// allocate memory
				_data = ve::malloc<vk::command_buffer>(_size);

				// here need exception guard !

				// create info
				const vk::command_buffer_info info {
					// structure type
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					// next structure
					.pNext              = nullptr,
					// command pool from which buffers are allocated
					.commandPool        = _pool,
					// level of command buffer
					.level              = _level,
					// number of command buffers to allocate
					.commandBufferCount = _size
				};

				// allocate command buffers
				vk::try_execute<"failed to allocate command buffers">(
						::vk_allocate_command_buffers,
						vulkan::device::logical(), &info, _data);
			}

			/* deleted copy constructor */
			commands(const ___self&) = delete;

			/* move constructor */
			commands(___self&& other) noexcept
			: _pool{other._pool}, _data{other._data}, _capacity{other._capacity}, _size{other._size} {

				// invalidate other
				other._init();
			}

			/* destructor */
			~commands(void) noexcept {

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

				// release command buffers
				___self::_clear();

				// deallocate memory
				___self::_deallocate();

				// move data
				_data     = other._data;
				_size     = other._size;
				_capacity = other._capacity;

				// invalidate other
				other._init();

				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> const vk::u32& {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> const vk::u32& {
				return _capacity;
			}

			/* data */
			auto data(void) noexcept -> vk::command_buffer* {
				return _data;
			}

			/* data */
			auto data(void) const noexcept -> const vk::command_buffer* {
				return _data;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const vk::u32 index) noexcept -> vulkan::command_buffer {
				return vulkan::command_buffer{_data[index]};
			}


			// -- public modifiers --------------------------------------------

			/* emplace back */
			auto emplace_back(void) -> void {

				// check if capacity is reached
				if (___self::_available() == 0U)
					// expand capacity
					___self::_reserve(___self::_expand());

				// create info object
				const vk::command_buffer_info info {
					// type of structure
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					// pointer to next structure
					.pNext              = nullptr,
					// command pool from which buffers are allocated
					.commandPool        = _pool,
					// level of command buffer
					.level              = _level,
					// number of command buffers to allocate
					.commandBufferCount = 1U
				};

				// create command buffer
				vk::try_execute<"failed to allocate command buffer">(
						::vk_allocate_command_buffers,
						vulkan::device::logical(), &info, _data + _size);

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
			auto reserve(const vk::u32 capacity) -> void {

				// check if capacity is sufficient
				if (capacity <= _capacity)
					return;

				// call reserve implementation
				___self::_reserve(capacity);
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto _init(void) noexcept -> void {
				_data     = nullptr;
				_size     = 0U;
				_capacity = 0U;
			}

			/* deallocate */
			auto _deallocate(void) const noexcept -> void {

				// check if pointer is null
				if (_data == nullptr)
					return;

				// deallocate memory
				ve::free(_data);
			}

			/* clear */
			auto _clear(void) const noexcept -> void {

				if (_size == 0U)
					return;

				// release command buffers
				::vk_free_command_buffers(vulkan::device::logical(),
						_pool, _size, _data);
			}

			/* available */
			auto _available(void) const noexcept -> vk::u32 {
				return _capacity - _size;
			}

			/* expand */
			auto _expand(void) const noexcept -> vk::u32 {
				return _capacity == 0U ? 1U : _capacity << 1U;
			}

			/* reserve */
			auto _reserve(const vk::u32& capacity) -> void {

				// reallocate memory
				_data = ve::realloc<vk::command_buffer>(_data, capacity);

				// update capacity
				_capacity = capacity;
			}

	}; // class commands

} // namespace vulkan

#endif // ___ve_vulkan_commands___
