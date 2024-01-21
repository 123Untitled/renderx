#include "vulkan_swapchain.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::swapchain::swapchain(void) noexcept
: _swapchain{VK_NULL_HANDLE} {}

/* logical device and surface constructor */
vulkan::swapchain::swapchain(const vulkan::physical_device& pdevice,
							 const vulkan::logical_device& device,
							 const vulkan::surface& surface)
: _swapchain{VK_NULL_HANDLE},
  _images{},
  _format{},
  _extent{},
  _device{device} {

	  return;


	// get surface capabilities
	auto capabilities = pdevice.surface_capabilities(surface);
	// get surface formats
	auto formats = pdevice.surface_formats(surface);
	// get surface modes
	auto modes = pdevice.surface_present_modes(surface);
	// get surface extent




	const vk::swapchain_info info{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.surface = surface,
	//info.minImageCount = capabilities.min_image_count() + 1; // for triple buffering
	//info.imageFormat = format.format; // not implemented
	//info.imageColorSpace = format.colorSpace; // not implemented
	//info.imageExtent = extent; // not implemented
		// for stereoscopic 3D applications
		.imageArrayLayers = 1,
		// see later for post-processing
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, /* VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing */
		// not implemented !!!
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		// not implemented !!!
		.queueFamilyIndexCount = 0,
		// not implemented !!!
		.pQueueFamilyIndices = nullptr,


		//info.preTransform = capabilities.current_transform(); // need to read tutorial
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, // for blending with other windows
															 //info.presentMode = mode; // not implemented
		.clipped = VK_TRUE, // not implemented
		.oldSwapchain = nullptr  // for resizing window, see later...
	};

	_swapchain = vk::create_swapchain(device, info);

	::uint32_t count = 0;
	::vkGetSwapchainImagesKHR(device, _swapchain, &count, nullptr);
	_images.resize(count);
	::vkGetSwapchainImagesKHR(device, _swapchain, &count, _images.data());
}





// -- public accessors --------------------------------------------------------

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

/* destroy */
auto vulkan::swapchain::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_swapchain == VK_NULL_HANDLE)
		return;
	vk::destroy_swapchain(device, _swapchain);
	//_swapchain = VK_NULL_HANDLE; // already done by vk::destroy_swapchain
}


// -- private static methods --------------------------------------------------


/* create swapchain info */
auto vulkan::swapchain::create_swapchain_info(const ::VkSurfaceCapabilitiesKHR& capabilities,
											  const ::VkSurfaceFormatKHR& format,
											  const ::VkExtent2D& extent,
											  const ::VkPresentModeKHR& mode) noexcept -> ::VkSwapchainCreateInfoKHR {
	// return swapchain info
	return ::VkSwapchainCreateInfoKHR{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.surface = nullptr,
		.minImageCount = capabilities.minImageCount,
		.imageFormat = format.format,
		.imageColorSpace = format.colorSpace,
		.imageExtent = extent,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
		.preTransform = capabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = mode,
		.clipped = VK_TRUE,
		.oldSwapchain = nullptr
	};
}


