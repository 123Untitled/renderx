/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_SDL_WINDOW_HPP___
#define ___RENDERX_SDL_WINDOW_HPP___

#include "renderx/sdl/typedefs.hpp"
#include "engine/types.hpp"


// -- forward declaration -----------------------------------------------------

/* window */
struct sdl_window;

/* display mode */
struct sdl_display_mode;


// -- S D L -------------------------------------------------------------------

namespace rx::sdl {


	// -- W I N D O W ---------------------------------------------------------

	class window final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::sdl::window;


			// -- private members ---------------------------------------------

			/* window */
			::sdl_window* _window;

			/* width */
			rx::u16 _width;

			/* height */
			rx::u16 _height;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;


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

			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> sdl_window&;

			/* width */
			static auto width(void) -> rx::u16;

			/* height */
			static auto height(void) -> rx::u16;

			/* ratio */
			static auto ratio(void) -> float;

	}; // class window

} // namespace rx::sdl

#endif // ___RENDERX_SDL_WINDOW_HPP___
