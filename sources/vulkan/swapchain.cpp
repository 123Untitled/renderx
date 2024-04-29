#include "engine/vulkan/swapchain.hpp"

//#include <xns/math.hpp>
#include <xns/math/clamp.hpp>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
//vulkan::swapchain::swapchain(void) noexcept
//: _swapchain{}, _images{}, _views{}, _format{}, _extent{} {
//}

/* logical device and surface constructor */
vulkan::swapchain::swapchain(const vulkan::device& device,
							 const vulkan::surface& surface)
: _swapchain{}, _render_pass{device}, _images{}, _views{device}, _frames{device}, _format{}, _extent{} {

	const auto& pdevice = device.physical_device();

	// pick surface format
	_format                 = self::pick_surface_format(pdevice.surface_formats(surface));
	// pick present mode
	const auto mode         = self::pick_present_mode(pdevice.surface_present_modes(surface));
	// get capabilities
	const auto capabilities = pdevice.surface_capabilities(surface);
	// pick extent
	_extent                 = self::pick_extent(capabilities);


	// +1 for triple buffering
	vk::u32 count = pdevice.surface_capabilities(surface).minImageCount + 1;

	// check for max image count
	if (capabilities.maxImageCount > 0 && count > capabilities.maxImageCount)
		count = capabilities.maxImageCount;

	// create swapchain with info
	_swapchain = {device, vk::swapchain_info{
		// structure type
		.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		// next structure
		.pNext                 = VK_NULL_HANDLE,
		// flags (none)
		.flags                 = 0U,
		// surface
		.surface               = surface,
		// min image count
		.minImageCount         = count,
		// image format
		.imageFormat           = _format.format,
		// image color space
		.imageColorSpace       = _format.colorSpace,
		// image extent
		.imageExtent           = _extent,

		// for stereoscopic 3D applications
		.imageArrayLayers      = 1,
		// for post-processing
		.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, /* see 'vk::image_usage_flags_bits' */
		// image sharing mode
		.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE, /* VK_SHARING_MODE_CONCURRENT */
		// number of queue families
		.queueFamilyIndexCount = 1U,
		// queue family indices
		.pQueueFamilyIndices   = &device.family(),


		// ...
		.preTransform = capabilities.currentTransform, // need to read tutorial
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, // for blending with other windows

		.presentMode = mode, // for vsync, etc...
		
															 //info.presentMode = mode; // not implemented
		.clipped = VK_TRUE, // not implemented
		.oldSwapchain = nullptr  // for resizing window, see later...
	}};



	// get swapchain images
	_images = vk::get_swapchain_images(device, _swapchain);


	{
		vk::image_view_info info {
			.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext      = VK_NULL_HANDLE,
			.flags      = 0U,
			.image      = VK_NULL_HANDLE,
			.viewType   = VK_IMAGE_VIEW_TYPE_2D,
			.format     = _format.format,
			.components = {
				.r = VK_COMPONENT_SWIZZLE_IDENTITY,
				.g = VK_COMPONENT_SWIZZLE_IDENTITY,
				.b = VK_COMPONENT_SWIZZLE_IDENTITY,
				.a = VK_COMPONENT_SWIZZLE_IDENTITY,
			},
			.subresourceRange   = {
				.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel   = 0U,
				.levelCount     = 1U,
				.baseArrayLayer = 0U,
				.layerCount     = 1U,
			}
		};

		_views.reserve((vk::u32)_images.size());

		for (vk::u32 i = 0; i < _images.size(); ++i) {
			// fill info with image
			info.image = _images[i];
			// create image view
			_views.emplace_back(info);
		}

	}



	{

		// create framebuffers
		_frames.reserve(_views.size());


		vk::framebuffer_info info {
			// structure type
			.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			// next structure
			.pNext           = VK_NULL_HANDLE,
			// flags (none)
			.flags           = 0U,
			// render pass
			.renderPass      = _render_pass,
			// attachment count (swapchain image views)
			.attachmentCount = 1U,
			// attachments (swapchain image views)
			.pAttachments    = VK_NULL_HANDLE,
			// width
			.width           = _extent.width,
			// height
			.height          = _extent.height,
			// layers
			.layers          = 1
		};

		for (vk::u32 i = 0; i < _views.size(); ++i) {
			// fill info with image view
			info.pAttachments = &_views[i];
			// create framebuffer
			_frames.emplace_back(info);
		}

	}


}

