#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <xns>
#include <vulkan/vulkan.h>

#include "vulkan_swapchain.hpp"
#include "vulkan_semaphore.hpp"
#include "vulkan_queue.hpp"
#include "glfw_events.hpp"


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

			// -- private members ---------------------------------------------

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

			/* image available semaphore */
			vulkan::semaphore _image_available;

			/* render finished semaphore */
			vulkan::semaphore _render_finished;


	}; // class renderer

} // namespace engine

#endif // ENGINE_RENDERER_HPP
