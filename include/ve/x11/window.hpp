#ifndef ___RENDERX_X11_WINDOW___
#define ___RENDERX_X11_WINDOW___

#include "ve/os.hpp"

#if defined(RENDERX_OS_LINUX)

#include <X11/Xlib.h>


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- W I N D O W ---------------------------------------------------------

	class window final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::window;


			// -- private members ---------------------------------------------

			/* display */
			::Display* _display;

			/* window */
			::Window _window;

			/* screen */
			::Screen* _screen;

			/* screen id */
			int _screenId;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			window(void)
			: _display{nullptr},
			  _window{0},
			  _screen{nullptr},
			  _screenId{0} {

				// open the display
				_display = XOpenDisplay(nullptr);
				if (_display == nullptr) {
					throw std::runtime_error("Could not open display");
				}

				// get the screen
				//_screen = ScreenOfDisplay(_display, DefaultScreen(_display));
				_screen = DefaultScreenOfDisplay(_display);

				// get the screen id
				_screenId = DefaultScreen(_display);

				// open the window
				_window = ::XCreateSimpleWindow(
								// display
								_display,
								// parent window
								::RootWindowOfScreen(_screen), // RootWindow(_display, _screenId),
								// x
								0,
								// y
								0,
								// width
								320,
								// height
								200,
								// border width
								1,
								// border color
								BlackPixel(_display, _screenId),
								// background color
								WhitePixel(_display, _screenId)
							);

				if (_window == 0) {
					throw std::runtime_error("Could not create window");
				}

				// show the window
				::XClearWindow(_display, _window);

				// map window
				::XMapRaised(_display, _window);

				// select input
				::XSelectInput(_display, _window,
						KeyPressMask | KeyReleaseMask | KeymapStateMask
						| LeaveWindowMask);


			}

	}; // class window

} // namespace rx

#endif // RENDERX_OS_LINUX

#endif // ___RENDERX_X11_WINDOW___