/* destructor */
vulkan::swapchain::~swapchain(void) noexcept {
	// wait for logical device to be idle
	vk::device_wait_idle(_swapchain.dependency());
}


// -- public assignment operators ---------------------------------------------

// THIS CLASS NEED TO BE HANDLE MOVE OR COPY (IMAGES, IMAGE VIEWS, ETC...)




// -- public accessors --------------------------------------------------------

/* size */
auto vulkan::swapchain::size(void) const noexcept -> vk::u32 {
	return (vk::u32)_images.size();
}

/* extent */
auto vulkan::swapchain::extent(void) const noexcept -> vk::extent2D {
	return _extent;
}

/* image views size */
auto vulkan::swapchain::image_views_size(void) const noexcept -> vk::u32 {
	return _views.size();
}

/* image views data */
auto vulkan::swapchain::image_views_data(void) const noexcept -> const vk::image_view* {
	return _views.data();
}

/* frames */
auto vulkan::swapchain::frames(void) const noexcept -> const vk::vvector<vk::framebuffer>& {
	return _frames;
}

/* render pass */
auto vulkan::swapchain::render_pass(void) const noexcept -> const vulkan::render_pass& {
	return _render_pass;
}

/* acquire next image */
auto vulkan::swapchain::acquire_next_image(const vulkan::semaphore& semaphore,
										   xns::u32& img_index) const noexcept -> bool {

	// get image index
	if (::vkAcquireNextImageKHR(_swapchain.dependency(),
								_swapchain,
								UINT64_MAX /* timeout */,
								semaphore,
								nullptr /* fence */,
								&img_index) != VK_SUCCESS) {
		std::cout << "failed to acquire swapchain image" << std::endl;
		// here error not means program must stop
		return false;
	}
	return true;
}


// -- public conversion operators ---------------------------------------------

/* vk::swapchain conversion operator */
vulkan::swapchain::operator const vk::swapchain&(void) const noexcept {
	return _swapchain;
}


// -- public modifiers --------------------------------------------------------

/* re-create */
auto vulkan::swapchain::recreate(const vulkan::device& device,
								 const vulkan::surface& surface) -> void {

	// destroy !!!
	// wait for logical device to be idle
	vk::device_wait_idle(_swapchain.dependency());

	_views.clear();


	const auto& pdevice = device.physical_device();

	// pick surface format
	_format         = self::pick_surface_format(pdevice.surface_formats(surface));
	// pick present mode
	const auto mode = self::pick_present_mode(pdevice.surface_present_modes(surface));
	// get capabilities
	const auto capabilities = pdevice.surface_capabilities(surface);
	// pick extent
	_extent         = self::pick_extent(capabilities);

}


// -- private static methods --------------------------------------------------

/* pick surface format */
auto vulkan::swapchain::pick_surface_format(const vk::vector<vk::surface_format>& formats) noexcept -> vk::surface_format {
	// if only one format and undefined format
	if (formats.empty() || (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED))
		// maybe throw an exception ?
		return vk::surface_format{VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	// loop over formats
	for (const auto& format : formats)
		// check for best format
		if (format.format     == VK_FORMAT_B8G8R8A8_SRGB
		 && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			return format;
	// else return first format
	return formats[0];

}

/* pick present mode */
auto vulkan::swapchain::pick_present_mode(const vk::vector<vk::present_mode>& modes) noexcept -> vk::present_mode {

	// VK_PRESENT_MODE_IMMEDIATE_KHR
	// VK_PRESENT_MODE_FIFO_KHR (always available)
	// VK_PRESENT_MODE_FIFO_RELAXED_KHR
	// VK_PRESENT_MODE_MAILBOX_KHR

	// loop over modes
	for (const auto& mode : modes)
		// check for best mode
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			return mode;
	// else return FIFO mode
	return VK_PRESENT_MODE_FIFO_KHR;
}

/* pick extent */
auto vulkan::swapchain::pick_extent(const vk::surface_capabilities& capabilities) noexcept -> vk::extent2D {

	if (capabilities.currentExtent.width != UINT32_MAX)
		return capabilities.currentExtent;

	vk::extent2D extent{800, 600}; // will be replaced by window size

	extent.width  = xns::clamp(extent.width,
			capabilities.minImageExtent.width,
			capabilities.maxImageExtent.width);
	extent.height = xns::clamp(extent.height,
			capabilities.minImageExtent.height,
			capabilities.maxImageExtent.height);

	return extent;
}
