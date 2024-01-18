#ifndef ENGINE_GLFW_WINDOW_HPP
#define ENGINE_GLFW_WINDOW_HPP

#include "glfw_system.hpp"

#include "exceptions.hpp"

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
			window(void);

			/* deleted copy constructor */
			window(const self&) = delete;

			/* move constructor */
			window(self&&) noexcept;

			/* destructor */
			~window(void) noexcept;


			// -- public address operators ------------------------------------

			/* ::GLFWwindow* address operator */
			auto operator&(void) noexcept -> ::GLFWwindow* {
				return _window;
			}



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
