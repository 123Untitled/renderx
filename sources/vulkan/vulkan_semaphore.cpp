#include "vulkan_semaphore.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::semaphore::semaphore(void) noexcept
: _semaphore{VK_NULL_HANDLE} {}

/* logical device constructor */
vulkan::semaphore::semaphore(const vulkan::logical_device& device)
: _semaphore{VK_NULL_HANDLE} {

	// create info
	const ::VkSemaphoreCreateInfo info{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0
	};
	// create semaphore
	if (::vkCreateSemaphore(device, &info, nullptr, &_semaphore) != VK_SUCCESS)
		throw engine::exception{"failed to create semaphore"};
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::semaphore::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_semaphore == VK_NULL_HANDLE)
		return;
	::vkDestroySemaphore(device, _semaphore, nullptr);
	_semaphore = VK_NULL_HANDLE;
}


// -- public conversion operators ---------------------------------------------

/* VkSemaphore conversion operator */
vulkan::semaphore::operator const ::VkSemaphore&(void) const noexcept {
	return _semaphore;
}
