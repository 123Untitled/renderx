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

#ifndef ENGINE_GLFW_SYSTEM_HEADER
#define ENGINE_GLFW_SYSTEM_HEADER

#define GLFW_INCLUDE_VULKAN

#include <xns/vector.hpp>


// -- forward declarations ----------------------------------------------------

/* GLFWwindow */
struct GLFWwindow;

/* GLFWmonitor */
struct GLFWmonitor;


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {


	// -- forward declarations ------------------------------------------------

	/* window */
	class window;


	// -- S Y S T E M ---------------------------------------------------------

	class system final {


		// -- friends ---------------------------------------------------------

		/* window as friend */
		friend class window;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = glfw::system;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			system(const self&) = delete;

			/* deleted move constructor */
			system(self&&) = delete;

			/* destructor */
			~system(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* vulkan required extensions */
			auto vulkan_required_extensions(void) -> xns::vector<const char*>;


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			system(void);


			// -- private methods ---------------------------------------------

			/* new window */
			auto new_window(const int, const int, const char*,
							GLFWmonitor*, GLFWwindow*) -> GLFWwindow*;


			// -- private static methods --------------------------------------

			/* error callback */
			static auto error_callback(int, const char*) noexcept -> void;

	}; // class system

} // namespace glfw

#endif // ENGINE_GLFW_SYSTEM_HEADER
