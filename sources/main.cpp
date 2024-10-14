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

#include <signal.h>

#include "renderx/vulkan/instance.hpp"
#include "renderx/wayland/wayland.hpp"

//
//auto create_vulkan_surface(wl::display& display, wl::surface& surface) -> void {
//
//	const vk::wayland_surface_create_info_khr info {
//		// structure type
//		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
//		// next structure
//		.pNext = nullptr,
//		// flags
//		.flags = 0U,
//		// wayland display
//		.display = &display.get(),
//		// wayland surface (window)
//		.surface = &surface.get()
//	};
//
//	vk::surface surface_khr;
//
//    // Créer la surface Vulkan avec Wayland
//    if (::vk_create_wayland_surface_khr(vulkan::instance::shared(),
//									&info, nullptr, &surface_khr) != VK_SUCCESS) {
//		throw std::runtime_error("Could not create vulkan surface");
//    }
//}



int main(void) {


	// wayland
	/*
	{
		wl::display display;
		wl::compositor compositor{display};
		wl::surface surface{compositor};

		create_vulkan_surface(display, surface);

		surface.commit();

		display.roundtrip();

		std::cout << "Wayland display: " << &display.get() << std::endl;
		while (display.dispatch() != 0U) {
			// do nothing
		}

		sleep(1);

		return 0;
	}
	*/




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
