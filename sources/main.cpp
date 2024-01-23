#define GLFW_INCLUDE_VULKAN


#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_logical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_shader_module.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"

#include "vk_typedefs.hpp"

#include "os.hpp"
#include "meta_vertex.hpp"
#include "basic_vertex.hpp"
#include "exceptions.hpp"
#include "shader_library.hpp"

#include <xns>


#include "vulkan_resource.hpp"


				//vulkan::command_pool pool{_ldevice};
				//auto buffers = pool.new_buffers(_ldevice, 2);
				//for (auto& buffer : buffers) {
				//	buffer.destroy(_ldevice, pool);
				//}
				//pool.destroy(_ldevice);


				//// get formats
				//const auto& formats = xns::get<xns::vector<::VkSurfaceFormatKHR>>(choice);
				//// get modes
				//const auto& modes = xns::get<xns::vector<::VkPresentModeKHR>>(choice);
				//// get capabilities
				//const auto& capabilities = xns::get<vulkan::surface_capabilities>(choice);
				//
				//
				//::VkSurfaceFormatKHR format = [](const auto& formats) {
				//	for (const auto& f : formats) {
				//		if (f.format == VK_FORMAT_B8G8R8A8_SRGB
				//				&& f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				//			return f;
				//		}
				//	}
				//	return formats[0];
				//}(formats);
				//
				//::VkPresentModeKHR mode = [](const auto& modes) {
				//	for (const auto& m : modes) {
				//		if (m == VK_PRESENT_MODE_MAILBOX_KHR) {
				//			return m;
				//		}
				//	}
				//	return VK_PRESENT_MODE_FIFO_KHR;
				//}(modes);
				//
				//
				//::VkExtent2D extent = [](const auto& capabilities, auto& window) -> ::VkExtent2D {
				//	if (capabilities.current_extent().width != UINT32_MAX) {
				//		return capabilities.current_extent();
				//	}
				//	int width, height;
				//	::glfwGetFramebufferSize(window.underlying(), &width, &height);
				//	::VkExtent2D extent = {
				//		.width  = xns::clamp(static_cast<uint32_t>(width),  capabilities.min_image_extent().width,
				//				capabilities.max_image_extent().width),
				//		.height = xns::clamp(static_cast<uint32_t>(height), capabilities.min_image_extent().height,
				//				capabilities.max_image_extent().height),
				//	};
				//	return extent;
				//
				//}(capabilities, _window);
				//
				//
				//_swapchain = vulkan::swapchain{_ldevice, _surface, capabilities, format, mode, extent};
				//


#include "vulkan_library.hpp"


