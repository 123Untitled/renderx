#include "engine/vulkan/semaphore.hpp"

#include "engine/vk/utils.hpp"
#include "engine/vulkan/device.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::semaphore::semaphore(void)
/* uninitialized semaphore */ {

	// create info
	vk::semaphore_info info {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0U
	};

	// create semaphore
	vk::try_execute<"failed to create semaphore">(
			::vk_create_semaphore,
			vulkan::device::logical(), &info, nullptr, &_semaphore);
}

/* move constructor */
vulkan::semaphore::semaphore(___self&& ___ot) noexcept
: _semaphore{___ot._semaphore} {

	// invalidate other
	___ot._semaphore = nullptr;
}

/* destructor */
vulkan::semaphore::~semaphore(void) noexcept {

	if (_semaphore == nullptr)
		return;

	// release semaphore
	::vk_destroy_semaphore(vulkan::device::logical(),
			_semaphore, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::semaphore::operator=(___self&& other) noexcept -> ___self& {

	// check for self-assignment
	if (this == &other)
		return *this;

	// release semaphore
	if (_semaphore != nullptr)
		::vk_destroy_semaphore(vulkan::device::logical(),
				_semaphore, nullptr);

	// move assignment
	_semaphore = other._semaphore;
	other._semaphore = nullptr;

	// done
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::semaphore::underlying(void) const noexcept -> const vk::semaphore& {
	return _semaphore;
}
