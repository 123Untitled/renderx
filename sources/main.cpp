#include "ve/all.hpp"

#include "ve/libraries.hpp"

#include "ve/vulkan/pipeline/library.hpp"
#include "ve/vulkan/descriptor/allocator.hpp"
#include "ve/singleton.hpp"

#include "ve/geometry/skybox.hpp"

auto main(int, char**) -> int {

	// wayland
	{
		wl::display display;
		wl::compositor compositor{display};
		wl::surface surface{compositor};

		//create_vulkan_surface(display, surface);

		surface.commit();

		display.roundtrip();

		std::cout << "Wayland display: " << &display.get() << std::endl;
		while (display.dispatch() != 0U) {
			// do nothing
		}

		sleep(1);

		return 0;
	}

	return 0;

	ve::mesh::skybox skybox;

	skybox.to_vertex();




	::signal(SIGINT, [](int) {
		ve::running::stop();
		ve::write("\n");
	});


	// launch renderer
	try {
		ve::renderer renderer;
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
