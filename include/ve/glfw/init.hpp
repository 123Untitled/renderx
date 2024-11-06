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

#ifndef ___ENGINE_GLFW_INIT_HPP___
#define ___ENGINE_GLFW_INIT_HPP___

#include "ve/glfw/glfw.hpp"
#include "ve/exceptions.hpp"
#include "ve/glfw/typedefs.hpp"


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {


	// -- I N I T -------------------------------------------------------------

	class init final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = glfw::init;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			init(void) {

				if (::glfw_init() == GLFW_FALSE)
					throw ve::exception{"failed to initialize glfw."};
			}

			/* deleted copy constructor */
			init(const ___self&) = delete;

			/* deleted move constructor */
			init(___self&&) = delete;

			/* destructor */
			~init(void) noexcept {
				// terminate glfw
				::glfw_terminate();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator = (const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator = (___self&&) -> ___self& = delete;

	}; // class init

} // namespace glfw

#endif // ___ENGINE_GLFW_INIT_HPP___
