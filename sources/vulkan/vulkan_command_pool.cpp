/**********************************************************/
/* ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░*/
/* ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒*/
/* ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓*/
/* ███    ███  ████  █  ███████  ███  ██        █  ██    █*/
/* ████  █████      ██        █  ████  █  ████  █  ███   █*/
/**********************************************************/

#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"
#include <vulkan/vulkan.h>


// -- public lifecycle --------------------------------------------------------

/* logical device and queue family index constructor */
vulkan::command_pool::command_pool(const vk::shared<vk::device>& device,
								   const vk::u32 family)
: _pool{} {

	_pool = {device, vk::command_pool_info{
		.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext            = nullptr,
		.flags            = 0,
		.queueFamilyIndex = family
	}};


	/* flags:

	 * VK_COMMAND_POOL_CREATE_TRANSIENT_BIT (reset command buffers, implicitly)
	 * VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT (reset command buffers, explicitly)
	 * VK_COMMAND_POOL_CREATE_PROTECTED_BIT (protected memory)

	 */
}


// -- public methods ----------------------------------------------------------

/* new primary command buffer */
auto vulkan::command_pool::new_primary_command_buffer(const vk::u32 size) -> vulkan::command_buffer {

	const auto& device = _pool.dependency();

	_buffers = vk::create(device, vk::command_buffer_info{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = VK_NULL_HANDLE,
			.commandPool = _pool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			.commandBufferCount = size
	});
	return {};
}

/* new secondary command buffer */
auto vulkan::command_pool::new_secondary_command_buffer(const vk::u32 size) -> vulkan::command_buffer {

	const auto& device = _pool.dependency();

	_buffers = vk::create(device, vk::command_buffer_info{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = VK_NULL_HANDLE,
			.commandPool = _pool,
			.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
			.commandBufferCount = size
	});
	return {};
}


// -- public conversion operators ---------------------------------------------

/* vk::shared<vk::command_pool> conversion operator */
vulkan::command_pool::operator const vk::shared<vk::command_pool>&(void) const noexcept {
	return _pool;
}


