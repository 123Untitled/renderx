#include "ve/vulkan/swapchain_manager.hpp"
#include "ve/surface_formats.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::swapchain_manager::swapchain_manager(void)
:

  _format{vulkan::surface_formats{}.find(VK_FORMAT_B8G8R8A8_SRGB,
										 VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)},

  _capabilities{vulkan::device::physical().surface_capabilities()},

  _extent{___self::_pick_extent(_capabilities)},

  _mode{___self::_pick_mode()},

  _size{___self::_pick_count(_capabilities)},

  _render_pass{},
  _swapchain{_size, _format, _extent, _capabilities, _mode},
  _images{_swapchain},
  _views{_images, _format.format},
  _multisampling{_extent},
  _depth_buffer{_extent},
  _frames{_views, _multisampling, _depth_buffer, _render_pass, _extent} {
}


// -- public modifiers --------------------------------------------------------

/* recreate */
auto vulkan::swapchain_manager::recreate(void) -> void {

	// get new window size
	vk::extent2D extent = glfw::window::framebuffer_size();

	// handle window minimization
	while (extent.width == 0U || extent.height == 0U) {

		// get new window size
		extent = glfw::window::framebuffer_size();

		std::cout << "waiting for window to restore" << std::endl;

		// wait for events
		glfw::events::wait();
	}

	// wait for device to terminate operations
	vulkan::device::wait_idle();


	_extent = extent;


	// recreate swapchain and related objects
	_swapchain.recreate(_size, _format, _extent, _capabilities, _mode);
	   _images.recreate(_swapchain);
	    _views.recreate(_images, _format.format);
	   _frames.recreate(_views, _multisampling, _depth_buffer, _render_pass, _extent);

	//_frames = vulkan::framebuffers{_views, _render_pass, _extent};
}




/* pick mode */
auto vulkan::swapchain_manager::_pick_mode(void) noexcept -> vk::present_mode {

	const auto modes = vulkan::device::physical().surface_present_modes();

	// VK_PRESENT_MODE_IMMEDIATE_KHR
	// VK_PRESENT_MODE_FIFO_KHR (always available)
	// VK_PRESENT_MODE_FIFO_RELAXED_KHR
	// VK_PRESENT_MODE_MAILBOX_KHR
    // VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR
    // VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR

	//return VK_PRESENT_MODE_IMMEDIATE_KHR;
	//return VK_PRESENT_MODE_MAILBOX_KHR;

	// loop over modes
	for (const auto& mode : modes) {

		// check for best mode

		// immediate mode (no vsync, tearing)
		if (mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			std::cout << "immediate mode" << std::endl;

		// fifo mode (vsync, wait for display)
		if (mode == VK_PRESENT_MODE_FIFO_KHR)
			std::cout << "fifo mode" << std::endl;
		return mode;

		// fifo relaxed mode (vsync, but if late, display last image)
		if (mode == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
			std::cout << "fifo relaxed mode" << std::endl;

		// mailbox mode (vsync, but if late, display last image)
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
			std::cout << "mailbox mode" << std::endl;
			return mode;
		}

		if (mode == VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR)
			std::cout << "shared demand refresh mode" << std::endl;

		if (mode == VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR)
			std::cout << "shared continuous refresh mode" << std::endl;

	}

	// else return FIFO mode
	return VK_PRESENT_MODE_FIFO_KHR;
}

/* pick extent */
auto vulkan::swapchain_manager::_pick_extent(const vk::surface_capabilities& caps) noexcept -> vk::extent2D {

	// check for current extent
	if (caps.currentExtent.width != UINT32_MAX)
		return caps.currentExtent;

	// get framebuffer size
	vk::extent2D extent = glfw::window::framebuffer_size();

	// clamp width extent
	extent.width = extent.width > caps.maxImageExtent.width ?
			caps.maxImageExtent.width : (extent.width < caps.minImageExtent.width ?
					caps.minImageExtent.width : extent.width);

	// clamp height extent
	extent.height = extent.height > caps.maxImageExtent.height ?
			caps.maxImageExtent.height : (extent.height < caps.minImageExtent.height ?
					caps.minImageExtent.height : extent.height);

	// done
	return extent;
}

/* pick count */
auto vulkan::swapchain_manager::_pick_count(const vk::surface_capabilities& capabilities) noexcept -> vk::u32 {

	// more images: more buffering, less tearing, more input lag
	// less images: less buffering, more tearing, less input lag

	return capabilities.minImageCount;

	// +1 for triple buffering
	vk::u32 count = capabilities.minImageCount + 1U;

	// check for max image count
	if (capabilities.maxImageCount > 0U && count > capabilities.maxImageCount)
		count = capabilities.maxImageCount;

	return count;
}
