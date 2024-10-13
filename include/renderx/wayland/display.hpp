#ifndef ___RENDERX_WAYLAND_DISPLAY___
#define ___RENDERX_WAYLAND_DISPLAY___

#include "renderx/os.hpp"

#if defined(RENDERX_OS_LINUX)

#include <stdexcept>
#include <wayland-client.h>


// -- W A Y L A N D  N A M E S P A C E ----------------------------------------

namespace wl {


	// -- D I S P L A Y -------------------------------------------------------

	class display final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = wl::display;


			// -- private members ---------------------------------------------

			/* display */
			struct ::wl_display* _display;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			display(void)
			: _display{::wl_display_connect(nullptr)} {

				// check display
				if (_display == nullptr)
					throw std::runtime_error("Could not connect to wayland display");
			}

			/* destructor */
			~display(void) noexcept {

				// disconnect display
				::wl_display_disconnect(_display);
			}


			// -- public methods ----------------------------------------------

			/* dispatch */
			auto dispatch(void) const -> ::size_t {

				// process incoming events
				const int state = ::wl_display_dispatch(_display);

				if (state == -1)
					throw std::runtime_error("Error dispatching wayland display");

				return static_cast<::size_t>(state);
			}

			/* roundtrip */
			auto roundtrip(void) const -> ::size_t {

				// process incoming events
				const int state = ::wl_display_roundtrip(_display);

				if (state == -1)
					throw std::runtime_error("Error roundtripping wayland display");

				return static_cast<::size_t>(state);
			}


			// -- public accessors --------------------------------------------

			/* const get */
			auto get(void) const noexcept -> const struct ::wl_display& {
				return *_display;
			}

			/* get */
			auto get(void) noexcept -> struct ::wl_display& {
				return *_display;
			}

			/* registry */
			auto registry(void) const noexcept -> struct ::wl_registry& {
				return *::wl_display_get_registry(_display);
				// maybe check for nullptr
			}

	}; // class display

} // namespace wl

#endif // RENDERX_OS_LINUX

#endif // ___RENDERX_WAYLAND_DISPLAY___
