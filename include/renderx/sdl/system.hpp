/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_SDL_SYSTEM_HPP___
#define ___RENDERX_SDL_SYSTEM_HPP___

#include "engine/vk/typedefs.hpp"


// -- S D L -------------------------------------------------------------------

namespace rx::sdl {


	// -- S Y S T E M ---------------------------------------------------------

	/* system */
	class system final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::sdl::system;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			system(void);

			/* deleted copy constructor */
			system(const ___self&) = delete;

			/* deleted move constructor */
			system(___self&&) = delete;

			/* destructor */
			~system(void) noexcept;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private methods ---------------------------------------------

			/* vulkan required extensions */
			auto _vulkan_required_extensions(void) const -> vk::vector<const char*>;


		public:

			// -- public static methods ---------------------------------------

			/* init */
			static auto init(void) -> void;

			/* vulkan required extensions */
			static auto vulkan_required_extensions(void) -> vk::vector<const char*>;

	}; // class system

} // namespace rx::sdl

#endif // ___RENDERX_SDL_SYSTEM_HPP___
