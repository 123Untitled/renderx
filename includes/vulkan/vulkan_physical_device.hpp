#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include "vulkan_instance.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_surface_capabilities.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* extension properties */
	class extension_properties;


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





			// -- public conversion operators ---------------------------------

			/* VkPhysicalDevice conversion operator */
			operator const ::VkPhysicalDevice&() const noexcept;


			// -- public accessors --------------------------------------------

			/* supports swapchain */
			auto supports_swapchain(void) const noexcept -> bool;

			/* have formats */
			auto have_formats(const vulkan::surface&) const -> bool;

			/* have present modes */
			auto have_present_modes(const vulkan::surface&) const -> bool;



			/* is support surface and queue family */
			auto is_support(const vulkan::surface&, ::uint32_t) const -> bool;



			/* extensions */
			auto extensions(void) const -> xns::vector<vulkan::extension_properties>;

			/* capabilities */
			auto capabilities(const vulkan::surface&) const -> vulkan::surface_capabilities;


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

			/* VkPhysicalDevice constructor */
			physical_device(const ::VkPhysicalDevice&) noexcept;


			// -- private static methods --------------------------------------

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
