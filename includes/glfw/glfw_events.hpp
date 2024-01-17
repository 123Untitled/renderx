#ifndef ENGINE_GLFW_EVENTS_HPP
#define ENGINE_GLFW_EVENTS_HPP

#include <GLFW/glfw3.h>

#include "glfw_window.hpp"


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {

	// -- E V E N T S ---------------------------------------------------------

	class events final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = glfw::events;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			events(void) = default;

			/* deleted copy constructor */
			events(const self&) = delete;

			/* deleted move constructor */
			events(self&&) = delete;

			/* destructor */
			~events(void) = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			/* run */
			auto run(const glfw::window& window) -> void {

				static int i = 0;

				while (window.should_close() == false) {
					::glfwWaitEvents();
					//::glfwPollEvents();
					std::cout << "glfw event loop: " << i++ << std::endl;
				}

			}

		private:


	};

}

#endif // ENGINE_GLFW_EVENTS_HPP
