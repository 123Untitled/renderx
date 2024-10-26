#include "ve/vulkan/swapchain.hpp"
#include "ve/vk/utils.hpp"

#include <iostream>
#include "ve/vk/info.hpp"
#include "ve/surface_formats.hpp"

#include "ve/glfw/window.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::swapchain::swapchain(void) noexcept
: _swapchain{}, _size{0U}, _extent{} {
}

/* parameters constructor */
vulkan::swapchain::swapchain(const vk::u32& size,
							 const vk::surface_format& format,
							 const vk::extent2D& extent,
							 const vk::surface_capabilities& capabilities,
							 const vk::present_mode& mode)
: _swapchain{}, _size{size}, _extent{extent} {

	// create info
	const vk::swapchain_info info {
		// structure type
		.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		// next structure
		.pNext                 = nullptr,
		// flags (none)
		.flags                 = 0U,
		// surface
		.surface               = vulkan::surface::shared(),
		// min image count
		.minImageCount         = size,
		// image format
		.imageFormat           = format.format,
		// image color space
		.imageColorSpace       = format.colorSpace,
		// image extent
		.imageExtent           = extent,
		// for stereoscopic 3D applications
		.imageArrayLayers      = 1U,
		// for post-processing see (vk::image_usage_flags_bits)
		.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		// image sharing mode (VK_SHARING_MODE_CONCURRENT)
		.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
		// number of queue families
		.queueFamilyIndexCount = 1U,
		// queue family indices
		.pQueueFamilyIndices   = &(vulkan::device::family()),
		// pre-transform (read tutorial !)
		.preTransform = capabilities.currentTransform,
		// composite alpha (for blending with other windows)
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		// present mode (vsync, etc...)
		.presentMode = mode,
		// clipped (not implemented)
		.clipped = VK_TRUE,
		// old swapchain (for resizing)
		.oldSwapchain = nullptr
	};

	// create swapchain
	_swapchain = vk::make_unique<vk::swapchain>(info);
}


// -- public accessors --------------------------------------------------------

/* acquire next image */
auto vulkan::swapchain::acquire_next_image(const vk::semaphore& semaphore,
												 vk::u32& img_index) const -> vk::result {

	// acquire next image
	const vk::result status = ::vk_acquire_next_image_khr(vulkan::device::logical(),
														  _swapchain,
														  UINT64_MAX /* timeout */,
														  semaphore,
														  nullptr /* fence */,
														  &img_index);

	return status;

	switch (status) {

		case VK_SUCCESS:
			return status;

		case VK_SUBOPTIMAL_KHR:
			// means swapchain is not optimal but still usable
			return status;

		case VK_ERROR_OUT_OF_DATE_KHR:
			// recreate swapchain
			break;

		//case VK_TIMEOUT:
		//	break;
		//
		//case VK_NOT_READY:
		//	break;
		//
		//case VK_ERROR_OUT_OF_HOST_MEMORY:
		//	break;
		//
		//case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		//	break;
		//
		//case VK_ERROR_DEVICE_LOST:
		//	break;
		//
		//case VK_ERROR_SURFACE_LOST_KHR:
		//	break;
		//
		//case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
		//	break;

		default:
			throw vk::exception("failed to acquire next image", status);
	}

	return status;


	/* On success, this command returns
		- VK_SUCCESS
		- VK_TIMEOUT
		- VK_NOT_READY
		- VK_SUBOPTIMAL_KHR */

	/* On failure, this command returns
		- VK_ERROR_OUT_OF_HOST_MEMORY
		- VK_ERROR_OUT_OF_DEVICE_MEMORY
		- VK_ERROR_DEVICE_LOST
		- VK_ERROR_OUT_OF_DATE_KHR
		- VK_ERROR_SURFACE_LOST_KHR
		- VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT */
}




// -- public modifiers --------------------------------------------------------

auto vulkan::swapchain::recreate(const vk::u32& size,
								 const vk::surface_format& format,
								 const vk::extent2D& extent,
								 const vk::surface_capabilities& capabilities,
								 const vk::present_mode& mode) -> void {

	_extent = extent;
	_size = size;

	const vk::swapchain old{_swapchain.release()};

	// create info
	const vk::swapchain_info info {
		// structure type
		.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		// next structure
		.pNext                 = nullptr,
		// flags (none)
		.flags                 = 0U,
		// surface
		.surface               = vulkan::surface::shared(),
		// min image count
		.minImageCount         = size,
		// image format
		.imageFormat           = format.format,
		// image color space
		.imageColorSpace       = format.colorSpace,
		// image extent
		.imageExtent           = extent,
		// for stereoscopic 3D applications
		.imageArrayLayers      = 1U,
		// for post-processing see (vk::image_usage_flags_bits)
		.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		// image sharing mode (VK_SHARING_MODE_CONCURRENT)
		.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
		// number of queue families
		.queueFamilyIndexCount = 1U,
		// queue family indices
		.pQueueFamilyIndices   = &(vulkan::device::family()),
		// pre-transform (read tutorial !)
		.preTransform = capabilities.currentTransform,
		// composite alpha (for blending with other windows)
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		// present mode (vsync, etc...)
		.presentMode = mode,
		// clipped (not implemented)
		.clipped = VK_TRUE,
		// old swapchain (for resizing)
		.oldSwapchain = old
	};

	// create swapchain
	_swapchain = vk::make_unique<vk::swapchain>(info);

	// destroy old swapchain (assuming it is not null)
	vk::destroy(old);
}
