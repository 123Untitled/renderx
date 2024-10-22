#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vulkan/surface.hpp"
#include "ve/vulkan/shader_module.hpp"
#include "ve/vulkan/swapchain.hpp"
#include "ve/vulkan/command_pool.hpp"
#include "ve/vulkan/command_buffer.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/os.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/exceptions.hpp"
#include "ve/shader_library.hpp"
#include "ve/vulkan/libraries/library.hpp"
#include "ve/vulkan/not_used/resource.hpp"
#include "ve/renderer.hpp"
#include "ve/vulkan/pipeline.hpp"
#include "ve/vulkan/commands.hpp"
#include "ve/vulkan/specialization.hpp"
#include "ve/vertex/position.hpp"
#include "ve/vertex/rotation.hpp"
#include "ve/shader_library.hpp"
#include "ve/vulkan/fence.hpp"
#include "ve/vertex/normal.hpp"
#include "ve/vulkan/allocator.hpp"
#include "ve/object.hpp"
#include "ve/transform.hpp"
#include "ve/running.hpp"
#include "ve/system/directory.hpp"
#include "ve/containers/static_map.hpp"

#include <signal.h>

#include "ve/vulkan/instance.hpp"
#include "ve/wayland/wayland.hpp"


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


#include "ve/obj_parser.hpp"
#include "ve/geometry/mesh_library.hpp"

#include "ve/geometry/icosphere.hpp"
#include "ve/structures/vector3.hpp"
#include "ve/math/pow.hpp"
#include "ve/structures/matrix.hpp"

int main(void) {



	// array constructor
	ve::matrix<float, 3U, 2U> mat2{
		{
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f
		}
	};


	// multi dimensional array constructor
	ve::matrix<float, 3U, 2U> mat1{
		{
			{1.0f, 2.0f},
			{3.0f, 4.0f},
			{5.0f, 6.0f}
		}
	};


	// variadic constructor
	ve::matrix<float, 3U, 2U> mat0{
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f
	};


	mat0 -= mat1;

	// row constructor
	//ve::matrix<float, 2, 2> mat3{
	//		{1.0f, 2.0f},
	//		{3.0f, 4.0f}
	//};

	return 0;


	//using matrix = ve::matrix<float, 2, 2>;

	return 0;




	//rx::obj_parser::parse("assets/models/cube.obj");
	//
	//return 0;

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
		ve::write("\n");
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
