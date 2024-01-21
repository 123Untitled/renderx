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
#include "vulkan_extension_properties.hpp"
#include "vulkan_command_pool.hpp"
#include "vulkan_command_buffer.hpp"

#include "vk_typedefs.hpp"

#include "os.hpp"
#include "meta_vertex.hpp"
#include "basic_vertex.hpp"
#include "exceptions.hpp"
#include "shader_library.hpp"

#include <xns>




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




void unamed(void) {

	const vk::primitive_topology topologies[] = {
		VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
		VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
		VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
		VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
		VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
		VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
	};


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

	// viewport state
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

	// depth and stencil testing (not used yet)


	// color blending


}


#include "renderer.hpp"

int main(void) {

	// memory try block
	try {
		try { // vulkan try block
			engine::renderer renderer;
			//renderer.launch();
		} catch (const engine::exception& except) {
			except.print();
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

