#ifndef ENGINE_VULKAN_QUEUE_FAMILIES_HPP
#define ENGINE_VULKAN_QUEUE_FAMILIES_HPP

#include <vulkan/vulkan.h>
#include "vulkan_physical_device.hpp"

// V U L K A N  N A M E S P A C E ---------------------------------------------

namespace vulkan {

	// Q U E U E  F A M I L I E S ---------------------------------------------

	class queue_families final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue_families;


			// -- public lifecycle --------------------------------------------

			/* physical device constructor */
			queue_families(const vulkan::physical_device& device) {

				::uint32_t count = 0;
				::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

				if (count == 0) {
					std::cerr << "error: no queue families found" << std::endl;
					return;
				}

				std::vector<::VkQueueFamilyProperties> families;
				families.resize(count);

				std::cout << "queue family count: " << count << std::endl;

				::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());

				for (::uint32_t i = 0; i < count; ++i) {

					if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
						std::cout << "graphics queue family found" << std::endl;
					}

					if (families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
						std::cout << "compute queue family found" << std::endl;
					}

					if (families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
						std::cout << "transfer queue family found" << std::endl;
					}

					if (families[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
						std::cout << "sparse binding queue family found" << std::endl;
					}

					if (families[i].queueFlags & VK_QUEUE_PROTECTED_BIT) {
						std::cout << "protected queue family found" << std::endl;
					}

					if (families[i].queueFlags & VK_QUEUE_FLAG_BITS_MAX_ENUM) {
						std::cout << "flag bits max enum queue family found" << std::endl;
					}
				}

			}



	};

}

#endif // ENGINE_VULKAN_QUEUE_FAMILIES_HPP
