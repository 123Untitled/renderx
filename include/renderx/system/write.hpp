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

#include "renderx/os.hpp"

// use write() to print to stdout (Linux)
// use _write() to print to stdout (Windows)
// use write() to print to stdout (MacOS)

#if defined(ENGINE_OS_LINUX) || defined(ENGINE_OS_MACOS)
	#include <unistd.h>
#elif defined(ENGINE_OS_WINDOWS)
	#include <io.h>
#endif
#include "renderx/types.hpp"


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	/* write */
	template <int ___where = STDOUT_FILENO, rx::size_t ___size> requires (___where == STDOUT_FILENO || ___where == STDERR_FILENO)
	auto write(const char (&___msg)[___size]) -> void {
		static_cast<void>(::write(___where, ___msg, ___size));
	}

} // namespace rx

#endif // ___RENDERX_SYSTEM_WRITE_HPP___
