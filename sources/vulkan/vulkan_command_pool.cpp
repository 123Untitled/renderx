#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::command_pool::command_pool(void) noexcept
: _pool{} {}

/* logical device and queue family index constructor */
vulkan::command_pool::command_pool(const vk::shared<vk::device>& device,
								   const vk::u32 family)
: _pool{} {

	auto pool = vk::create(device, vk::command_pool_info{
		.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext            = nullptr,
		.flags            = 0,
		// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT (reset command buffers, implicitly)
		// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT (reset command buffers, explicitly)
		// VK_COMMAND_POOL_CREATE_PROTECTED_BIT (protected memory)
		.queueFamilyIndex = family
	});

	// make managed
	_pool = vk::make_managed(pool, device);
}

/* copy constructor */
vulkan::command_pool::command_pool(const self& other) noexcept
: _pool{other._pool} {
}

/* move constructor */
vulkan::command_pool::command_pool(self&& other) noexcept
: _pool{xns::move(other._pool)} {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::command_pool::operator=(const self& other) noexcept -> self& {
	_pool = other._pool;
	return *this;
}

/* move assignment operator */
auto vulkan::command_pool::operator=(self&& other) noexcept -> self& {
	_pool = xns::move(other._pool);
	return *this;
}


// -- public methods ----------------------------------------------------------

/* new primary command buffer */
auto vulkan::command_pool::new_primary_command_buffer(const vk::u32 size) -> void {

	const vk::shared<vk::device>& device = _pool.dependency<0>();

	_buffers = vk::create(device, vk::command_buffer_info{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = VK_NULL_HANDLE,
			.commandPool = _pool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, // or VK_COMMAND_BUFFER_LEVEL_SECONDARY
			.commandBufferCount = size
	});
}

/* new secondary command buffer */
auto vulkan::command_pool::new_secondary_command_buffer(const vk::u32 size) -> void {

	const vk::shared<vk::device>& device = _pool.dependency<0>();

	_buffers = vk::create(device, vk::command_buffer_info{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = VK_NULL_HANDLE,
			.commandPool = _pool,
			.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY, // or VK_COMMAND_BUFFER_LEVEL_SECONDARY
			.commandBufferCount = size
	});
}


/* new buffers */
auto vulkan::command_pool::new_buffers(const vulkan::logical_device& device, const ::uint32_t count) const -> xns::vector<vulkan::command_buffer> {
	return vulkan::command_buffer::create_buffers(device, *this, count);
}


// -- public conversion operators ---------------------------------------------

/* vk::command_pool conversion operator */
vulkan::command_pool::operator const vk::command_pool&(void) const noexcept {
	return _pool;
}


