#ifndef ___RENDERX_WAYLAND_SURFACE___
#define ___RENDERX_WAYLAND_SURFACE___

#include "renderx/os.hpp"

#if defined(RENDERX_OS_LINUX)

#include "renderx/wayland/compositor.hpp"
#include <wayland-client.h>
#include <stdexcept>


// -- W A Y L A N D  N A M E S P A C E ----------------------------------------

namespace wl {

	// -- S U R F A C E -------------------------------------------------------

	class surface final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = wl::surface;


			// -- private members ---------------------------------------------

			/* surface */
			struct ::wl_surface* _surface;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			surface(wl::compositor& compositor)
			: _surface{::wl_compositor_create_surface(compositor.get())} {

				// check surface
				if (_surface == nullptr)
					throw std::runtime_error("Could not create wayland surface");

			}

			/* destructor */
			~surface(void) noexcept {

				// destroy surface
				::wl_surface_destroy(_surface);
			}


			// -- public methods ----------------------------------------------

			/* commit */
			auto commit(void) const -> void {
				::wl_surface_commit(_surface);
			}



			// -- public accessors --------------------------------------------

			/* const get */
			auto get(void) const noexcept -> const struct ::wl_surface& {
				return *_surface;
			}

			/* get */
			auto get(void) noexcept -> struct ::wl_surface& {
				return *_surface;
			}

	}; // class surface

} // namespace wl

#endif // RENDERX_OS_LINUX
#endif // ___RENDERX_WAYLAND_SURFACE___
