#include "engine/vulkan/render_pass.hpp"
#include "engine/vk/array.hpp"
#include "engine/vulkan/device.hpp"


// -- public lifecycle --------------------------------------------------------

/* device constructor */
vulkan::render_pass::render_pass(const vulkan::device& ___dev)
: _render_pass{___self::_create_render_pass(___dev)} {
}


// -- public conversion operators ---------------------------------------------

/* underlying conversion operator */
vulkan::render_pass::operator const vk::render_pass&(void) const noexcept {
	return _render_pass;
}

/* shared conversion operator */
vulkan::render_pass::operator const vk::shared<vk::render_pass>&(void) const noexcept {
	return _render_pass;
}


auto find_supported_format(const vulkan::device& ___dev) -> vk::format {

	const std::vector<vk::format> candidates{
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D24_UNORM_S8_UINT
	};

	vk::image_tiling tiling{VK_IMAGE_TILING_OPTIMAL};

	vk::format_feature_flags features{VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT};

	vk::physical_device pdevice{___dev.physical_device()};


	for (vk::format format : candidates) {

		VkFormatProperties props;

		::vkGetPhysicalDeviceFormatProperties(pdevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		} else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}


// -- private static methods --------------------------------------------------

/* create render pass */
auto vulkan::render_pass::_create_render_pass(const vulkan::device& ___dev)
	-> vk::shared<vk::render_pass> {


	// msaa samples
	const vk::sample_count_flag_bits msaa_samples = VK_SAMPLE_COUNT_1_BIT;



	// -- attachments ---------------------------------------------------------

	const vk::array attachments {

		// color attachment
		vk::attachment_description {
			// flags
			0U,
			// format (swapchain format)
			VK_FORMAT_B8G8R8A8_SRGB,
			// samples (multisampling)
			msaa_samples,
			// load op
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			// store op
			VK_ATTACHMENT_STORE_OP_STORE,
			// stencil load op
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			// stencil store op
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			// initial layout
			VK_IMAGE_LAYOUT_UNDEFINED,
			// final layout
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},

		// depth attachment
		vk::attachment_description {
			// flags
			0U,
			// format (find depth format) !!!
			find_supported_format(___dev),
			// samples (multisampling)
			msaa_samples,
			// load op
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			// store op
			VK_ATTACHMENT_STORE_OP_STORE,
			// stencil load op
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			// stencil store op
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			// initial layout
			VK_IMAGE_LAYOUT_UNDEFINED,
			// final layout
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		},

		// resolve attachment
		vk::attachment_description {
			// flags
			0U,
			// format (swapchain format)
			VK_FORMAT_B8G8R8A8_SRGB,
			// samples
			VK_SAMPLE_COUNT_1_BIT,
			// load op
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			// store op
			VK_ATTACHMENT_STORE_OP_STORE,
			// stencil load op
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			// stencil store op
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			// initial layout
			VK_IMAGE_LAYOUT_UNDEFINED,
			// final layout
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		},

	};


	// -- references ----------------------------------------------------------

	const vk::array references {

		// color reference
		vk::attachment_reference {
			// attachment (index)
			0U,
			// layout
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},

		// depth reference
		vk::attachment_reference {
			// attachment (index)
			1U,
			// layout
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		},

		// resolve reference
		vk::attachment_reference {
			// attachment (index)
			2U,
			// layout
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		}
	};


	// -- subpasses -----------------------------------------------------------

	const vk::array subpasses {

		// subpass
		vk::subpass_description {
			// flags
			0U,
			// pipeline bind point
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			// input attachment count
			0U,
			// input attachments
			nullptr,
			// color attachment count
			1U,
			// color attachments
			&references[0],
			// resolve attachments
			&references[2],
			// depth stencil attachment
			&references[1],
			// preserve attachment count
			0U,
			// preserve attachments
			nullptr
		}
	};


	// -- dependencies --------------------------------------------------------

	const vk::array dependencies {

		// dependency
		vk::subpass_dependency {
			.srcSubpass      = VK_SUBPASS_EXTERNAL,
			.dstSubpass      = 0U,

			.srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
			.dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,

			.srcAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,

			.dependencyFlags = 0U
		}
	};


	// render pass info
	vk::render_pass_info info {
		// structure type
		VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		// next structure
		nullptr,
		// flags
		0U,
		// attachment count
		attachments.size(),
		// attachments
		attachments.data(),
		// subpass count
		subpasses.size(),
		// subpasses
		subpasses.data(),
		// dependency count
		dependencies.size(),
		// dependencies
		dependencies.data()
	};

	// create render pass
	return vk::shared<vk::render_pass>{___dev, info};
}

