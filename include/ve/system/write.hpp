/*****************************************************************************/
/*                                                                           */
/*      dMP dMP .aMMMb  dMP dMMMMb                                           */
/*     dMP dMP dMP"dMP amr dMP VMP                                           */
/*    dMP dMP dMP dMP dMP dMP dMP                                            */
/*    YMvAP  dMP aMP dMP dMP.aMP                                             */
/*     VP    VMMMP  dMP dMMMMP                                               */
/*                                                                           */
/*       dMMMMMP dMMMMb   aMMMMP dMP dMMMMb  dMMMMMP                         */
/*      dMP     dMP dMP dMP     amr dMP dMP dMP                              */
/*     dMMMP   dMP dMP dMP MMP dMP dMP dMP dMMMP                             */
/*    dMP     dMP dMP dMP.dMP dMP dMP dMP dMP                                */
/*   dMMMMMP dMP dMP  VMMMP" dMP dMP dMP dMMMMMP                             */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ve_system_write___
#define ___ve_system_write___

#include "ve/os.hpp"
#include "ve/types.hpp"

#if defined(ENGINE_OS_LINUX) || defined(ENGINE_OS_MACOS)
	#include <unistd.h>
#elif defined(ENGINE_OS_WINDOWS)
	#include <io.h>
#endif


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	/* write */
	template <int ___where = STDOUT_FILENO, rx::size_t ___size> requires (___where == STDOUT_FILENO || ___where == STDERR_FILENO)
	auto write(const char (&___msg)[___size]) -> void {
		static_cast<void>(::write(___where, ___msg, ___size));
	}

} // namespace ve

#endif // ___ve_system_write___
