#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::command_pool::command_pool(void) noexcept
: _pool{VK_NULL_HANDLE} {}

/* logical device and queue family index constructor */
vulkan::command_pool::command_pool(const vulkan::logical_device& device, const vk::u32 family)
// create command pool
: _pool{vk::create_command_pool(device, vk::command_pool_info{
		.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext            = nullptr,
		.flags            = 0,
		.queueFamilyIndex = family
	})} {
}

/* copy constructor */
vulkan::command_pool::command_pool(const self& other) noexcept
: _pool{other._pool} {
}

/* move constructor */
vulkan::command_pool::command_pool(self&& other) noexcept
: self{other} /* copy */ {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::command_pool::operator=(const self& other) noexcept -> self& {
	_pool = other._pool;
	return *this;
}

/* move assignment operator */
auto vulkan::command_pool::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public methods ----------------------------------------------------------

/* new command buffer */
auto vulkan::command_pool::new_command_buffer(const vulkan::logical_device& device) const -> vulkan::command_buffer {
	return vulkan::command_buffer{device, *this};
}

/* new buffers */
auto vulkan::command_pool::new_buffers(const vulkan::logical_device& device, const ::uint32_t count) const -> xns::vector<vulkan::command_buffer> {
	return vulkan::command_buffer::create_buffers(device, *this, count);
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::command_pool::destroy(const vulkan::logical_device& device) noexcept -> void {
	vk::destroy_command_pool(device, _pool);
}


// -- public conversion operators ---------------------------------------------

/* vk::command_pool conversion operator */
vulkan::command_pool::operator const vk::command_pool&(void) const noexcept {
	return _pool;
}


