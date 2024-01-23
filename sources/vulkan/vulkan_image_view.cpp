#include "vulkan_image_view.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::image_view::image_view(const vulkan::logical_device& device,
							   const vk::image& image,
							   const vk::format& format)
// create image view
: _view{vk::create_image_view(device, vk::image_view_info{
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
	})} {
}

/* copy constructor */
vulkan::image_view::image_view(const self& other) noexcept
: _view{other._view} {}

/* move constructor */
vulkan::image_view::image_view(self&& other) noexcept
: self{other} /* copy */ {}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::image_view::operator=(const self& other) noexcept -> self& {
	_view = other._view;
	return *this;
}

/* move assignment operator */
auto vulkan::image_view::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public conversion operators ---------------------------------------------

/* vk::image_view conversion operator */
vulkan::image_view::operator const vk::image_view&() const noexcept {
	return _view;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::image_view::destroy(const vulkan::logical_device& device) noexcept -> void {
	vk::destroy_image_view(device, _view);
}

