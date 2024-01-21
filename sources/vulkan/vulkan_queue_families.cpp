#include "vulkan_queue_families.hpp"


// -- public static methods ---------------------------------------------------

/* find */
auto vulkan::queue_families::find(const vulkan::physical_device& device,
								  const vulkan::surface& surface) -> vk::u32 {
	// get queue families properties
	static const auto properties = vk::get_physical_device_queue_family_properties(device);

	for (vk::u32 i = 0; i < properties.size(); ++i) {
		// check queue flags
		if (properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT
		&& device.is_support_surface_and_queue_family(surface, i)) {
			return i;
		}
	}
	throw engine::exception{"failed to find suitable queue family"};
}
