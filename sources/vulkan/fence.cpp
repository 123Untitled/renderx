#include "renderx/vulkan/fence.hpp"
#include "renderx/vk/utils.hpp"
#include "renderx/vulkan/device.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::fence::fence(const vk::fence_create_flags& ___flags)
/* uninitialized fence */ {

	// create info
	const vk::fence_info info {
		// structure type
		VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		// next structure
		nullptr,
		// flag
		___flags
	};

	// create fence
	vk::try_execute<"failed to create fence">(
			::vk_create_fence,
			vulkan::device::logical(), &info, nullptr, &_fence);
}

/* move constructor */
vulkan::fence::fence(___self&& ___ot) noexcept
: _fence{___ot._fence} {

	// invalidate other
	___ot._fence = nullptr;
}

/* destructor */
vulkan::fence::~fence(void) noexcept {

	// check if fence is null
	if (_fence == nullptr)
		return;

	// destroy fence
	::vk_destroy_fence(vulkan::device::logical(),
			_fence, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::fence::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// release fence
	if (_fence != nullptr)
		::vk_destroy_fence(vulkan::device::logical(),
				_fence, nullptr);

	// move fence
	_fence = ___ot._fence;

	// invalidate other
	___ot._fence = nullptr;

	// done
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::fence::underlying(void) const noexcept -> const vk::fence& {
	return _fence;
}


// -- public methods ----------------------------------------------------------

/* reset */
auto vulkan::fence::reset(void) -> void {

	// reset fence
	::vk_reset_fences(
		// device
		vulkan::device::logical(),
		// fence count
		1U,
		// fences array
		&_fence
	);
}

/* wait */
auto vulkan::fence::wait(void) -> void {

	// wait all fences
	::vk_wait_for_fences(
			// device
			vulkan::device::logical(),
			// fence count
			1U,
			// fences array
			&_fence,
			// wait all
			VK_TRUE,
			// timeout
			UINT64_MAX
	);
}
