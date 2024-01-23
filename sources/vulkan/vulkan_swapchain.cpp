#include "vulkan_swapchain.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::swapchain::swapchain(void) noexcept
: _swapchain{VK_NULL_HANDLE},
  _device{},
  _images{},
  _views{},
  _format{},
  _extent{} {
}

/* logical device and surface constructor */
vulkan::swapchain::swapchain(const vulkan::physical_device& pdevice,
							 const vulkan::shared_device& device,
							 const vulkan::surface& surface)
: _swapchain{VK_NULL_HANDLE},
  _device{device},
  _images{},
  _views{},
  _format{},
  _extent{} {


	// pick surface format
	_format         = self::pick_surface_format(pdevice.surface_formats(surface));
	// pick present mode
	const auto mode = self::pick_present_mode(pdevice.surface_present_modes(surface));
	// get capabilities
	const auto capabilities = pdevice.surface_capabilities(surface);
	// pick extent
	_extent         = self::pick_extent(capabilities);


	// +1 for triple buffering
	vk::u32 count = pdevice.surface_capabilities(surface).minImageCount + 1;
	// check for max image count
	if (capabilities.maxImageCount > 0 && count > capabilities.maxImageCount)
		count = capabilities.maxImageCount;

	// create swapchain with info
	_swapchain = vk::create_swapchain(*_device, vk::swapchain_info{
		.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext                 = nullptr,
		.flags                 = 0,

		.surface               = surface,
		.minImageCount         = count,
		.imageFormat           = _format.format,
		.imageColorSpace       = _format.colorSpace,
		.imageExtent           = _extent,

		// for stereoscopic 3D applications
		.imageArrayLayers      = 1,
		// see later for post-processing
		.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		// not implemented !!!
		.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
		// not implemented !!!
		.queueFamilyIndexCount = 0,
		// not implemented !!!
		.pQueueFamilyIndices   = nullptr,


		.preTransform = capabilities.currentTransform, // need to read tutorial
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, // for blending with other windows
															 //info.presentMode = mode; // not implemented
		.clipped = VK_TRUE, // not implemented
		.oldSwapchain = nullptr  // for resizing window, see later...
	});

	// get swapchain images
	_images = vk::get_swapchain_images(*_device, _swapchain);

	for (const auto& image : _images)
		_views.emplace_back(*_device, image, _format.format);

}

/* move constructor */
vulkan::swapchain::swapchain(self&& other) noexcept
: _swapchain{other._swapchain},
  _device{xns::move(other._device)},
  _images{xns::move(other._images)},
  _views{xns::move(other._views)},
  _format{other._format},
  _extent{other._extent} {
}

/* destructor */
vulkan::swapchain::~swapchain(void) noexcept {
	this->free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::swapchain::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	_swapchain   = other._swapchain;
	_device      = xns::move(other._device);
	_images      = xns::move(other._images);
	_views       = xns::move(other._views);
	_format      = other._format;
	_extent      = other._extent;
	return *this;
}



// -- public accessors --------------------------------------------------------

/* extent */
auto vulkan::swapchain::extent(void) const noexcept -> vk::extent2D {
	return _extent;
}

/* image views size */
auto vulkan::swapchain::image_views_size(void) const noexcept -> vk::u32 {
	return static_cast<vk::u32>(_views.size());
}

/* image views data */
auto vulkan::swapchain::image_views_data(void) const noexcept -> const vk::image_view* {
	return reinterpret_cast<const vk::image_view*>(_views.data());
}

/* acquire next image */
auto vulkan::swapchain::acquire_next_image(const vulkan::logical_device& device,
										   const vulkan::semaphore& semaphore,
										   xns::u32& img_index) const noexcept -> bool {
	// get image index
	if (::vkAcquireNextImageKHR(device, _swapchain,
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
auto vulkan::swapchain::recreate(const vulkan::physical_device& pdevice,
								 const vulkan::surface& surface) -> void {

	// destroy
	this->free();

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



// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::swapchain::free(void) noexcept -> void {
	if (_swapchain == VK_NULL_HANDLE)
		return;
	// wait for logical device to be idle
	_device->wait_idle();
	// loop over image views
	for (auto& view : _views)
		// destroy image view
		view.destroy(*_device);
	// destroy swapchain
	vk::destroy_swapchain(*_device, _swapchain);
}
