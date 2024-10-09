/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "engine/vulkan/physical_device.hpp"
#include "engine/vulkan/device.hpp"
#include "engine/vulkan/surface.hpp"
#include "engine/vulkan/shader_module.hpp"
#include "engine/vulkan/swapchain.hpp"
#include "engine/vulkan/command_pool.hpp"
#include "engine/vulkan/command_buffer.hpp"

#include "engine/vk/typedefs.hpp"

#include "engine/os.hpp"
#include "engine/vertex/vertex.hpp"
#include "engine/exceptions.hpp"
#include "engine/shader_library.hpp"

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
#include "engine/vulkan/fence.hpp"



#include "renderx/vertex/normal.hpp"


#include "renderx/vulkan/allocator.hpp"
#include "renderx/object.hpp"
#include "renderx/transform.hpp"



#include "renderx/running.hpp"

// include for event tap
#include <ApplicationServices/ApplicationServices.h>


int main(void) {

	::signal(SIGINT, [](int) {
		rx::running::stop();
		rx::write("\n");
	});






	// launch as daemon

	/*
	rx::object obj;

	obj.position() += 1.0f;


	rx::transform<float, 3U> t;

	t.rotation() += 2.0f;

	const auto& r = t.rotation();
	const auto& p = t.position();
	const auto& s = t.scale();

	std::cout << "rotation: " << r.x << ", " << r.y << ", " << r.z << std::endl;
	std::cout << "position: " << p.x << ", " << p.y << ", " << p.z << std::endl;
	std::cout << "scale: " << s.x << ", " << s.y << ", " << s.z << std::endl;
	*/

	// launch renderer
	try {
		engine::renderer renderer;
		renderer.run();
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
