#define GLFW_INCLUDE_VULKAN

#include "os.hpp"
#include <simd/simd.h>

#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_logical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_shader_module.hpp"

#include "meta_vertex.hpp"
#include "basic_vertex.hpp"

#include "exceptions.hpp"


namespace vulkan {

	class vertex_descriptor final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::vertex_descriptor;

			/* vertex input binding description */
			using binding = ::VkVertexInputBindingDescription;

			/* vertex input attribute description */
			using attribute = ::VkVertexInputAttributeDescription;


			// -- public lifecycle --------------------------------------------


		private:

			// -- private members ---------------------------------------------

			/* vertex input binding descriptions */
			std::vector<binding> _bindings;

	};
}

namespace engine {

	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::renderer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderer(void)
			:	_window{},
				_instance{},
				_surface{_instance, _window},
				_pdevice{vulkan::physical_device::pick(_instance)},
				_ldevice{_pdevice, _surface} {
			}


			/* run */
			auto run(void) -> void {

				glfw::events events;
				events.run(_window);
			}


		private:

			// -- private members ---------------------------------------------

			/* window */
			glfw::window _window;

			/* instance */
			vulkan::instance _instance;

			/* surface */
			vulkan::surface _surface;

			/* physical device */
			vulkan::physical_device _pdevice;

			/* device */
			vulkan::logical_device _ldevice;


	};

}




int main(void) {

	try {
		engine::renderer renderer;
		renderer.run();
	} catch (const engine::exception& except) {
		except.print();
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

