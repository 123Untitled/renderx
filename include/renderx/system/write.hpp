/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_SYSTEM_WRITE_HPP___
#define ___RENDERX_SYSTEM_WRITE_HPP___

#include <unistd.h>
#include "engine/types.hpp"


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	/* write */
	template <int ___where = STDOUT_FILENO, rx::size_t ___size> requires (___where == STDOUT_FILENO || ___where == STDERR_FILENO)
	auto write(const char (&___msg)[___size]) -> void {
		static_cast<void>(::write(___where, ___msg, ___size));
	}

} // namespace rx

#endif // ___RENDERX_SYSTEM_WRITE_HPP___
