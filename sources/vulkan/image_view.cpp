#include "ve/vulkan/image_view.hpp"


// -- I M A G E  V I E W ------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* parameter constructor */
ve::image_view::image_view(const vk::image& image,
						   const vk::format& format,
						   const vk::image_aspect_flags& aspect)
: _view{ve::image_view::_create_image_view(image, format, aspect)} {

	/* VK_IMAGE_ASPECT_COLOR_BIT */
}


// -- public conversion operators ---------------------------------------------

/* const vk::image_view& conversion operator */
ve::image_view::operator const vk::image_view&(void) const noexcept {
	return _view.get();
}


// -- private static methods --------------------------------------------------

/* create image view */
auto ve::image_view::_create_image_view(const vk::image& image,
										const vk::format& format,
										const vk::image_aspect_flags& aspect
										) -> vk::unique<vk::image_view> {

	// create info
	const vk::image_view_info info{
		// structure type
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		// next structure
		.pNext = nullptr,
		// flags
		.flags = 0U,
		// image
		.image = image,
		// view type
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		// format
		.format = format,
		// components
		.components = {
			.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.a = VK_COMPONENT_SWIZZLE_IDENTITY
		},
		// subresource range
		.subresourceRange = {
			.aspectMask = aspect,
			.baseMipLevel = 0U,
			.levelCount = 1U,
			.baseArrayLayer = 0U,
			.layerCount = 1U
		}
	};

	// create image view
	return vk::make_unique<vk::image_view>(info);
}
