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


#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_physical_device.hpp"
#include "vulkan_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_shader_module.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_command_pool.hpp"
#include "vulkan/command_buffer.hpp"

#include "vk_typedefs.hpp"
#include "vulkan/vk_shared.hpp"

#include "os.hpp"
#include "basic_vertex.hpp"
#include "exceptions.hpp"
#include "shader_library.hpp"

#include <xns/literal_map.hpp>

#include "vulkan_library.hpp"

#include "vulkan_resource.hpp"

#include "renderer.hpp"

#include "vulkan_pipeline.hpp"




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




#include "vulkan/vk_vector.hpp"
#include "vulkan/commands.hpp"


class _A {

	public:

		_A(void) noexcept {
		}

		_A(int&&) noexcept {
		}

		~_A(void) = default;

	private:

		int c;
};

// overload <<

std::ostream& operator<<(std::ostream& os, const _A& a) {
	os << "A";
	return os;
}


int main(void) {

	int i = 0;
	float f = 0.0f;

	std::cout << "sizeof _A: " << sizeof(_A) << std::endl;

	vulkan::specialization sp{123, _A{}, (short)4242, 99.9, 'x'};
	//vulkan::specialization<int, _A, short, double, char> sp{123, _A{}, (short)4242, 99.9, 'x'};
	//vulkan::specialization<int, short, double, char> sp{123, (short)4242, 99.9, 'x'};
	sp.print();

	//auto& e = sp[0];


	return 0;

	//try {
	//
	//	vulkan::command_pool<vk::void_bit> pool{};
	//
	//	vulkan::commands<vulkan::primary> cmds{pool};
	//
	//	vulkan::command_buffer<vulkan::primary>& buff = cmds[0];
	//
	//	buff.begin();
	//
	//	buff.end();
	//
	//	//auto com = pool.make_primary(100);
	//	//auto v2 = pool.make_secondary(100);
	//	//pool.reset_to_system();
	//	//pool.trim();
	//	//v.emplace_back(vk::command_buffer_info{});
	//
	//}
	//catch (const vk::exception& except) {
	//	except.what();
	//}
	//
	//return 0;



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

	// memory catch block
	catch (const xns::exception& except) {
		std::cerr << except.get_message() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
