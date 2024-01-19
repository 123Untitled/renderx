#include "vulkan_image_view.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::image_view::image_view(const vulkan::logical_device& device,
									::VkImage& image,
									::VkFormat& format)
: _view{nullptr}, _device{device.underlying()} {
	// create image view info
	auto info = self::create_image_view_info(image, format);
	// create image view
	_view = self::create_image_view(device, info);
}

/* move constructor */
vulkan::image_view::image_view(self&& other) noexcept
: _view{other._view}, _device{other._device} {
	other.init();
}

/* destructor */
vulkan::image_view::~image_view(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::image_view::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	  _view = other._view;
	_device = other._device;
	other.init();
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::image_view::underlying(void) noexcept -> ::VkImageView& {
	return _view;
}

/* const underlying */
auto vulkan::image_view::underlying(void) const noexcept -> const ::VkImageView& {
	return _view;
}


// -- private static methods --------------------------------------------------

/* create image view */
auto vulkan::image_view::create_image_view(const vulkan::logical_device& device,
										   const ::VkImageViewCreateInfo& info) -> ::VkImageView {
	::VkImageView view;
	// create image view
	if (::vkCreateImageView(device.underlying(), &info, nullptr, &view) != VK_SUCCESS)
		throw engine::exception{"failed to create image view"};
	return view;
}

/* create image view info */
auto vulkan::image_view::create_image_view_info(::VkImage& image,
												::VkFormat& format) noexcept -> ::VkImageViewCreateInfo {
	return ::VkImageViewCreateInfo{
		.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext      = nullptr,
		.flags      = 0,
		.image      = image,
		.viewType   = VK_IMAGE_VIEW_TYPE_2D,
		.format     = format,
		.components = {
			.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.a = VK_COMPONENT_SWIZZLE_IDENTITY,
		},
		.subresourceRange   = {
			.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel   = 0,
			.levelCount     = 1,
			.baseArrayLayer = 0,
			.layerCount     = 1,
		}
	};
}


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::image_view::free(void) noexcept -> void {
	if (_view == nullptr)
		return;
	::vkDestroyImageView(_device, _view, nullptr);
}

/* init */
auto vulkan::image_view::init(void) noexcept -> void {
	  _view = VK_NULL_HANDLE;
	_device = VK_NULL_HANDLE;
}
