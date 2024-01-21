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
	auto capabilities = pdevice.capabilities(surface);
	// get surface formats
	auto formats = pdevice.formats(surface);
	// get surface modes
	auto modes = pdevice.present_modes(surface);
	// get surface extent




	::VkSwapchainCreateInfoKHR info{};
	info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info.pNext = nullptr;
	info.flags = 0;
	info.surface = surface;
	info.minImageCount = capabilities.min_image_count() + 1; // for triple buffering
	//info.imageFormat = format.format; // not implemented
	//info.imageColorSpace = format.colorSpace; // not implemented
	//info.imageExtent = extent; // not implemented
	info.imageArrayLayers = 1; // for stereoscopic 3D applications
	info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // see later for post-processing
	/* VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing */


	// not implemented !!!
	info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	// not implemented !!!
	info.queueFamilyIndexCount = 0;
	// not implemented !!!
	info.pQueueFamilyIndices = nullptr;


	info.preTransform = capabilities.current_transform(); // need to read tutorial
	info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // for blending with other windows
	//info.presentMode = mode; // not implemented
	info.clipped = VK_TRUE; // not implemented
	info.oldSwapchain = nullptr; // for resizing window, see later...

	_swapchain = self::create_swapchain(device, info);

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

/* VkSwapchainKHR conversion operator */
vulkan::swapchain::operator const ::VkSwapchainKHR&(void) const noexcept {
	return _swapchain;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::swapchain::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_swapchain == VK_NULL_HANDLE)
		return;
	::vkDestroySwapchainKHR(_device, _swapchain, nullptr);
	_swapchain = VK_NULL_HANDLE;
}


// -- private static methods --------------------------------------------------

/* create swapchain */
auto vulkan::swapchain::create_swapchain(const vulkan::logical_device& device,
										 const ::VkSwapchainCreateInfoKHR& info) -> ::VkSwapchainKHR {
	// create swapchain
	::VkSwapchainKHR swapchain{nullptr};
	if (::vkCreateSwapchainKHR(device, &info, nullptr, &swapchain) != VK_SUCCESS)
		throw engine::exception{"failed to create swapchain"};
	// return swapchain
	return swapchain;
}

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


