/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_RENDERER_HEADER
#define ENGINE_RENDERER_HEADER

#include <xns>
#include <vulkan/vulkan.h>

#include "basic_vertex.hpp"

#include "vulkan_swapchain.hpp"
#include "vulkan_semaphore.hpp"
#include "vulkan_queue.hpp"
#include "glfw_events.hpp"

#include "shader_library.hpp"

#include "vulkan/global/instance.hpp"



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

			/* deleted copy constructor */
			renderer(const self&) = delete;

			/* deleted move constructor */
			renderer(self&&) noexcept = delete;

			/* destructor */
			~renderer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public methods ----------------------------------------------

			/* draw frame */
			auto draw_frame(void) -> void;

			/* launch */
			auto launch(void) -> void;


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

			/* command pool */
			vulkan::command_pool _command_pool;

			/* command buffer */
			vulkan::command_buffer _command_buffer;

			/* image available semaphore */
			vulkan::semaphore _image_available;

			/* render finished semaphore */
			vulkan::semaphore _render_finished;

			/* shader library */
			shader_library _shaders;

			/* render pass */
			vulkan::render_pass _render_pass;


	}; // class renderer

} // namespace engine

#endif // ENGINE_RENDERER_HEADER
