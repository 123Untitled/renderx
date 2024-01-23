#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <xns>
#include <vulkan/vulkan.h>

#include "basic_vertex.hpp"

#include "vulkan_swapchain.hpp"
#include "vulkan_semaphore.hpp"
#include "vulkan_queue.hpp"
#include "glfw_events.hpp"

#include "shader_library.hpp"



// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::renderer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderer(void);

			/* destructor */
			~renderer(void) noexcept;


			// -- public methods ----------------------------------------------

			/* draw frame */
			auto draw_frame(void) -> void;


			/* launch */
			auto launch(void) -> void;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;



		private:

			// -- private methods ---------------------------------------------

			/* initialize */
			auto initialize(void) -> void;


			// -- private members ---------------------------------------------

			/* vulkan instance */
			vulkan::instance _instance;

			/* window */
			glfw::window _window;

			/* gflw events */
			glfw::events _events;

			/* surface */
			vulkan::surface _surface;

			/* physical device */
			vulkan::physical_device _pdevice;

			/* device */
			vulkan::logical_device _ldevice;

			/* swapchain */
			vulkan::swapchain _swapchain;

			/* command pool */
			vulkan::command_pool _command_pool;

			/* image available semaphore */
			vulkan::semaphore _image_available;

			/* render finished semaphore */
			vulkan::semaphore _render_finished;

			/* shader library */
			shader_library _shaders;



	}; // class renderer

} // namespace engine

#endif // ENGINE_RENDERER_HPP
