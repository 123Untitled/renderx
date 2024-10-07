/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#include "renderx/sdl/system.hpp"
#include "renderx/sdl/exception.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "engine/os.hpp"
#include "renderx/sdl/typedefs.hpp"


// -- private static methods --------------------------------------------------

/* shared */
auto rx::sdl::system::_shared(void) -> ___self& {
	static ___self ___ins;
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
rx::sdl::system::system(void) {

	// flags
	constexpr auto flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;// | SDL_INIT_AUDIO;

	// initialize SDL
	if (::sdl_init_subsystem(flags) == false)
		rx::sdl::exception{"Failed to initialize SDL subsystems."};


	// raw 0, wrapped 1
	if (::sdl_set_hint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "0") == false
	// mouse scale
	 || ::sdl_set_hint(SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE, "0.1") == false
	// unscaled 0, scaled 1 (system mouse acceleration curve)
	 || ::sdl_set_hint(SDL_HINT_MOUSE_RELATIVE_SYSTEM_SCALE, "0") == false
	// motion event should be generated for mouse warping in relative mode.
	 || ::sdl_set_hint(SDL_HINT_MOUSE_RELATIVE_WARP_MOTION, "0") == false
	// relative mouse mode constrains the mouse to the center of the window (1 center, 0 top-left)
	 || ::sdl_set_hint(SDL_HINT_MOUSE_RELATIVE_MODE_CENTER, "1") == false)
		rx::sdl::exception{"Failed to set SDL hint."};
}


/* destructor */
rx::sdl::system::~system(void) noexcept {

	// quit SDL
	::sdl_quit();
}


// -- private methods ---------------------------------------------------------

/* vulkan required extensions */
auto rx::sdl::system::_vulkan_required_extensions(void) const -> vk::vector<const char*> {

	// get required extensions
	vk::u32                 count = 0U;
	const char* const* extensions = ::sdl_vulkan_get_instance_extensions(&count);

	if (extensions == nullptr)
		throw rx::sdl::exception{"Failed to get SDL required instance extensions."};

	vk::vector<const char*> result;
	result.reserve(count);

	// check macos system
	#if defined(ENGINE_OS_MACOS)
	result.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	result.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
	#endif

	// validation layers check
	#if defined(ENGINE_VL_DEBUG)
	result.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif

	// loop over extensions
	for (vk::u32 i = 0U; i < count; ++i)
		result.push_back(extensions[i]);

	// done
	return result;
}


// -- public static methods ---------------------------------------------------

/* init */
auto rx::sdl::system::init(void) -> void {

	// initialize SDL
	static_cast<void>(___self::_shared());
}

/* vulkan required extensions */
auto rx::sdl::system::vulkan_required_extensions(void) -> vk::vector<const char*> {

	// return extensions
	return ___self::_shared()._vulkan_required_extensions();
}
