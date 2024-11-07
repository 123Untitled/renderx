#include "ve/all.hpp"

#include "ve/libraries.hpp"

#include "ve/vulkan/pipeline/library.hpp"
#include "ve/vulkan/descriptor/allocator.hpp"
#include "ve/singleton.hpp"

#include "ve/geometry/skybox.hpp"

auto main(int, char**) -> int {

	// wayland

	ve::mesh::skybox skybox;

	//skybox.to_vertex();




	::signal(SIGINT, [](int) {
		ve::running::stop();
		ve::write("\n");
	});


	// launch renderer
	try {
		ve::renderer renderer;
		renderer.run();

	}
	// ve exceptions
	catch (const ve::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}
	// std exceptions
	catch (const std::exception& except) {
		std::cerr << except.what() << std::endl;
		return EXIT_FAILURE;
	}
	// unknown exceptions
	catch (...) {
		std::cerr << "unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
