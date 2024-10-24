#include "ve/vulkan/render_pass.hpp"
#include "ve/vk/utils.hpp"
#include "ve/vk/array.hpp"
#include "ve/vulkan/device.hpp"

#include <stdexcept>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::render_pass::render_pass(void)
: _render_pass{___self::_create_render_pass()} {
}

/* move constructor */
vulkan::render_pass::render_pass(___self&& ___ot) noexcept
: _render_pass{___ot._render_pass} {

	// invalidate other
	___ot._render_pass = nullptr;
}

/* destructor */
vulkan::render_pass::~render_pass(void) noexcept {

	if (_render_pass == nullptr)
		return;

	// release render pass
	::vk_destroy_render_pass(vulkan::device::logical(),
			_render_pass, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::render_pass::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// release render pass
	if (_render_pass != nullptr)
		::vk_destroy_render_pass(vulkan::device::logical(),
				_render_pass, nullptr);

	// move data
	_render_pass = ___ot._render_pass;

	// invalidate other
	___ot._render_pass = nullptr;

	// done
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::render_pass::underlying(void) const noexcept -> const vk::render_pass& {
	return _render_pass;
}



auto find_supported_format(void) -> vk::format {

	const vk::array<vk::format, 3U> candidates {
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D24_UNORM_S8_UINT
	};

	const vk::image_tiling tiling{VK_IMAGE_TILING_OPTIMAL};

	vk::format_feature_flags features{VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT};

	vk::physical_device pdevice = vulkan::device::physical();


	for (vk::u32 i = 0U; i < candidates.size(); ++i) {

		vk::format_properties props;

		::vk_get_physical_device_format_properties(pdevice, candidates[i], &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return candidates[i];

		}

		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return candidates[i];
		}
	}

	throw std::runtime_error("failed to find supported format!");
}


// -- private static methods --------------------------------------------------

/* create render pass */
auto vulkan::render_pass::_create_render_pass(void) -> vk::render_pass {


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
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			//VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},

		// depth attachment
		//vk::attachment_description {
		//	// flags
		//	0U,
		//	// format (find depth format) !!!
		//	find_supported_format(),
		//	// samples (multisampling)
		//	msaa_samples,
		//	// load op
		//	VK_ATTACHMENT_LOAD_OP_CLEAR,
		//	// store op
		//	VK_ATTACHMENT_STORE_OP_STORE,
		//	// stencil load op
		//	VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		//	// stencil store op
		//	VK_ATTACHMENT_STORE_OP_DONT_CARE,
		//	// initial layout
		//	VK_IMAGE_LAYOUT_UNDEFINED,
		//	// final layout
		//	VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		//},

		//// resolve attachment
		//vk::attachment_description {
		//	// flags
		//	0U,
		//	// format (swapchain format)
		//	VK_FORMAT_B8G8R8A8_SRGB,
		//	// samples
		//	VK_SAMPLE_COUNT_1_BIT,
		//	// load op
		//	VK_ATTACHMENT_LOAD_OP_CLEAR,
		//	// store op
		//	VK_ATTACHMENT_STORE_OP_STORE,
		//	// stencil load op
		//	VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		//	// stencil store op
		//	VK_ATTACHMENT_STORE_OP_DONT_CARE,
		//	// initial layout
		//	VK_IMAGE_LAYOUT_UNDEFINED,
		//	// final layout
		//	VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		//},

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
		//vk::attachment_reference {
		//	// attachment (index)
		//	1U,
		//	// layout
		//	VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		//},
		//
		//// resolve reference
		//vk::attachment_reference {
		//	// attachment (index)
		//	2U,
		//	// layout
		//	VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		//}
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
			nullptr,
			//&references[2],
			// depth stencil attachment
			nullptr,
			//&references[1],
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
			// subpass source (index)
			VK_SUBPASS_EXTERNAL,
			// subpass destination (index)
			0U,

			// source stage mask
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,// | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
			// destination stage mask
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,

			// source access mask
			VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,// | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			// destination access mask
			VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,

			// dependency flags
			0U
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


	vk::render_pass ___rpass;

	// create render pass
	vk::try_execute<"failed to create render pass">(
			::vk_create_render_pass,
			vulkan::device::logical(), &info, nullptr, &___rpass);

	return ___rpass;
}
