#include "vulkan/vulkan_pipeline.hpp"


// -- public lifecycle --------------------------------------------------------

/* infos constructor */
template <decltype(sizeof(0)) S>
vulkan::pipeline::pipeline(const vk::shared<vk::device>&                 device,
						   const vk::pipeline_shader_stage_info(&        shader_stages)[S],
						   const vk::pipeline_vertex_input_state_info&   vertex_input,
						   const vk::pipeline_input_assembly_state_info& input_assembly_info,
						   const vk::pipeline_tesselation_state_info&    tesselation,
						   const vk::pipeline_viewport_state_info&       viewport_info,
						   const vk::pipeline_rasterization_state_info&  rasterizer,
						   const vk::pipeline_multisample_state_info&    multisampling,
						   const vk::pipeline_depth_stencil_state_info&  depth_stencil,
						   const vk::pipeline_color_blend_state_info&    color_blend,
						   const vk::pipeline_dynamic_state_info&        dynamic,
						   const vk::pipeline_layout&                    layout,
						   const vk::render_pass&                        render_pass)

: _pipeline{device, vk::graphics_pipeline_info{
		// type of struct
		.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		// pointer to next struct
		.pNext               = nullptr,
		// flags
		.flags               = 0,
		// shader stage count
		.stageCount          = S,
		// shader stages
		.pStages             = shader_stages,
		// vertex input state
		.pVertexInputState   = &vertex_input,
		// input assembly state
		.pInputAssemblyState = &input_assembly_info,
		// tesselation state
		.pTessellationState  = &tesselation,
		// viewport state
		.pViewportState      = &viewport_info,
		// rasterization state
		.pRasterizationState = &rasterizer,
		// multisample state
		.pMultisampleState   = &multisampling,
		// depth stencil state
		.pDepthStencilState  = &depth_stencil,
		// color blend state
		.pColorBlendState    = &color_blend,
		// dynamic state
		.pDynamicState       = &dynamic,
		// pipeline layout
		.layout              = layout,
		// render pass
		.renderPass          = VK_NULL_HANDLE,
		// subpass
		.subpass             = 0,
		// base pipeline handle
		.basePipelineHandle  = VK_NULL_HANDLE,
		// base pipeline index
		.basePipelineIndex   = -1
	}} {

}
