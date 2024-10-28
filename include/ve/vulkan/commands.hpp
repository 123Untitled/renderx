/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_COMMANDS___
#define ___ENGINE_VULKAN_COMMANDS___

#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vk/exception.hpp"
#include "ve/vk/utils.hpp"

#include <concepts>

#include "ve/memory/malloc.hpp"
#include "ve/memory/memcpy.hpp"



namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* commands */
	template <typename T>
	class command_buffer;

}


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- level types ---------------------------------------------------------

	/* primary level */
	struct primary;

	/* secondary level */
	struct secondary;


	// -- I S  L E V E L ------------------------------------------------------

	template <typename ___type>
	concept is_level = std::same_as<___type, primary> || std::same_as<___type, secondary>;


	// -- C O M M A N D S -----------------------------------------------------

	template <typename ___type>
	class commands final {


		// -- assertions ------------------------------------------------------

		/* check if T is a valid level type */
		static_assert(vulkan::is_level<___type>, "commands: invalid level type");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::commands<___type>;


		public:

			// -- public types ------------------------------------------------


			/* level type */
			using level_type = ___type;

			/* size type */
			using size_type  = vk::u32;

			/* mutable reference type */
			using mut_ref    = vulkan::command_buffer<level_type>&;

			/* constant reference type */
			using const_ref  = const vulkan::command_buffer<level_type>&;

			/* mutable pointer type */
			using mut_ptr    = vk::command_buffer*;

			/* constant pointer type */
			using const_ptr  = const vk::command_buffer*;


		private:

			// -- private members ---------------------------------------------

			/* pool */
			vk::command_pool _pool;

			/* data */
			vk::command_buffer* _data;

			/* size */
			size_type _size;

			/* capacity */
			size_type _capacity;



		public:


			// -- public static methods ---------------------------------------

			/* level */
			static constexpr auto level(void) noexcept -> vk::command_buffer_level {
				if constexpr (std::same_as<___type, primary>)
					return VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				else
					return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
			}


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			commands(void) = delete;

			/* command pool constructor */
			commands(const vk::command_pool& ___pool) noexcept
			: _pool{___pool}, _data{nullptr}, _size{0U}, _capacity{0U} {
			}

			/* command buffer constructor */
			commands(const vk::command_pool& ___pool, const size_type& ___sz)
			: _pool{___pool}, _data{nullptr}, _size{___sz}, _capacity{___sz} {

				// check if size is zero
				if (_size == 0U)
					return;

				// allocate memory
				_data = ve::malloc<vk::command_buffer>(_size);

				// here need exception guard !

				// create info
				const vk::command_buffer_info info {
					// type of structure
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					// pointer to next structure
					.pNext              = nullptr,
					// command pool from which buffers are allocated
					.commandPool        = _pool,
					// level of command buffer
					.level              = ___self::level(),
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
			commands(___self&& ___ot) noexcept
			: _pool{___ot._pool}, _data{___ot._data}, _size{___ot._size}, _capacity{___ot._capacity} {

				// invalidate other
				___ot._init();
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
			auto operator[](const size_type ___idx) noexcept -> mut_ref {
				return reinterpret_cast<mut_ref>(*(_data + ___idx));
			}

			/* const subscript operator */
			auto operator[](const size_type ___idx) const noexcept -> const_ref {
				return reinterpret_cast<const_ref>(*(_data + ___idx));
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
					.level              = ___self::level(),
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
			auto reserve(const size_type ___sz) -> void {

				// check if capacity is sufficient
				if (___sz <= _capacity)
					return;

				// call reserve implementation
				___self::_reserve(___sz);
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
			auto _available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* expand */
			auto _expand(void) const noexcept -> size_type {
				return _capacity == 0U ? 1U : _capacity << 1U;
			}

			/* reserve */
			auto _reserve(const size_type ___cap) -> void {

				// reallocate memory
				const auto ___ndata = ve::realloc<vk::command_buffer>(_data, ___cap);

				// update members
				_data     = ___ndata;
				_capacity = ___cap;
			}

	}; // class commands

} // namespace vulkan

#endif // ___ENGINE_VULKAN_COMMANDS___
