#ifndef ENGINE_VULKAN_DEVICE_HPP
#define ENGINE_VULKAN_DEVICE_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_physical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- D E V I C E ---------------------------------------------------------

	class logical_device final {
		
		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::logical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			logical_device(void) noexcept
			: _device{nullptr}, _priority{1.0f} {
			}

			/* physical device constructor */
			logical_device(vulkan::physical_device& pdevice, const vulkan::surface& surface) noexcept
			: _device{nullptr}, _priority{1.0f} {

				::VkDeviceQueueCreateInfo queue_info = self::create_device_queue_info(pdevice, surface, _priority);

				::VkPhysicalDeviceFeatures features{}; /* not implemented */
				std::memset(&features, 0, sizeof(features));

				::VkDeviceCreateInfo device_info = self::create_device_info(queue_info, features);

				::VkResult result = ::vkCreateDevice(pdevice.underlying(),
													 &device_info,
													 nullptr,
													 &_device);

				if (result != VK_SUCCESS) {
					std::cerr << "failed to create logical device: " << result << std::endl;
					return;
				}

			}

			/* deleted copy constructor */
			logical_device(const self&) = delete;

			/* move constructor */
			logical_device(self&& other) noexcept
			: _device{other._device}, _priority{other._priority} {
				other.init();
			}

			/* destructor */
			~logical_device(void) noexcept {
				free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				free();
				  _device = other._device;
				_priority = other._priority;
				other.init();
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkDevice& {
				return _device;
			}

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkDevice& {
				return _device;
			}


		private:

			// -- private static methods --------------------------------------

			/* create device info */
			static auto create_device_info(::VkDeviceQueueCreateInfo& queue_info,
										   ::VkPhysicalDeviceFeatures& features) noexcept -> ::VkDeviceCreateInfo {

				return ::VkDeviceCreateInfo{
							.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
							.pNext                   = nullptr,
							.flags                   = 0,
							.queueCreateInfoCount    = 1,
							.pQueueCreateInfos       = &queue_info,
							.enabledLayerCount       = 0,
							.ppEnabledLayerNames     = nullptr,
							.enabledExtensionCount   = 0,
							.ppEnabledExtensionNames = nullptr,
							.pEnabledFeatures        = &features
				};
			}

			/* create device queue info */
			static auto create_device_queue_info(vulkan::physical_device& pdevice,
												 const vulkan::surface& surface,
												 float& priority) noexcept -> ::VkDeviceQueueCreateInfo {

				::int32_t index = vulkan::queue_families::find(pdevice, surface);

				if (index == -1) {
					std::cerr << "failed to find queue family with graphics bit set" << std::endl;
				}

				return ::VkDeviceQueueCreateInfo{
							.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
							.pNext            = nullptr,
							.flags            = 0,
							.queueFamilyIndex = static_cast<::uint32_t>(index),
							.queueCount       = 1,
							.pQueuePriorities = &priority
				};
			}



			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				if (_device == nullptr)
					return;
				::vkDestroyDevice(_device, nullptr);
			}

			/* init */
			auto init(void) noexcept -> void {
				_device = nullptr;
				_priority = 1.0f;
			}


			// -- private members ---------------------------------------------

			/* vulkan device */
			::VkDevice _device;

			/* queue priority */
			float _priority;

	}; // class device

} // namespace vulkan

#endif // ENGINE_VULKAN_DEVICE_HPP
