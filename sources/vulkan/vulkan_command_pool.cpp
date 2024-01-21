#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* logical device constructor */
vulkan::command_pool::command_pool(const vulkan::logical_device& device)
: _pool{VK_NULL_HANDLE} {

	const ::VkCommandPoolCreateInfo info{
		.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext            = nullptr,
		.flags            = 0,
		.queueFamilyIndex = 0 // here need to get queue family index
	};

	if (::vkCreateCommandPool(device, &info, nullptr, &_pool) != VK_SUCCESS)
		throw engine::exception{"failed to create command pool"};
}


// -- public methods ----------------------------------------------------------

/* new buffer */
auto vulkan::command_pool::new_buffer(const vulkan::logical_device& device) const -> vulkan::command_buffer {
	return vulkan::command_buffer{device, *this};
}

/* new buffers */
auto vulkan::command_pool::new_buffers(const vulkan::logical_device& device, const ::uint32_t count) const -> xns::vector<vulkan::command_buffer> {
	return vulkan::command_buffer::create_buffers(device, *this, count);
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::command_pool::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_pool == VK_NULL_HANDLE)
		return;
	::vkDestroyCommandPool(device, _pool, nullptr);
	_pool = VK_NULL_HANDLE;
}


// -- public conversion operators ---------------------------------------------

/* VkCommandPool conversion operator */
vulkan::command_pool::operator ::VkCommandPool(void) const noexcept {
	return _pool;
}


