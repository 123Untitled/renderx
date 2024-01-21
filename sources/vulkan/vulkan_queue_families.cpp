#include "vulkan_queue_families.hpp"


// -- public static methods ---------------------------------------------------

/* find */
auto vulkan::queue_families::find(const vulkan::physical_device& device,
								  const vulkan::surface& surface) -> ::uint32_t {
	// get queue families
	static const auto families = self::enumerate(device);

	for (::uint32_t i = 0; i < families.size(); ++i) {
		// check queue flags
		if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT
		&& device.is_support(surface, i)) {
			return i;
		}
	}
	throw engine::exception{"failed to find suitable queue family"};
}


// -- private static methods --------------------------------------------------

/* enumeration */
auto vulkan::queue_families::enumerate(const vulkan::physical_device& device) -> std::vector<::VkQueueFamilyProperties> {

	::uint32_t count = 0;
	// get number of queue families
	::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
	// check number of queue families
	if (count == 0)
		throw engine::exception{"failed to find queue families"};
	// new vector of queue families properties
	std::vector<::VkQueueFamilyProperties> families;
	// allocate memory
	families.resize(count);
	// get queue families
	::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());
	// return queue families
	return families;
}


