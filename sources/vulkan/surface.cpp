#include "engine/vulkan/surface.hpp"

#include "engine/vulkan/instance.hpp"
#include "engine/exceptions.hpp"

#include "renderx/sdl/window.hpp"
#include <SDL3/SDL_vulkan.h>


// -- private static methods --------------------------------------------------

/* shared */
auto vulkan::surface::_shared(void) -> ___self& {
	static vulkan::surface ___ins{};
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void)
/* uninitialized surface */ {

	auto& instance = vulkan::instance::shared();
	auto&   window = rx::sdl::window::shared();

	// create surface
	if (::sdl_vulkan_create_surface(&window, instance, nullptr, &_surface) == false
		|| _surface == nullptr)
		throw engine::exception{"failed to create vulkan surface."};
}

/* destructor */
vulkan::surface::~surface(void) noexcept {

	// free surface
	::sdl_vulkan_destroy_surface(vulkan::instance::shared(), _surface, nullptr);
	//::vk_destroy_surface_khr(vulkan::instance::shared(), _surface, nullptr);
}


// -- public static accessors -------------------------------------------------

/* shared */
auto vulkan::surface::shared(void) -> vk::surface& {
	return ___self::_shared()._surface;
}
