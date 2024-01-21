#include "vulkan_queue.hpp"


// -- public lifecycle --------------------------------------------------------

/* device and queue family constructor */
vulkan::queue::queue(const vulkan::logical_device& device,
					 const ::uint32_t index) noexcept
: _queue{nullptr} {

	//::vkGetDeviceQueue(device.underlying(), index, 0, &_queue);
}


// -- public static methods ---------------------------------------------------

/* create queue info */
auto vulkan::queue::create_queue_info(const ::uint32_t index,
									  const float& priority) noexcept -> ::VkDeviceQueueCreateInfo {
	// return queue info
	return ::VkDeviceQueueCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueFamilyIndex = index,
		.queueCount = 1,
		.pQueuePriorities = &priority
	};
}


// -- public methods ----------------------------------------------------------

/* submit */
auto vulkan::queue::submit(const vulkan::semaphore* wait,
						   ::uint32_t wait_count,
						   const vulkan::semaphore* signal,
						   ::uint32_t signal_count,
						   const vulkan::command_buffer* buffers,
						   ::uint32_t buffer_count) const -> void {


	const ::VkPipelineStageFlags wait_stages[] = {
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
	};

	const ::VkSubmitInfo info{
		// structure type
		.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext                = nullptr,

		// wait semaphores
		.waitSemaphoreCount   = wait_count,
		.pWaitSemaphores      = reinterpret_cast<const ::VkSemaphore*>(wait),

		// wait stages
		.pWaitDstStageMask    = wait_stages,

		// command buffers
		.commandBufferCount   = buffer_count,
		/* command_buffers[image_index] */
		.pCommandBuffers      = reinterpret_cast<const ::VkCommandBuffer*>(buffers),

		// signal semaphores
		.signalSemaphoreCount = signal_count,
		.pSignalSemaphores    = reinterpret_cast<const ::VkSemaphore*>(signal)
	};

	if (::vkQueueSubmit(
			_queue,
			1, // submit count
			&info,
			nullptr // fence
			) != VK_SUCCESS)
		throw engine::exception{"failed to submit draw command buffer"};
}

/* present */
auto vulkan::queue::present(const vulkan::swapchain& swapchain,
							const ::uint32_t image_index,
							const vulkan::semaphore* wait,
							::uint32_t wait_count) const -> bool {

	const ::VkPresentInfoKHR info{
		.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext              = nullptr,

		.waitSemaphoreCount = wait_count,
		.pWaitSemaphores    = reinterpret_cast<const ::VkSemaphore*>(wait),

		.swapchainCount     = 1, // swapchain count ???
		.pSwapchains        = &(static_cast<const ::VkSwapchainKHR&>(swapchain)),
		.pImageIndices      = &image_index,
		.pResults           = nullptr // VkResult array, optional
	};

	// here error not means program must stop
	if (::vkQueuePresentKHR(_queue, &info) != VK_SUCCESS) {
		std::cout << "failed to present swapchain image" << std::endl;
		return false;
	}

	return true;
}