void make_lib(void) {


	// exemple of usage
	xns::literal_map<vk::pipeline_shader_stage_info, "basic_vertex", "basic_fragment"> shader_stages;

	xns::get<"basic_vertex">(shader_stages) = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = VK_NULL_HANDLE,
		.pName = "main",
		.pSpecializationInfo = nullptr,
	};

	xns::get<"basic_fragment">(shader_stages) = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = VK_NULL_HANDLE,
		.pName = "main",
		.pSpecializationInfo = nullptr,
	};

	//xns::get<"basic_vertex">(shader_stages).module = VK_NULL_HANDLE;

	// exemple of usage
	constexpr xns::literal_map<vk::pipeline_shader_stage_info, "basic_vertex", "basic_fragment"> shader_stages2 {
		vk::pipeline_shader_stage_info{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr, (VkPipelineShaderStageCreateFlags)0,
			VK_SHADER_STAGE_VERTEX_BIT,
			VK_NULL_HANDLE,
			"main",
			nullptr
		},
		vk::pipeline_shader_stage_info{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr, (VkPipelineShaderStageCreateFlags)0,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			VK_NULL_HANDLE,
			"main",
			nullptr
		}
	};
}




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

	const vk::pipeline_layout_info layout_info{
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
	};


	vk::pipeline_layout layout{};

	::vkCreatePipelineLayout(VK_NULL_HANDLE /* device */,
							&layout_info, nullptr, &layout);


	//vk::render_pass render_pass{};

	const vk::graphics_pipeline_info info{
		// type of struct
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		// pointer to next struct
		.pNext = nullptr,
		// flags
		.flags = 0,
		// shader stage count
		.stageCount = 2,
		// shader stages
		.pStages = shader_stages,
		// vertex input state
		.pVertexInputState = &vertex_input,
		// input assembly state
		.pInputAssemblyState = &input_assembly_info,
		// tesselation state
		.pTessellationState = &tesselation,
		// viewport state
		.pViewportState = &viewport_info,
		// rasterization state
		.pRasterizationState = &rasterizer,
		// multisample state
		.pMultisampleState = &multisampling,
		// depth stencil state
		.pDepthStencilState = &depth_stencil,
		// color blend state
		.pColorBlendState = &color_blend,
		// dynamic state
		.pDynamicState = &dynamic,
		// pipeline layout
		.layout = layout,
		// render pass
		.renderPass = VK_NULL_HANDLE,
		// subpass
		.subpass = 0,
		// base pipeline handle
		.basePipelineHandle = VK_NULL_HANDLE,
		// base pipeline index
		.basePipelineIndex = -1,
	};

	vk::pipeline pipeline{};

	::vkCreateGraphicsPipelines(VK_NULL_HANDLE /* device */,
								VK_NULL_HANDLE /* pipeline cache */,
								1, &info, nullptr, &pipeline);

	vk::pipeline_bind_point bind_point{VK_PIPELINE_BIND_POINT_GRAPHICS};


	::vkDestroyPipeline(VK_NULL_HANDLE /* device */, pipeline, nullptr);



}


void unamed(void) {






	// depth and stencil testing (not used yet)


	// color blending


}

#include "renderer.hpp"

int main(void) {

	//try {
	//	try {
	//	vulkan::instance::shared();
	//
	//} catch (const vulkan::exception& except) {
	//	except.what();
	//	return 1;
	//}
	//} catch (const xns::exception& except) {
	//	xns::print(except.get_message());
	//	return 1;
	//}
	//
	//
	//return 0;


	//auto module = vulkan::make_shared(device, info);

	//vulkan::shared<vk::device> device{};

	//auto device = vulkan::make_shared(vk::device_info{/* */}, vk::physical_device{/* */});

	//auto module = vk::create(device, vk::shader_module_info{});
	//auto managed = vulkan::make_managed(module, device);

	//vulkan::managed<vk::shader_module,
	//				vulkan::shared<vk::device>>
	//module_managed{module, device};



		//> debug_messenger{};
	//vulkan::shared<vk::command_pool> command_pool{};

	//using command_pool = vulkan::managed<vk::command_pool, int, vulkan::shared<vk::device>>;

	/*
	using command_pool = vulkan::managed<
		vk::command_pool,
		vulkan::shared<vk::device>
		>;

	using command_buffer = vulkan::managed<
		vk::command_buffer,
		command_pool,
		vulkan::shared<vk::device>
		>;
		*/

	//using test = vulkan::managed<
	//	vk::shader_module,
	//	shader_module
	//	>;

	//command_pool pool{};

	//command_buffer buffer{};


	//vulkan::resource<vk::swapchain,
	//				vulkan::shared<vk::device>,
	//				command_pool
	//					> swapchain{};


	/*
	static_assert(vulkan::is_managed<
			//int
			vulkan::managed<int>
			>, "is not managed");
			*/


	//vulkan::instance::shared();



	// memory try block
	try {
		try { // vulkan try block
			engine::renderer renderer;
			renderer.launch();
		} catch (const vulkan::exception& except) {
			except.what();
			return 1;
		}
	} catch (const xns::exception& except) {
		xns::print(except.get_message());
		return 1;
	}
	return 0;
}

	//vulkan::shader_module module;
	//vulkan::shader_library library;

	//glfw::window win;
	//glfw::events events;
	//events.run(win);

	//vulkan::surface surface{instance, win};

	//vulkan::queue_families families{device};

