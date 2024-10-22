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

#ifndef ___ve_memory_memcpy___
#define ___ve_memory_memcpy___

#include "ve/types.hpp"
#include "ve/config.hpp"

#if !___ve_has_builtin(__builtin_memcpy)
#	include <string.h>
#endif


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	/* memcpy */
	inline auto memcpy(void* dst, const void* src, const ve::size_t count) noexcept -> void {
		#if ___ve_has_builtin(__builtin_memcpy)
			__builtin_memcpy(dst, src, count);
		#else
			static_cast<void>(::memcpy(dst, src, count));
		#endif
	}

} // namespace ve

#endif // ___ve_memory_memcpy___
