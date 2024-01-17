#ifndef ENGINE_GLFW_WINDOW_HPP
#define ENGINE_GLFW_WINDOW_HPP

#include <GLFW/glfw3.h>
#include "glfw_system.hpp"


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {


	// -- W I N D O W ---------------------------------------------------------

	class window final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = glfw::window;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			window(void) noexcept;

			/* deleted copy constructor */
			window(const self&) = delete;

			/* move constructor */
			window(self&&) noexcept;

			/* destructor */
			~window(void) noexcept;


			// -- public conversion operators ---------------------------------

			///* ::GLFWwindow* conversion operator */
			//operator ::GLFWwindow*(void) noexcept;


			// -- public accessors --------------------------------------------

			/* should close */
			auto should_close(void) const noexcept -> bool;


		private:

			// -- private members ---------------------------------------------

			/* window */
			::GLFWwindow* _window;

	};

}

#endif // ENGINE_GLFW_WINDOW_HPP
