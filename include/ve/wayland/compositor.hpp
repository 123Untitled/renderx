#ifndef ___RENDERX_WAYLAND_COMPOSITOR___
#define ___RENDERX_WAYLAND_COMPOSITOR___

#include "ve/os.hpp"

#if defined(RENDERX_OS_LINUX)

#include "ve/wayland/display.hpp"
#include <wayland-client.h>


// -- W A Y L A N D  N A M E S P A C E ----------------------------------------

namespace wl {


	// -- C O M P O S I T O R -------------------------------------------------

	class compositor final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = wl::compositor;


			// -- private members ---------------------------------------------

			/* compositor */
			struct ::wl_compositor* _compositor;


			// -- private static methods --------------------------------------

			// callback pour récupérer le compositor
			static auto _registry_handler(void* data, struct ::wl_registry* registry,
					uint32_t id, const char *interface, uint32_t version) noexcept -> void {

				// get compositor
				auto& self = *static_cast<___self*>(data);

				if (__builtin_strcmp(interface, "wl_compositor") == 0) {
					self._compositor = static_cast<struct ::wl_compositor*>(
										::wl_registry_bind(registry, id, &::wl_compositor_interface, 1));
				}
			}

			// Callback pour gérer les événements de suppression
			static void _registry_remover(void *data, struct wl_registry *registry, uint32_t id) {
				// Do nothing in this minimal example
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* display constructor */
			compositor(wl::display& display)
			: _compositor{nullptr} {

				const struct ::wl_registry_listener rlistener {
					.global = _registry_handler,
					.global_remove = _registry_remover
				};

				// Obtenir le registre des objets du serveur Wayland
				auto& registry = display.registry();

				::wl_registry_add_listener(&registry, &rlistener, this);

				// wait for compositor binding
				display.roundtrip();

				if (!_compositor)
					throw std::runtime_error("Could not bind to wayland compositor");
			}


			// -- public accessors --------------------------------------------

			/* const get */
			auto get(void) const noexcept -> const struct ::wl_compositor* {
				return _compositor;
			}

			/* get */
			auto get(void) noexcept -> struct ::wl_compositor* {
				return _compositor;
			}

	}; // class compositor

} // namespace wl

#endif // RENDERX_OS_LINUX

#endif // ___RENDERX_WAYLAND_COMPOSITOR___
