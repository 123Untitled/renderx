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

#include "engine/vk/typedefs.hpp"
#include "engine/vk/shared.hpp"
#include "engine/vertex/is_vertex.hpp"
#include "engine/vertex/vertex.hpp"
#include "engine/vk/array.hpp"
#include "engine/vulkan/specialization.hpp"
#include "engine/vulkan/shader_module.hpp"

#include "engine/shader_library.hpp"


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
			vk::shared<vk::pipeline> _pipeline;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline(void) noexcept = default;

			/* info constructor */
			pipeline(const vk::shared<vk::device>& ___dev,
					 const vk::graphics_pipeline_info& ___info)
			: _pipeline{___dev, ___info} {
			}


			/* copy constructor */
			pipeline(const ___self&) noexcept = default;

			/* move constructor */
			pipeline(___self&&) noexcept = default;

			/* destructor */
			~pipeline(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


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

			// -- public lifecycle --------------------------------------------


			// -- public methods ----------------------------------------------

			/* shader stage info */
			//template <vk::shader_stage_flag_bits ___stage>
			//static constexpr auto shader_stage_info(const vulkan::shader_module& ___mod) noexcept -> vk::pipeline_shader_stage_info {
			//
			//	return vk::pipeline_shader_stage_info {
			//		.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			//		.pNext  = nullptr,
			//		.flags  = 0U,
			//		.stage  = ___stage,
			//		.module = ___mod,
			//		.pName  = "main",
			//		.pSpecializationInfo = nullptr,
			//	};
			//}
			//
			//template <vk::shader_stage_flag_bits ___stage, typename... ___types>
			//static constexpr auto shader_stage_info(const vulkan::shader_module& ___mod,
			//										const vulkan::specialization<___types...>& ___spec
			//		) noexcept -> vk::pipeline_shader_stage_info {
			//
			//	return vk::pipeline_shader_stage_info {
			//		.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			//		.pNext  = nullptr,
			//		.flags  = 0U,
			//		.stage  = ___stage,
			//		.module = ___mod,
			//		.pName  = "main",
			//		.pSpecializationInfo = &___spec.info(),
			//	};
			//}



			/* build */
			static auto build(
					const vk::shared<vk::device>& ___device,
					const engine::shader_library& ___shaders,
							  const vk::shared<vk::render_pass>& ___render_pass) -> vulkan::pipeline {

				// shader stages
				const vk::array stages {
					___shaders.vertex_module("basic").stage_info(),
					___shaders.fragment_module("basic").stage_info()
				};

				// vertex input info
				const auto vertex_input_info = ___vertex::info();

				// input assembly info
				const auto input_assembly_info = ___self::input_assembly_info<VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE>();

				// tesselation info
				const auto tesselation_info = ___self::tesselation_info(); 

				// viewport
				const auto viewport = ___self::viewport();

				// scissor
				const auto scissor = ___self::scissor();

				// viewport info
				const auto viewport_info = ___self::viewport_info();

				// rasterization info
				const auto rasterization_info = ___self::rasterization_info();

				// multisample info
				const auto multisampling = ___self::multisample_info();

				// depth stencil info
				const auto depth_stencil_info = ___self::depth_stencil_info();

				// color blend attachment
				const auto color_blend_attachment = ___self::color_blend_attachment();

				// color blend info
				const auto color_blend_info = ___self::color_blend_info(color_blend_attachment);

				// dynamic state info
				const auto dynamic_state_info = ___self::dynamic_state_info();

				// pipeline layout
				const auto layout = ___self::layout(___device);

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
					.pInputAssemblyState = &input_assembly_info,
					// tesselation state
					.pTessellationState  = &tesselation_info,
					// viewport state
					.pViewportState      = &viewport_info,
					// rasterization state
					.pRasterizationState = &rasterization_info,
					// multisample state
					.pMultisampleState   = &multisampling,
					// depth stencil state
					.pDepthStencilState  = &depth_stencil_info,
					// color blend state
					.pColorBlendState    = &color_blend_info,
					// dynamic state
					.pDynamicState       = &dynamic_state_info,
					// pipeline layout
					.layout              = layout,
					// render pass
					.renderPass          = ___render_pass,
					// subpass
					.subpass             = 0U,
					// base pipeline handle
					.basePipelineHandle  = VK_NULL_HANDLE,
					// base pipeline index
					.basePipelineIndex   = -1
				};

				return vulkan::pipeline{___device, info};
			}


			// -- public interface --------------------------------------------

			/* input assembly info */
			template <vk::primitive_topology ___topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
					              vk::bool32 ___restart  = VK_FALSE>
			static constexpr auto input_assembly_info(void) noexcept -> vk::pipeline_input_assembly_state_info {

				return vk::pipeline_input_assembly_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// topology
					.topology = ___topology,
					// primitive restart enable (only for indexed draws)
					.primitiveRestartEnable = ___restart,
				};
			}

			/* tessellation info */
			static constexpr auto tesselation_info(void) noexcept -> vk::pipeline_tesselation_state_info {

				return vk::pipeline_tesselation_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// patch control points (only for tesselation shaders)
					.patchControlPoints = 0U,
				};
			}

			/* viewport */
			static constexpr auto viewport(void) noexcept -> vk::viewport {

				return vk::viewport {
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
			}

			/* scissor */
			static constexpr auto scissor(void) noexcept {

				// cutout view
				return vk::scissor {
					// offset
					.offset = {0, 0},
					// extent
					.extent = {800U, 600U}, // swapchain extent
				};
			}


			/* viewport info */
			static constexpr auto viewport_info(void) noexcept -> vk::pipeline_viewport_state_info {

				return vk::pipeline_viewport_state_info {
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
				// need to setup dynamic viewport and scissor !!!
			}


			/* rasterization info */
			static constexpr auto rasterization_info(void) noexcept -> vk::pipeline_rasterization_state_info {

				return vk::pipeline_rasterization_state_info {
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
			}

			/* multisample info */
			static constexpr auto multisample_info(void) noexcept -> vk::pipeline_multisample_state_info {

				return vk::pipeline_multisample_state_info {
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
			}

			/* depth stencil info */
			static constexpr auto depth_stencil_info(void) noexcept -> vk::pipeline_depth_stencil_state_info {

				return vk::pipeline_depth_stencil_state_info {
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
			}

			/* color blend attachment */
			static constexpr auto color_blend_attachment(void) noexcept -> vk::pipeline_color_blend_attachment_state {

				return vk::pipeline_color_blend_attachment_state {
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
			}

			/* color blend info */
			static constexpr auto color_blend_info(const vk::pipeline_color_blend_attachment_state& ___cba) noexcept -> vk::pipeline_color_blend_state_info {

				return vk::pipeline_color_blend_state_info {
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
					.pAttachments = &___cba,
					// blend constants
					.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f},
				};
			}


			/* dynamic state info */
			static /*constexpr*/ auto dynamic_state_info(void) noexcept -> vk::pipeline_dynamic_state_info {

				// WARNING need to setup dynamic separtely !
				static const vk::dynamic_state dynamic_state[] = {
					VK_DYNAMIC_STATE_VIEWPORT,
					VK_DYNAMIC_STATE_SCISSOR,
					VK_DYNAMIC_STATE_LINE_WIDTH,
				};

				return vk::pipeline_dynamic_state_info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// dynamic state count
					.dynamicStateCount = 2U,
					// dynamic states
					.pDynamicStates = dynamic_state,
				};
			}

			/* pipeline layout */
			static auto layout(const vk::shared<vk::device>& ___device) -> vk::shared<vk::pipeline_layout> {

				return vk::shared<vk::pipeline_layout> {

					___device, vk::pipeline_layout_info{
						// type of struct
						.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
						// pointer to next struct
						.pNext = nullptr,
						// flags
						.flags = 0U,
						// set layout count
						.setLayoutCount = 0U,
						// set layouts
						.pSetLayouts = nullptr,
						// push constant range count
						.pushConstantRangeCount = 0U,
						// push constant ranges
						.pPushConstantRanges = nullptr,
					}
				};
			}

	}; // class pipeline_builder





	// pipeline creation
	template <typename T>
	auto create_pipeline(const vk::shared<vk::device>& ___device,
						 const vk::shared<vk::render_pass>& ___render_pass) -> vulkan::pipeline {

		//static_assert(engine::meta::is_vertex<T>, "T must be a vertex type");

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


		const vk::array stages {

			vk::pipeline_shader_stage_info {
				.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0U,
				.stage = VK_SHADER_STAGE_VERTEX_BIT,
				.module = VK_NULL_HANDLE,
				.pName = "main",
				.pSpecializationInfo = nullptr,
			},

			vk::pipeline_shader_stage_info {
				.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0U,
				.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
				.module = VK_NULL_HANDLE,
				.pName = "main",
				.pSpecializationInfo = nullptr,
			}
		};


		vk::pipeline_vertex_input_state_info vertex_input = vertex_type::info();


		const vk::pipeline_input_assembly_state_info input_assembly_info = {
			// type of struct
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			// pointer to next struct
			.pNext = nullptr,
			// flags
			.flags = 0U,
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


		vk::shared<vk::pipeline_layout> layout {

			___device, vk::pipeline_layout_info{
				// type of struct
				.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
				// pointer to next struct
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// set layout count
				.setLayoutCount = 0U,
				// set layouts
				.pSetLayouts = nullptr,
				// push constant range count
				.pushConstantRangeCount = 0U,
				// push constant ranges
				.pPushConstantRanges = nullptr,
			}
		};

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
			.renderPass          = ___render_pass,
			// subpass
			.subpass             = 0,
			// base pipeline handle
			.basePipelineHandle  = VK_NULL_HANDLE,
			// base pipeline index
			.basePipelineIndex   = -1
		};

		return vulkan::pipeline{___device, info};

	}

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_HEADER
