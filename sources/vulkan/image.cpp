#include "ve/vulkan/image.hpp"


// -- I M A G E ---------------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

ve::image::image(const vk::u32& width,
				 const vk::u32& height,
				 const vk::format& format,
				 const vk::sample_count_flag_bits& samples,
				 const vk::image_tiling& tiling,
				 const vk::image_usage_flags& usage,
				 const vk::image_layout& layout,
				 const vk::memory_property_flags& properties)

// create image
: _image{___self::_create_image(width, height, format, samples, tiling, usage)},
// allocate memory
  _alloc{vulkan::allocator<vulkan::gpu_memory>::allocate_image(_image.get())} {
}


// -- public conversion operators ---------------------------------------------

// const vk::image& conversion operator
ve::image::operator const vk::image&(void) const noexcept {
	return _image.get();
}


// -- private static methods --------------------------------------

/* create image */
auto ve::image::_create_image(const vk::u32& width,
							  const vk::u32& height,
							  const vk::format& format,
							  const vk::sample_count_flag_bits& samples,
							  const vk::image_tiling& tiling,
							  const vk::image_usage_flags& usage,
							  const vk::image_layout& layout
							  ) -> vk::unique<vk::image> {

	// create info
	const vk::image_info info {
		// structure type
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		// next structure
		.pNext = nullptr,
		// flags
		.flags = 0U,
		// image type
		.imageType = VK_IMAGE_TYPE_2D,
		// format
		.format = format,
		// extent 3D
		.extent {
			.width = width,
			.height = height,
			.depth = 1
		},
		// mip levels
		.mipLevels = 1,
		// array layers
		.arrayLayers = 1,
		// samples
		.samples = samples,
		// tiling
		.tiling = tiling,
		// usage
		.usage = usage,
		// sharing mode
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		// queue family index count
		.queueFamilyIndexCount = 0U,
		// queue family indices
		.pQueueFamilyIndices = nullptr,
		// initial layout
		.initialLayout = layout
	};

	// create image
	return vk::make_unique<vk::image>(info);
}
