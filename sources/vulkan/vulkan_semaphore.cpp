#include "vulkan_semaphore.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::semaphore::semaphore(void) noexcept
: _semaphore{} {
}

/* logical device constructor */
vulkan::semaphore::semaphore(const vk::shared<vk::device>& device)
: _semaphore{} {

	_semaphore = {device, vk::semaphore_info{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0
	}};

}


// -- public conversion operators ---------------------------------------------

/* vk::semaphore conversion operator */
vulkan::semaphore::operator const vk::semaphore&(void) const noexcept {
	return _semaphore;
}
