#ifndef ENGINE_VULKAN_SWAPCHAIN_HPP
#define ENGINE_VULKAN_SWAPCHAIN_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- S W A P C H A I N ---------------------------------------------------

	class swapchain final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::swapchain;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			swapchain(void) noexcept;

			/* logical device and surface constructor */
			swapchain(const vulkan::logical_device&,
					  const vulkan::surface&,
					  const vulkan::surface_capabilities&,
					  const ::VkSurfaceFormatKHR&,
					  const ::VkPresentModeKHR&,
					  const ::VkExtent2D&);

			/* deleted copy constructor */
			swapchain(const self&) = delete;

			/* move constructor */
			swapchain(self&&) noexcept;

			/* destructor */
			~swapchain(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


		private:

			// -- private static methods --------------------------------------

			/* create swapchain info */
			static auto create_swapchain_info(const ::VkSurfaceCapabilitiesKHR&,
											 const ::VkSurfaceFormatKHR&,
											 const ::VkExtent2D&,
											 const ::VkPresentModeKHR&) noexcept -> ::VkSwapchainCreateInfoKHR;

			/* create swapchain */
			static auto create_swapchain(const vulkan::logical_device&,
										 const ::VkSwapchainCreateInfoKHR&) -> ::VkSwapchainKHR;





			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* swapchain */
			::VkSwapchainKHR _swapchain;

			/* images */
			xns::vector<::VkImage> _images;

			/* format */
			::VkFormat _format;

			/* extent */
			::VkExtent2D _extent;

			/* logical device */
			::VkDevice _device;

	}; // class swapchain

} // namespace vulkan

#endif // ENGINE_VULKAN_SWAPCHAIN_HPP
