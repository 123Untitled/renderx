/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#include "renderx/sdl/window.hpp"
#include "renderx/sdl/exception.hpp"
#include "renderx/sdl/system.hpp"
#include <SDL3/SDL.h>

#include <iostream>

// -- private static methods --------------------------------------------------

/* shared */
auto rx::sdl::window::_shared(void) -> ___self& {
	static ___self ___ins;
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
rx::sdl::window::window(void)
/* uninitialized window */ {

	// initialize sdl
	rx::sdl::system::init();

	// get desktop display mode
	const ::sdl_display_id id = 1U;
	const ::sdl_display_mode* display = ::sdl_get_current_display_mode(id);

	if (display == nullptr)
		throw rx::sdl::exception{"Failed to get current display mode"};

	std::cout << "display: " << display->w << "x" << display->h << std::endl;

	_width  = (display->w / 4) * 3;
	_height = (display->h / 4) * 3;


	// flags
	constexpr auto flags = SDL_WINDOW_VULKAN
						 | SDL_WINDOW_RESIZABLE
						 | SDL_WINDOW_HIGH_PIXEL_DENSITY
						 //| SDL_WINDOW_BORDERLESS
						 | SDL_WINDOW_MOUSE_RELATIVE_MODE;

	// create window
	_window = ::sdl_create_window("renderx", _width, _height, flags);

	if (_window == nullptr)
		throw rx::sdl::exception{"Failed to create SDL window"};
}

/* destructor */
rx::sdl::window::~window(void) noexcept {

	// release window
	::sdl_destroy_window(_window);
}


// -- public static methods ---------------------------------------------------

/* shared */
auto rx::sdl::window::shared(void) -> sdl_window& {
	return *(___self::_shared()._window);
}

/* width */
auto rx::sdl::window::width(void) -> rx::u16 {
	return ___self::_shared()._width;
}

/* height */
auto rx::sdl::window::height(void) -> rx::u16 {
	return ___self::_shared()._height;
}
