#include "ve/vulkan/pipeline/pipeline.hpp"


// -- P I P E L I N E ---------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* graphics pipeline constructor */
vulkan::pipeline::pipeline(const vk::graphics_pipeline_info& info)
: _pipeline{vk::make_unique<vk::pipeline>(info)} {
}

/* compute pipeline constructor */
vulkan::pipeline::pipeline(const vk::pipeline_shader_stage_info& stage,
						   const vk::pipeline_layout& layout)
: _pipeline{vulkan::pipeline::_create_compute_pipeline(stage, layout)} {
}


// -- public conversion operators ---------------------------------------------

/* const vk::pipeline& conversion operator */
vulkan::pipeline::operator const vk::pipeline&(void) const noexcept {
	return _pipeline.get();
}


// -- private static methods --------------------------------------------------

/* create compute pipeline */
auto vulkan::pipeline::_create_compute_pipeline(
		const vk::pipeline_shader_stage_info& stage,
		const vk::pipeline_layout& layout) -> vk::unique<vk::pipeline> {

	// create info
	vk::compute_pipeline_info info{
		// structure type
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		// next structure
		.pNext = nullptr,
		// create flags
		.flags = 0U,
		// stage
		.stage = stage,
		// layout
		.layout = layout,
		// base pipeline handle (for deriving)
		.basePipelineHandle = nullptr,
		// base pipeline index (for deriving)
		.basePipelineIndex = 0
	};

	// create pipeline
	return vk::make_unique<vk::pipeline>(info);
}
