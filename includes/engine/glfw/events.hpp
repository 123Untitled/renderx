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

#ifndef ___ENGINE_GLFW_EVENTS_HPP___
#define ___ENGINE_GLFW_EVENTS_HPP___

#include <GLFW/glfw3.h>


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


			/* poll */
			auto poll(void) -> void {
				::glfwPollEvents();
			}

			/* wait */
			auto wait(void) -> void {
				::glfwWaitEvents();
			}

	}; // class events

} // namespace glfw

#endif // ENGINE_GLFW_EVENTS_HPP
