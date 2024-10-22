/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_HINT___
#define ___RENDERX_HINT___

#include "ve/system/write.hpp"


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- H I N T  N A M E S P A C E ------------------------------------------

	namespace hint {


		/* success */
		template <rx::size_t ___sz>
		auto success(const char (&___msg)[___sz]) noexcept -> void {
			rx::write<STDOUT_FILENO>("\x1b[32m");
			rx::write<STDOUT_FILENO>(___msg);
			rx::write<STDOUT_FILENO>("\x1b[0m\n");
		}

		/* warning */
		template <rx::size_t ___sz>
		auto warning(const char (&___msg)[___sz]) noexcept -> void {
			rx::write<STDOUT_FILENO>("\x1b[33m");
			rx::write<STDOUT_FILENO>(___msg);
			rx::write<STDOUT_FILENO>("\x1b[0m\n");
		}

		/* error */
		template <rx::size_t ___sz>
		auto error(const char (&___msg)[___sz]) noexcept -> void {
			rx::write<STDERR_FILENO>("\x1b[31m");
			rx::write<STDERR_FILENO>(___msg);
			rx::write<STDERR_FILENO>("\x1b[0m\n");
		}

		/* info */
		template <rx::size_t ___sz>
		auto info(const char (&___msg)[___sz]) noexcept -> void {
			rx::write<STDOUT_FILENO>("\x1b[34m");
			rx::write<STDOUT_FILENO>(___msg);
			rx::write<STDOUT_FILENO>("\x1b[0m\n");
		}

	} // namespace hint

} // namespace ws

#endif // ___RENDERX_HINT___
