#include "vulkan_semaphore.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::semaphore::semaphore(void) noexcept
: _semaphore{} {
}

/* logical device constructor */
vulkan::semaphore::semaphore(const vk::shared<vk::device>& device)
: _semaphore{} {

	auto semaphore = vk::create(device, vk::semaphore_info{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0
	});

	// make managed
	_semaphore = vk::make_managed(semaphore, device);
}

/* copy constructor */
vulkan::semaphore::semaphore(const self& other) noexcept
: _semaphore{other._semaphore} {
}

/* move constructor */
vulkan::semaphore::semaphore(self&& other) noexcept
: _semaphore{xns::move(other._semaphore)} {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::semaphore::operator=(const self& other) noexcept -> self& {
	_semaphore = other._semaphore;
	return *this;
}

/* move assignment operator */
auto vulkan::semaphore::operator=(self&& other) noexcept -> self& {
	_semaphore = xns::move(other._semaphore);
	return *this;
}





// -- public conversion operators ---------------------------------------------

/* vk::semaphore conversion operator */
vulkan::semaphore::operator const vk::semaphore&(void) const noexcept {
	return _semaphore;
}
