/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_GLFW_WINDOW___
#define ___ENGINE_GLFW_WINDOW___

#include "ve/glfw/glfw.hpp"
#include "ve/glfw/typedefs.hpp"

#include "ve/vk/typedefs.hpp"


// -- G L F W -----------------------------------------------------------------

namespace glfw {


	// -- W I N D O W ---------------------------------------------------------

	class window final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = glfw::window;


			// -- private members ---------------------------------------------

			/* window */
			::glfw_window* _window;

			/* resize */
			bool _resize;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) noexcept -> ___self&;

			/* size callback */
			static auto _size_callback(::glfw_window* const, const int, const int) noexcept -> void;

			/* close callback */
			static auto _close_callback(::glfw_window* const) noexcept -> void;

			/* iconify callback */
			static auto _iconify_callback(::glfw_window* const, const int) noexcept -> void;

			/* focus callback */
			static auto _focus_callback(::glfw_window* const, const int) noexcept -> void;

			/* maximize callback */
			static auto _maximize_callback(::glfw_window* const, const int) noexcept -> void;

			/* refresh callback */
			static auto _refresh_callback(::glfw_window* const) noexcept -> void;

			/* framebuffer size callback */
			static auto _framebuffer_size_callback(::glfw_window* const, const int, const int) noexcept -> void;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			window(void);

			/* deleted copy constructor */
			window(const ___self&) = delete;

			/* deleted move constructor */
			window(___self&&) = delete;

			/* destructor */
			~window(void) noexcept;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static accessors -------------------------------------

			/* shared */
			static auto shared(void) noexcept -> ::glfw_window&;

			/* should close */
			static auto should_close(void) noexcept -> bool;


			// -- public static methods ---------------------------------------

			/* hide */
			static auto hide(void) noexcept -> void;

			/* show */
			static auto show(void) noexcept -> void;

			/* framebuffer size */
			static auto framebuffer_size(void) -> vk::extent2D;

			/* resized */
			static auto resized(void) noexcept -> bool;

	}; // class window

} // namespace glfw

#endif // ___ENGINE_GLFW_WINDOW___
