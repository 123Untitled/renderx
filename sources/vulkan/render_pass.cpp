#include "ve/vulkan/render_pass.hpp"
#include "ve/vulkan/multisampling.hpp"
#include "ve/vk/utils.hpp"
#include "ve/vk/array.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vulkan/depth_buffer.hpp"

#include <stdexcept>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::render_pass::render_pass(void)
: _render_pass{___self::_create_render_pass()} {
}


// -- public conversion operators ---------------------------------------------

/* const vk::render_pass& conversion operator */
ve::render_pass::operator const vk::render_pass&(void) const noexcept {
	return _render_pass;
}



// -- private static methods --------------------------------------------------

/* create render pass */
auto ve::render_pass::_create_render_pass(void) -> vk::unique<vk::render_pass> {


	// -- attachments ---------------------------------------------------------

	const vk::array attachments {

		// color attachment
		vk::attachment_description {
			// flags
			0U,
			// format (swapchain format)
			VK_FORMAT_B8G8R8A8_SRGB,
			// samples
			ve::multisampling::max(),
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
			//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},

		// depth attachment
		vk::attachment_description {
			// flags
			0U,
			// format
			ve::depth_buffer::format(),
			// samples (multisampling)
			ve::multisampling::max(),
			// load op
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			// store op
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
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
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
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

	// create render pass
	return vk::make_unique<vk::render_pass>(info);
}
