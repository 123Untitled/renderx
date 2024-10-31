/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_PIPELINE_HEADER
#define ENGINE_VULKAN_PIPELINE_HEADER

#include "ve/vk/typedefs.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vk/array.hpp"
#include "ve/vulkan/specialization.hpp"
#include "ve/vulkan/shader_module.hpp"
#include "./pipeline_layout.hpp"

#include "ve/vulkan/descriptors/descriptor_set_layout_library.hpp"
#include "ve/vulkan/descriptors/pipeline_layout_library.hpp"


#include "ve/libraries/shader_library.hpp"


#include <glm/glm.hpp>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P I P E L I N E -----------------------------------------------------

	class pipeline final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::pipeline;


			// -- private members ---------------------------------------------

			/* pipeline */
			vk::unique<vk::pipeline> _pipeline;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline(void) noexcept = default;

			/* info constructor */
			pipeline(const vk::graphics_pipeline_info& info)
			: _pipeline{vk::make_unique<vk::pipeline>(info)} {
			}


			/* deleted copy constructor */
			pipeline(const ___self&) = delete;

			/* move constructor */
			pipeline(___self&&) noexcept = default;

			/* destructor */
			~pipeline(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* layout */
			auto layout(void) const noexcept -> const vk::pipeline_layout& {
				return ve::pipeline_layout_library::get<"main">();
			}


			// -- public conversion operators ---------------------------------

			/* vk::pipeline conversion operator */
			operator const vk::pipeline&(void) const noexcept {
				return _pipeline;
			}

	}; // class pipeline




	// another approach (builder pattern)

	template <typename ___vtype>
	class pipeline_builder {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::pipeline_builder<___vtype>;

			/* vertex type */
			using ___vertex = ___vtype;


		public:

			// -- public static methods ---------------------------------------

			/* build */
			static auto build(const vk::render_pass& render_pass) -> vulkan::pipeline {

				// shader stages
				const vk::array stages {
					ve::shader_library::vertex_stage_info<"planet">(/* specialization */),
					ve::shader_library::fragment_stage_info<"planet">(),
					ve::shader_library::hull_stage_info<"planet">(),
					ve::shader_library::domain_stage_info<"planet">(),
					
				};

				// vertex input info
				const auto vertex_input_info = ___vertex::info();

				// input assembly info
				const vk::pipeline_input_assembly_state_info input_assembly_state_info {
					// type of struct
					VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
					// pointer to next struct
					nullptr,
					// flags
					0U,
					// topology
					//VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
					VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
					// primitive restart enable
					VK_FALSE
				};

				// tesselation info
				const vk::pipeline_tesselation_state_info tesselation_state_info {
					// type of struct
					VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
					// pointer to next struct
					nullptr,
					// flags
					0U,
					// patch control points (only for tesselation shaders)
					3U
				};

				// viewport
				const vk::viewport viewport {
					// x coordinate
					.x = 0.0f,
					// y coordinate
					.y = 0.0f,
					// width
					.width = 800.0f,
					// height
					.height = 600.0f,
					// min depth
					.minDepth = 0.0f,
					// max depth
					.maxDepth = 1.0f,
				};

				// scissor
				const vk::scissor scissor {
					// offset
					.offset = {0, 0},
					// extent
					.extent = {800U, 600U}, // swapchain extent
				};

				// viewport info
				const vk::pipeline_viewport_state_info viewport_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// viewport count
					.viewportCount = 1U,
					// pointer to viewports
					.pViewports = nullptr,//&_viewport,
					// scissor count
					.scissorCount = 1U,
					// pointer to scissors
					.pScissors = nullptr,//&_scissor,
				};

				// rasterization info
				const vk::pipeline_rasterization_state_info rasterization_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// depth clamp enable
					.depthClampEnable = VK_FALSE,
					// rasterizer discard enable
					.rasterizerDiscardEnable = VK_FALSE,
					// polygon mode
					.polygonMode = VK_POLYGON_MODE_FILL,
					// cull mode
					.cullMode = VK_CULL_MODE_BACK_BIT,
					// front face
					.frontFace = VK_FRONT_FACE_CLOCKWISE,
					// depth bias enable
					.depthBiasEnable = VK_FALSE,
					// depth bias constant factor
					.depthBiasConstantFactor = 0.0f,
					// depth bias clamp
					.depthBiasClamp = 0.0f,
					// depth bias slope factor
					.depthBiasSlopeFactor = 0.0f,
					// line width
					.lineWidth = 1.0f, // needs GPU feature (extension: VK_EXT_line_rasterization ? wideLines)
				};

				// multisample info
				const vk::pipeline_multisample_state_info multisample_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// rasterization samples
					.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
					// sample shading enable
					.sampleShadingEnable = VK_FALSE,
					// min sample shading
					.minSampleShading = 1.0f,
					// sample mask
					.pSampleMask = nullptr,
					// alpha to coverage enable
					.alphaToCoverageEnable = VK_FALSE,
					// alpha to one enable
					.alphaToOneEnable = VK_FALSE,
				};

				// depth stencil info
				const vk::pipeline_depth_stencil_state_info depth_stencil_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0,
					// depth test enable
					.depthTestEnable = VK_TRUE,
					// depth write enable
					.depthWriteEnable = VK_TRUE,
					// depth compare operation
					.depthCompareOp = VK_COMPARE_OP_LESS,
					// depth bounds test enable
					.depthBoundsTestEnable = VK_FALSE,
					// stencil test enable
					.stencilTestEnable = VK_FALSE,
					// front stencil operation
					.front = {},
					// back stencil operation
					.back = {},
					// min depth bounds
					.minDepthBounds = 0.0f,
					// max depth bounds
					.maxDepthBounds = 1.0f,
				};

				// color blend attachment
				const vk::pipeline_color_blend_attachment_state color_blend_attachment_state {
					// blend enable
					.blendEnable         = VK_FALSE,
					// source color blend factor
					.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
					// destination color blend factor
					.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
					// color blend operation
					.colorBlendOp        = VK_BLEND_OP_ADD,
					// source alpha blend factor
					.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
					// destination alpha blend factor
					.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
					// alpha blend operation
					.alphaBlendOp        = VK_BLEND_OP_ADD,
					// color write mask
					.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
										 | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
				};

				// color blend info
				const vk::pipeline_color_blend_state_info color_blend_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// logic operation enable
					.logicOpEnable = VK_FALSE,
					// logic operation
					.logicOp = VK_LOGIC_OP_COPY,
					// attachment count
					.attachmentCount = 1U,
					// attachments
					.pAttachments = &color_blend_attachment_state,
					// blend constants
					.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f},
				};

				// WARNING need to setup dynamic separtely !
				const vk::dynamic_state dynamic_states[] = {
					VK_DYNAMIC_STATE_VIEWPORT,
					VK_DYNAMIC_STATE_SCISSOR,
					VK_DYNAMIC_STATE_LINE_WIDTH,
				};

				// dynamic state info
				const vk::pipeline_dynamic_state_info dynamic_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// dynamic state count
					.dynamicStateCount = sizeof(dynamic_states) / sizeof(dynamic_states[0]),
					// dynamic states
					.pDynamicStates = dynamic_states,
				};

				// pipeline info
				vk::graphics_pipeline_info info {
					// type of struct
					.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
					// pointer to next struct
					.pNext               = nullptr,
					// flags
					.flags               = 0U,
					// shader stage count
					.stageCount          = stages.size(),
					// shader stages
					.pStages             = stages.data(),
					// vertex input state
					.pVertexInputState   = &vertex_input_info,
					// input assembly state
					.pInputAssemblyState = &input_assembly_state_info,
					// tesselation state
					.pTessellationState  = &tesselation_state_info,
					// viewport state
					.pViewportState      = &viewport_state_info,
					// rasterization state
					.pRasterizationState = &rasterization_state_info,
					// multisample state
					.pMultisampleState   = &multisample_state_info,
					// depth stencil state
					.pDepthStencilState  = &depth_stencil_state_info,
					// color blend state
					.pColorBlendState    = &color_blend_state_info,
					// dynamic state
					.pDynamicState       = &dynamic_state_info,
					// pipeline layout
					.layout              = ve::pipeline_layout_library::get<"main">(),
					// render pass
					.renderPass          = render_pass,
					// subpass
					.subpass             = 0U,
					// base pipeline handle
					.basePipelineHandle  = VK_NULL_HANDLE,
					// base pipeline index
					.basePipelineIndex   = -1
				};

				return vulkan::pipeline{info};
			}





	}; // class pipeline_builder


} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_HEADER
