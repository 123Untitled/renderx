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

#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vk_shared.hpp"
#include "meta_vertex.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P I P E L I N E -----------------------------------------------------

	class pipeline final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::pipeline;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline(void) noexcept = default;

			/* infos constructor */
			template <decltype(sizeof(0)) S>
			pipeline(const vk::shared<vk::device>&,
					 const vk::pipeline_shader_stage_info(&)[S],
					 const vk::pipeline_vertex_input_state_info&,
					 const vk::pipeline_input_assembly_state_info&,
					 const vk::pipeline_tesselation_state_info&,
					 const vk::pipeline_viewport_state_info&,
					 const vk::pipeline_rasterization_state_info&,
					 const vk::pipeline_multisample_state_info&,
					 const vk::pipeline_depth_stencil_state_info&,
					 const vk::pipeline_color_blend_state_info&,
					 const vk::pipeline_dynamic_state_info&,
					 const vk::pipeline_layout&,
					 const vk::render_pass&);

			/* copy constructor */
			pipeline(const self&) noexcept = default;

			/* move constructor */
			pipeline(self&&) noexcept = default;

			/* destructor */
			~pipeline(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::pipeline conversion operator */
			operator const vk::pipeline&(void) const noexcept {
				return _pipeline;
			}


		private:

			// -- private members ---------------------------------------------

			/* pipeline */
			vk::shared<vk::pipeline> _pipeline;

	}; // class pipeline


	// pipeline creation
	template <typename T>
	auto create_pipeline(void) {

		static_assert(engine::meta::is_vertex<T>, "T must be a vertex type");

		using vertex_type = T;

		//Shader stages
		//VertexInput State
		//InputAssembly State
		//Tesselation State
		//Viewport State
		//Rasterization State
		//MultiSample State
		//DepthStencil State
		//ColorBlend State
		//Dynamic State
		//Pipeline layout
		//RenderPass
		//basePipelineHandle
		//basePipelineIndex
		// VkGraphicsPipelineCreateInfo


		const vk::pipeline_shader_stage_info shader_stages[] = {{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stage = VK_SHADER_STAGE_VERTEX_BIT,
			.module = VK_NULL_HANDLE,
			.pName = "main",
			.pSpecializationInfo = nullptr,
		}, {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = VK_NULL_HANDLE,
			.pName = "main",
			.pSpecializationInfo = nullptr,
		}};

		vk::pipeline_vertex_input_state_info vertex_input
			= vertex_type::pipeline_vertex_input_state_info();

		const vk::pipeline_input_assembly_state_info input_assembly_info = {
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// topology
			.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			// primitive restart enable (only for indexed draws)
			.primitiveRestartEnable = VK_FALSE,
		};

		const vk::pipeline_tesselation_state_info tesselation{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// patch control points (only for tesselation shaders)
			.patchControlPoints = 0,
		};

		// transform view
		const vk::viewport viewport{
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

		// cutout view
		const vk::rect2D scissor{
			// offset
			.offset = {0, 0},
			// extent
			.extent = {800, 600}, // swapchain extent
		};

		const vk::pipeline_viewport_state_info viewport_info{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// viewport count
			.viewportCount = 1,
			// pointer to viewports
			.pViewports = &viewport,
			// scissor count
			.scissorCount = 1,
			// pointer to scissors
			.pScissors = &scissor,

		};
		// need to setup dynamic viewport and scissor !!!

		// rasterizer
		const vk::pipeline_rasterization_state_info rasterizer{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
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

		// multisampling
		const vk::pipeline_multisample_state_info multisampling{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
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

		const vk::pipeline_depth_stencil_state_info depth_stencil{
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

		const vk::pipeline_color_blend_attachment_state color_blend_attachment{
			// blend enable
			.blendEnable = VK_FALSE,
			// source color blend factor
			.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
			// destination color blend factor
			.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
			// color blend operation
			.colorBlendOp = VK_BLEND_OP_ADD,
			// source alpha blend factor
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
			// destination alpha blend factor
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
			// alpha blend operation
			.alphaBlendOp = VK_BLEND_OP_ADD,
			// color write mask
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
							| VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		};

		const vk::pipeline_color_blend_state_info color_blend{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// logic operation enable
			.logicOpEnable = VK_FALSE,
			// logic operation
			.logicOp = VK_LOGIC_OP_COPY,
			// attachment count
			.attachmentCount = 1,
			// attachments
			.pAttachments = &color_blend_attachment,
			// blend constants
			.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f},
		};


		const vk::dynamic_state dynamic_state[] = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR,
			VK_DYNAMIC_STATE_LINE_WIDTH,
		};


		const vk::pipeline_dynamic_state_info dynamic{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// dynamic state count
			.dynamicStateCount = 2,
			// dynamic states
			.pDynamicStates = dynamic_state,
		};


		vk::shared<vk::device> device{};


		vk::shared<vk::pipeline_layout> layout {
			
			device, vk::pipeline_layout_info{
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0,
			// set layout count
			.setLayoutCount = 0,
			// set layouts
			.pSetLayouts = nullptr,
			// push constant range count
			.pushConstantRangeCount = 0,
			// push constant ranges
			.pPushConstantRanges = nullptr,
		}};


		vulkan::pipeline pipeline{device,
								shader_stages,
								vertex_input,
								input_assembly_info,
								tesselation,
								viewport_info,
								rasterizer,
								multisampling,
								depth_stencil,
								color_blend,
								dynamic,
								layout,
								vk::render_pass{}};


		//vk::pipeline pipeline{};
		//::vkCreateGraphicsPipelines(VK_NULL_HANDLE /* device */,
		//							VK_NULL_HANDLE /* pipeline cache */,
		//							1,             /* pipeline count */
		//							&info, nullptr, &pipeline);
		//vk::pipeline_bind_point bind_point{VK_PIPELINE_BIND_POINT_GRAPHICS};
		//::vkDestroyPipeline(VK_NULL_HANDLE /* device */, pipeline, nullptr);

	}

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_HEADER
