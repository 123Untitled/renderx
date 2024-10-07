/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "engine/vulkan/queue.hpp"
#include "engine/vulkan/device.hpp"


// -- public lifecycle --------------------------------------------------------

/* device and queue family constructor */
vulkan::queue::queue(void) noexcept
: _queue{nullptr} {

	// get device queue
	::vk_get_device_queue(vulkan::device::logical(),
						  vulkan::device::family(), 0U, &_queue);
}


// -- public static methods ---------------------------------------------------

/* info */
auto vulkan::queue::info(const vk::u32 index,
						 const float& priority) noexcept -> vk::device_queue_info {
	// return queue info
	return vk::device_queue_info{
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0U,
		.queueFamilyIndex = index,
		.queueCount = 1U,
		.pQueuePriorities = &priority
	};
}

#include "engine/vulkan/command_buffer.hpp"

// -- public methods ----------------------------------------------------------


/* submit */ // not thread safe
auto vulkan::queue::submit(const vk::semaphore& wait,
						   const vk::semaphore& signal,
						   const vk::fence& fence,
						   const vulkan::command_buffer<vulkan::primary>& cmd) const -> void {


	const vk::pipeline_stage_flags wait_stages[] = {
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
	};


	const vk::submit_info info{
		// structure type
		.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext                = nullptr,
		// wait semaphores
		.waitSemaphoreCount   = 1U,
		.pWaitSemaphores      = &(wait),
		// wait stages
		.pWaitDstStageMask    = wait_stages,
		// command buffer count
		.commandBufferCount   = 1U,
		// command buffers
		.pCommandBuffers      = &(cmd.underlying()),
		// signal semaphores
		.signalSemaphoreCount = 1U,
		.pSignalSemaphores    = &(signal)
	};

	// see vkQueueSubmit2KHR
	vk::try_execute<"failed to submit queue">(
			::vkQueueSubmit, _queue, 1U, // submit count
						&info, fence);
}

/* present */
auto vulkan::queue::present(const vulkan::swapchain& swapchain,
							const vk::u32&           image_index,
							const vk::semaphore&     wait) const -> bool {

	// create present info
	const vk::present_info info{
		// structure type
		VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		// next structure
		nullptr,
		// wait semaphore count
		1U,
		// wait semaphores
		&wait,
		// swapchain count
		1U,
		// swapchains
		&(swapchain.underlying()),
		// image indices (index of image to present)
		&image_index,
		// results (optional)
		nullptr
	};

	// here error not means program must stop
	if (::vkQueuePresentKHR(_queue, &info) != VK_SUCCESS) {
		std::cout << "failed to present swapchain image" << std::endl;
		return false;
	}

	return true;

}

/* wait idle */
auto vulkan::queue::wait_idle(void) const -> void {

	// wait for queue to be idle
	vk::try_execute<"failed to wait for queue to be idle">(
			::vkQueueWaitIdle, _queue);

	// this synchronization is not optimal
	// prefer to use fences and semaphores
}
