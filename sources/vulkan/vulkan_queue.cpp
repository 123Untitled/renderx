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
