/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#define GLFW_INCLUDE_VULKAN


#include "engine/glfw/window.hpp"
#include "engine/glfw/events.hpp"

#include "engine/vulkan/physical_device.hpp"
#include "engine/vulkan/device.hpp"
#include "engine/vulkan/surface.hpp"
#include "engine/vulkan/shader_module.hpp"
#include "engine/vulkan/swapchain.hpp"
#include "engine/vulkan/command_pool.hpp"
#include "engine/vulkan/command_buffer.hpp"

#include "engine/vk/typedefs.hpp"
#include "engine/vk/shared.hpp"

#include "engine/os.hpp"
#include "engine/vertex/vertex.hpp"
#include "engine/exceptions.hpp"
#include "engine/shader_library.hpp"

#include <xns/literal_map.hpp>

#include "engine/vulkan/libraries/library.hpp"

#include "engine/vulkan/not_used/resource.hpp"

#include "engine/renderer.hpp"

#include "engine/vulkan/pipeline.hpp"

#include "engine/vk/vector.hpp"
#include "engine/vulkan/commands.hpp"

#include "engine/vulkan/specialization.hpp"



#include "engine/vertex/position.hpp"
#include "engine/vertex/rotation.hpp"


// note: analyze <vulkan/vulkan.hpp> to get ideas for my cpp wrapper

#include "engine/shader_library.hpp"

int main(void) {



	/*
	engine::vertex v{vx::float3{1.0f, 2.0f, 3.0f},
					 vx::rotation{4.0f, 5.0f, 6.0f}};

	v.print_info();
	*/


	// launch renderer
	try {
		engine::renderer renderer;
		renderer.launch();
	}

	// vulkan catch block
	catch (const vk::exception& except) {
		except.what();
		return EXIT_FAILURE;
	}

	catch (const engine::exception& except) {
		except.print();
		return EXIT_FAILURE;
	}

	// memory catch block
	catch (const xns::exception& except) {
		std::cerr << except.message() << std::endl;
		return EXIT_FAILURE;
	}

	catch (...) {
		std::cerr << "unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



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
