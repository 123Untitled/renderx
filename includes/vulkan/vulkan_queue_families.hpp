#ifndef ENGINE_VULKAN_QUEUE_FAMILIES_HPP
#define ENGINE_VULKAN_QUEUE_FAMILIES_HPP

#include <vulkan/vulkan.h>
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"

// V U L K A N  N A M E S P A C E ---------------------------------------------

namespace vulkan {

	// -- Q U E U E  F A M I L I E S ------------------------------------------

	class queue_families final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue_families;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			queue_families(void) = delete;

			/* deleted copy constructor */
			queue_families(const self&) = delete;

			/* deleted move constructor */
			queue_families(self&&) = delete;

			/* destructor */
			~queue_families(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public static methods ---------------------------------------

			/* find */
			static auto find(const vulkan::physical_device& device, const vulkan::surface& surface) -> ::uint32_t {
				// get queue families
				static const auto families = self::enumerate(device);

				for (::uint32_t i = 0; i < families.size(); ++i) {
					// check queue flags
					if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
						VkBool32 present = false;
						VkResult result = ::vkGetPhysicalDeviceSurfaceSupportKHR(device.underlying(), i, surface.underlying(), &present);
						if (result != VK_SUCCESS)
							throw engine::exception{"failed to get physical device surface support"};
						if (present == VK_TRUE)
							return i;
					}
				}
				throw engine::exception{"failed to find suitable queue family"};
			}


		private:

			// -- private static methods --------------------------------------

			/* enumeration */
			static auto enumerate(const vulkan::physical_device& device) -> std::vector<::VkQueueFamilyProperties> {

				::uint32_t count = 0;
				// get number of queue families
				::vkGetPhysicalDeviceQueueFamilyProperties(device.underlying(), &count, nullptr);
				// check number of queue families
				if (count == 0)
					throw engine::exception{"failed to find queue families"};
				// new vector of queue families properties
				std::vector<::VkQueueFamilyProperties> families;
				// allocate memory
				families.resize(count);
				// get queue families
				::vkGetPhysicalDeviceQueueFamilyProperties(device.underlying(), &count, families.data());
				// return queue families
				return families;
			}

	}; // class queue_families


	// -- Q U E U E -----------------------------------------------------------

	class queue final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue;


			// -- public lifecycle --------------------------------------------

			/* device and queue family index constructor */
			//queue(const vulkan::logical_device& device, ::uint32_t index) noexcept
			//: _queue{nullptr} {
			//
			//	::vkGetDeviceQueue(device.underlying(), index, 0, &_queue);
			//}


		private:

			// -- private members ---------------------------------------------

			/* queue */
			::VkQueue _queue;

	};

} // namespace vulkan

#endif // ENGINE_VULKAN_QUEUE_FAMILIES_HPP





/*
			static auto print(const std::vector<::VkQueueFamilyProperties>& families) -> void {

				for (const auto& family : families) {

					if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
						std::cout << "graphics queue family found" << std::endl;
					}

					if (family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
						std::cout << "compute queue family found" << std::endl;
					}

					if (family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
						std::cout << "transfer queue family found" << std::endl;
					}

					if (family.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
						std::cout << "sparse binding queue family found" << std::endl;
					}

					if (family.queueFlags & VK_QUEUE_PROTECTED_BIT) {
						std::cout << "protected queue family found" << std::endl;
					}

					if (family.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) {
						std::cout << "video decode queue family found" << std::endl;
					}

					#ifdef VK_ENABLE_BETA_EXTENSIONS
					if (family.queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) {
						std::cout << "video encode queue family found" << std::endl;
					}
					#endif

					if (family.queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV) {
						std::cout << "optical flow queue family found" << std::endl;
					}
				}
			}
			*/
