#include "vulkan_semaphore.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::semaphore::semaphore(void) noexcept
: _semaphore{VK_NULL_HANDLE} {}

/* logical device constructor */
vulkan::semaphore::semaphore(const vulkan::logical_device& device)
// create semaphore
: _semaphore{vk::create_semaphore(device, vk::semaphore_info{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0
		})} {
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::semaphore::destroy(const vulkan::logical_device& device) noexcept -> void {
	vk::destroy_semaphore(device, _semaphore);
}


// -- public conversion operators ---------------------------------------------

/* vk::semaphore conversion operator */
vulkan::semaphore::operator const vk::semaphore&(void) const noexcept {
	return _semaphore;
}
