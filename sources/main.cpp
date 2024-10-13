#include "renderx/vulkan/physical_device.hpp"
#include "renderx/vulkan/device.hpp"
#include "renderx/vulkan/surface.hpp"
#include "renderx/vulkan/shader_module.hpp"
#include "renderx/vulkan/swapchain.hpp"
#include "renderx/vulkan/command_pool.hpp"
#include "renderx/vulkan/command_buffer.hpp"
#include "renderx/vk/typedefs.hpp"
#include "renderx/os.hpp"
#include "renderx/vertex/vertex.hpp"
#include "renderx/exceptions.hpp"
#include "renderx/shader_library.hpp"
#include "renderx/vulkan/libraries/library.hpp"
#include "renderx/vulkan/not_used/resource.hpp"
#include "renderx/renderer.hpp"
#include "renderx/vulkan/pipeline.hpp"
#include "renderx/vulkan/commands.hpp"
#include "renderx/vulkan/specialization.hpp"
#include "renderx/vertex/position.hpp"
#include "renderx/vertex/rotation.hpp"
#include "renderx/shader_library.hpp"
#include "renderx/vulkan/fence.hpp"
#include "renderx/vertex/normal.hpp"
#include "renderx/vulkan/allocator.hpp"
#include "renderx/object.hpp"
#include "renderx/transform.hpp"
#include "renderx/running.hpp"
#include "renderx/system/directory.hpp"
#include "renderx/containers/static_map.hpp"



int main(void) {


	//glfw::window::resized();
	//
	//while (glfw::window::should_close() == false) {
	//	glfw::events::wait();
	//}
	//
	//return 0;



	//xe::static_map<vulkan::shader_module<VK_SHADER_STAGE_VERTEX_BIT>,
	//	"basic"> m{std::string{"shaders/basic.vert.spv"}};
	//
	//
	//m.for_each([](const auto& value) {
	//		});
	//

	::signal(SIGINT, [](int) {
		rx::running::stop();
		rx::write("\n");
	});


	// launch renderer
	try {
		rx::renderer renderer;
		renderer.run();
	}


	// vulkan catch block
	catch (const vk::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}

	catch (const std::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}

	catch (const engine::exception& except) {
		except.print();
		return EXIT_FAILURE;
	}

	catch (const char* except) {
		std::cerr << except << std::endl;
		return EXIT_FAILURE;
	}
	catch (const std::string& except) {
		std::cerr << except << std::endl;
		return EXIT_FAILURE;
	}

	catch (...) {
		std::cerr << "unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
