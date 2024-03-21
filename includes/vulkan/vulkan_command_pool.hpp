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

#ifndef ENGINE_VULKAN_COMMAND_POOL_HEADER
#define ENGINE_VULKAN_COMMAND_POOL_HEADER

// interal headers
#include "vulkan/vk_shared.hpp"
#include "vulkan/command_buffer.hpp"




namespace vk {

	struct transient_bit final {
		// reset command buffers, implicitly
		static constexpr vk::command_pool_create_flags value = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	};

	struct reset_bit final {
		// reset command buffers, explicitly
		static constexpr vk::command_pool_create_flags value = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	};

	struct protected_bit final {
		// protected memory
		static constexpr vk::command_pool_create_flags value = VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
	};

	struct void_bit final {
		static constexpr vk::command_pool_create_flags value = 0;
	};
}



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- C O M M A N D  P O O L ----------------------------------------------

	template <typename T>
	class command_pool final {

		// -- assertions ------------------------------------------------------

		/* check if T is a valid flags type */
		static_assert(std::same_as<T, vk::transient_bit>
				   || std::same_as<T, vk::reset_bit>
				   || std::same_as<T, vk::protected_bit>
				   || std::same_as<T, vk::void_bit>,
				   "T must be a valid flags type");



		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_pool<T>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_pool(void) noexcept = default;

			/* logical device and queue family index constructor */
			command_pool(const vk::shared<vk::device>& device,
						 const vk::u32& family)
			: _pool{

				device, vk::command_pool_info {
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.pNext = nullptr,
					.flags = T::value,
					.queueFamilyIndex = family
				}} {
			}


			/* copy constructor */
			command_pool(const self&) noexcept = default;

			/* move constructor */
			command_pool(self&&) noexcept = default;

			/* destructor */
			~command_pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* reset to system */
			auto reset_to_system(void) const -> void {
				// info: all command buffer objects allocated from command pool must not be in the pending state
				// command buffer allocations back to the system
				vk::reset_command_pool(_pool.dependency(), _pool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
			}

			/* reset to pool */
			auto reset_to_pool(void) const -> void {
				// info: all command buffer objects allocated from command pool must not be in the pending state
				// command buffer allocations back to the pool
				vk::reset_command_pool(_pool.dependency(), _pool, 0U);
			}

			/* trim */
			auto trim(void) const noexcept -> void {
				// trimming a command pool recycles unused memory from the command pool back to the system.
				// command buffers allocated from the pool are not affected by the command.
				vk::trim_command_pool(_pool.dependency(), _pool);
			}


			// -- public conversion operators ---------------------------------

			/* vk::command_pool conversion operator */
			operator const vk::command_pool&(void) const noexcept {
				return _pool;
			}

			/* vk::shared<vk::command_pool> conversion operator */
			operator const vk::shared<vk::command_pool>&(void) const noexcept {
				return _pool;
			}


		private:

			// -- private members ---------------------------------------------

			/* pool */
			vk::shared<vk::command_pool> _pool;

	}; // class command_pool

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMAND_POOL_HEADER
