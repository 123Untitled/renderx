#include "ve/vulkan/fence.hpp"
#include "ve/vk/utils.hpp"
#include "ve/vulkan/device.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::fence::fence(void)
: ve::fence{VK_FENCE_CREATE_SIGNALED_BIT} {
}

/* flags constructor */
ve::fence::fence(const vk::fence_create_flags& flags)
: _fence{

	// create fence
	vk::make_unique<vk::fence>(

			// create info
			vk::fence_info{
				// structure type
				VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
				// next structure
				nullptr,
				// flag
				flags})} {
}


// -- public accessors --------------------------------------------------------

/* get */
auto ve::fence::get(void) const noexcept -> const vk::fence& {
	return _fence;
}


// -- public methods ----------------------------------------------------------

/* reset */
auto ve::fence::reset(void) -> void {

	// reset fence
	vk::try_execute<"failed to reset fence">(
		// function
		::vk_reset_fences,
		// device
		vulkan::device::logical(),
		// fence count
		1U,
		// fences array
		&(_fence.get())
	);
/*
   On success, this command returns
   VK_SUCCESS
   On failure, this command returns
   VK_ERROR_OUT_OF_DEVICE_MEMORY
*/


}

/* wait */
auto ve::fence::wait(void) -> void {

	// wait all fences
	vk::try_execute<"failed to wait for fence">(
			// function
			::vk_wait_for_fences,
			// device
			vulkan::device::logical(),
			// fence count
			1U,
			// fences array
			&(_fence.get()),
			// wait all
			VK_TRUE,
			// timeout
			UINT64_MAX
	);

	/*
	   On success, this command returns

	   VK_SUCCESS
	   VK_TIMEOUT

	   On failure, this command returns

	   VK_ERROR_OUT_OF_HOST_MEMORY
	   VK_ERROR_OUT_OF_DEVICE_MEMORY
	   VK_ERROR_DEVICE_LOST
	*/


}
