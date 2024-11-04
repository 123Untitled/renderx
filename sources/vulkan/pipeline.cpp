#include "ve/vulkan/pipeline/pipeline.hpp"


// -- P I P E L I N E ---------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* graphics pipeline constructor */
vk::pipeline::pipeline(const ::vk_graphics_pipeline_create_info& info)
: _pipeline{vk::make_unique<::vk_pipeline>(info)} {
}

/* compute pipeline constructor */
vk::pipeline::pipeline(const ::vk_pipeline_shader_stage_create_info& stage,
						   const ::vk_pipeline_layout& layout)
: _pipeline{vk::pipeline::_create_compute_pipeline(stage, layout)} {
}


// -- public conversion operators ---------------------------------------------

/* const reference conversion operator */
vk::pipeline::operator const ::vk_pipeline&(void) const noexcept {
	return _pipeline.get();
}


// -- private static methods --------------------------------------------------

/* create compute pipeline */
auto vk::pipeline::_create_compute_pipeline(
		const ::vk_pipeline_shader_stage_create_info& stage,
		const ::vk_pipeline_layout& layout) -> vk::unique<::vk_pipeline> {

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
	return vk::make_unique<::vk_pipeline>(info);
}
