#ifndef ENGINE_VULKAN_SWAPCHAIN_HPP
#define ENGINE_VULKAN_SWAPCHAIN_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"
#include "vulkan_semaphore.hpp"

#include <xns>

#include "vk_typedefs.hpp"


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
			swapchain(const vulkan::physical_device&,
					  const vulkan::logical_device&,
					  const vulkan::surface&);

			/* deleted copy constructor */
			swapchain(const self&) = delete;

			/* deleted move constructor */
			swapchain(self&&) noexcept = delete;

			/* destructor */
			~swapchain(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public accessors --------------------------------------------

			/* acquire next image */
			auto acquire_next_image(const vulkan::logical_device&,
									const vulkan::semaphore&,
									xns::u32&) const noexcept -> bool;


			// -- public conversion operators ---------------------------------

			/* vk::swapchain conversion operator */
			operator const vk::swapchain&(void) const noexcept;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


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






			// -- private members ---------------------------------------------

			/* swapchain */
			vk::swapchain _swapchain;

			/* images */
			vk::vector<vk::image> _images;

			/* format */
			vk::format _format;

			/* extent */
			vk::extent2D _extent;

			/* logical device */
			vk::device _device;

	}; // class swapchain

} // namespace vulkan

#endif // ENGINE_VULKAN_SWAPCHAIN_HPP
