#ifndef ___RENDERX_WAYLAND_WINDOW___
#define ___RENDERX_WAYLAND_WINDOW___

#include "ve/os.hpp"

#if defined(RENDERX_OS_LINUX)

#include "ve/wayland/compositor.hpp"
#include "ve/wayland/display.hpp"
#include "ve/wayland/surface.hpp"

#include <wayland-client.h>


// -- W A Y L A N D  N A M E S P A C E ----------------------------------------

namespace wl {


	// -- W I N D O W ---------------------------------------------------------

	class window final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = wl::window;


			// -- private members ---------------------------------------------

			/* display */
			wl::display _display;

			/* compositor */
			wl::compositor _compositor;

			/* surface */
			wl::surface _surface;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self shared{};
				return shared;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			window(void)
			: _display{},
			  _compositor{_display},
			  _surface{_compositor} {
			}

			/* destructor */
			~window(void) noexcept = default;


		public:

			// -- public static methods ---------------------------------------

			/* display */
			static auto display(void) -> wl::display& {
				return ___self::_shared()._display;
			}

			/* compositor */
			static auto compositor(void) -> wl::compositor& {
				return ___self::_shared()._compositor;
			}

			/* surface */
			static auto surface(void) -> wl::surface& {
				return ___self::_shared()._surface;
			}

	}; // class window

} // namespace wl

#endif // RENDERX_OS_LINUX

#endif // ___RENDERX_WAYLAND_WINDOW___

	// wayland
	/*
	{
		wl::display display;
		wl::compositor compositor{display};
		wl::surface surface{compositor};

		create_vulkan_surface(display, surface);

		surface.commit();

		display.roundtrip();

		std::cout << "Wayland display: " << &display.get() << std::endl;
		while (display.dispatch() != 0U) {
			// do nothing
		}

		sleep(1);

		return 0;
	}
	*/
