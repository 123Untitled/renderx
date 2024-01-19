#include "vulkan_swapchain.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::swapchain::swapchain(void) noexcept
: _swapchain{nullptr}, _device{nullptr} {}

/* logical device and surface constructor */
vulkan::swapchain::swapchain(const vulkan::logical_device& device,
							 const vulkan::surface& surface,
							 const ::VkSurfaceCapabilitiesKHR& capabilities,
							 const ::VkSurfaceFormatKHR& format,
							 const ::VkPresentModeKHR& mode,
							 const ::VkExtent2D& extent)
: _swapchain{nullptr},
  _images{},
  _format{format},
  _extent{extent},
  _device{device.underlying()} {

	::VkSwapchainCreateInfoKHR info{};
	info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info.pNext = nullptr;
	info.flags = 0;
	info.surface = surface.underlying();
	info.minImageCount = capabilities.minImageCount + 1;
	info.imageFormat = format.format; // not implemented
	info.imageColorSpace = format.colorSpace; // not implemented
	info.imageExtent = extent; // not implemented
	info.imageArrayLayers = 1; // for stereoscopic 3D applications
	info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // see later for post-processing
	/* VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing */
	info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // not implemented !!!
	info.queueFamilyIndexCount = 0; // not implemented !!!
	info.pQueueFamilyIndices = nullptr; // not implemented !!!
	info.preTransform = capabilities.currentTransform; // need to read tutorial
	info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // for blending with other windows
	info.presentMode = mode; // not implemented
	info.clipped = VK_TRUE; // not implemented
	info.oldSwapchain = nullptr; // for resizing window, see later...

	_swapchain = self::create_swapchain(device, info);

	::uint32_t count = 0;
	::vkGetSwapchainImagesKHR(device.underlying(), _swapchain, &count, nullptr);
	_images.resize(count);
	::vkGetSwapchainImagesKHR(device.underlying(), _swapchain, &count, _images.data());
}

/* move constructor */
vulkan::swapchain::swapchain(self&& other) noexcept
: _swapchain{other._swapchain} {
	other.init();
}

/* destructor */
vulkan::swapchain::~swapchain(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::swapchain::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	_swapchain = other._swapchain;
	   _device = other._device;
	other.init();
	return *this;
}


// -- private static methods --------------------------------------------------

/* create swapchain */
auto vulkan::swapchain::create_swapchain(const vulkan::logical_device& device,
										 const ::VkSwapchainCreateInfoKHR& info) -> ::VkSwapchainKHR {
	// create swapchain
	::VkSwapchainKHR swapchain{nullptr};
	if (::vkCreateSwapchainKHR(device.underlying(), &info, nullptr, &swapchain) != VK_SUCCESS)
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


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::swapchain::free(void) noexcept -> void {
	if (_swapchain == nullptr)
		return;
	::vkDestroySwapchainKHR(_device, _swapchain, nullptr);
}

/* init */
auto vulkan::swapchain::init(void) noexcept -> void {
	_swapchain = nullptr;
	   _device = nullptr;
}

