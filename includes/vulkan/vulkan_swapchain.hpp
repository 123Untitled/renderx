#ifndef ENGINE_VULKAN_SWAPCHAIN_HPP
#define ENGINE_VULKAN_SWAPCHAIN_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"
#include "vulkan_image_view.hpp"
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
					  const vulkan::shared_device&,
					  const vulkan::surface&);

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


			// -- public accessors --------------------------------------------

			/* extent */
			auto extent(void) const noexcept -> vk::extent2D;

			/* image views size */
			auto image_views_size(void) const noexcept -> vk::u32;

			/* image views data */
			auto image_views_data(void) const noexcept -> const vk::image_view*;


			/* acquire next image */
			auto acquire_next_image(const vulkan::logical_device&,
									const vulkan::semaphore&,
									xns::u32&) const noexcept -> bool;


			// -- public conversion operators ---------------------------------

			/* vk::swapchain conversion operator */
			operator const vk::swapchain&(void) const noexcept;


			// -- public modifiers --------------------------------------------

			/* re-create */
			auto recreate(const vulkan::physical_device&,
						  const vulkan::surface&) -> void;


		private:

			// -- private static methods --------------------------------------

			/* pick surface format */
			static auto pick_surface_format(const vk::vector<vk::surface_format>&) noexcept -> vk::surface_format;

			/* pick present mode */
			static auto pick_present_mode(const vk::vector<vk::present_mode>&) noexcept -> vk::present_mode;

			/* pick extent */
			static auto pick_extent(const vk::surface_capabilities&) noexcept -> vk::extent2D;



			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;



			// -- private members ---------------------------------------------

			/* swapchain */
			vk::swapchain _swapchain;

			/* logical device */
			vulkan::shared_device _device;

			/* images */
			vk::vector<vk::image> _images;

			/* image views */
			vk::vector<vulkan::image_view> _views;

			/* format */
			vk::surface_format _format;

			/* extent */
			vk::extent2D _extent;


	}; // class swapchain

} // namespace vulkan

#endif // ENGINE_VULKAN_SWAPCHAIN_HPP
