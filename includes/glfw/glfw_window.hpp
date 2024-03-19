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

#ifndef ENGINE_GLFW_WINDOW_HEADER
#define ENGINE_GLFW_WINDOW_HEADER

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
			window(void) noexcept;

			/* width and height constructor */
			window(const int, const int);

			/* deleted copy constructor */
			window(const self&) = delete;

			/* move constructor */
			window(self&&) noexcept;

			/* destructor */
			~window(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying pointer */
			auto underlying(void) noexcept -> ::GLFWwindow*;

			/* const underlying pointer */
			auto underlying(void) const noexcept -> const ::GLFWwindow*;

			/* should close */
			auto should_close(void) const noexcept -> bool;


		private:

			// -- private static methods --------------------------------------

			/* resize callback */
			static auto resize_callback(::GLFWwindow*, const int, const int) noexcept -> void;


			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* window */
			::GLFWwindow* _window;

	};

} // namespace glfw

#endif // ENGINE_GLFW_WINDOW_HEADER
