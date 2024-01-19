#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include "vulkan_instance.hpp"
#include "vulkan_surface.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::physical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			physical_device(void) noexcept;


			/* copy constructor */
			physical_device(const self&) noexcept;

			/* move constructor */
			physical_device(self&&) noexcept;

			/* destructor */
			~physical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkPhysicalDevice&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkPhysicalDevice&;



			/* is support surface and queue family */
			auto is_support(const vulkan::surface&, ::uint32_t) const -> bool;



			/* extensions */
			auto extensions(void) const -> xns::vector<::VkExtensionProperties>;

			/* capabilities */
			auto capabilities(const vulkan::surface&) const -> ::VkSurfaceCapabilitiesKHR;

			/* formats */
			auto formats(const vulkan::surface&) const -> xns::vector<::VkSurfaceFormatKHR>;

			/* present modes */
			auto present_modes(const vulkan::surface&) const -> xns::vector<::VkPresentModeKHR>;

			/* properties */
			auto properties(void) const -> ::VkPhysicalDeviceProperties;

			/* features */
			auto features(void) const -> ::VkPhysicalDeviceFeatures;



			/* info */
			auto info(void) const noexcept -> void {

				::VkPhysicalDeviceProperties properties;
				::vkGetPhysicalDeviceProperties(_device, &properties);
				std::cout << "device name: " << properties.deviceName << std::endl;
			}


		private:

			// -- friends -----------------------------------------------------

			/* xns allocator as friend */
			friend class xns::allocator<self>;


			// -- private lifecycle -------------------------------------------

			/* ::VkPhysicalDevice constructor */
			physical_device(const ::VkPhysicalDevice&) noexcept;


			// -- private static methods --------------------------------------


			/* is device suitable */
			static auto is_suitable(const ::VkPhysicalDevice&,
									const std::vector<::VkExtensionProperties>&,
									const ::VkSurfaceCapabilitiesKHR&,
									const std::vector<::VkSurfaceFormatKHR>&,
									const std::vector<::VkPresentModeKHR>&) noexcept -> bool;

			/* device type */
			static auto type(const ::VkPhysicalDeviceProperties&) noexcept -> void;

			/* device features */
			static auto features(const ::VkPhysicalDeviceFeatures&) noexcept -> void;


			// -- private members ---------------------------------------------

			/* device */
			::VkPhysicalDevice _device;

	};

}

#endif // ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
