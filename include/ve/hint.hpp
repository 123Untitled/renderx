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

#ifndef ___ve_hint___
#define ___ve_hint___

#include "ve/system/write.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- H I N T  N A M E S P A C E ------------------------------------------

	namespace hint {


		/* success */
		template <ve::size_t ___sz>
		auto success(const char (&___msg)[___sz]) noexcept -> void {
			ve::write<STDOUT_FILENO>("\x1b[32m");
			ve::write<STDOUT_FILENO>(___msg);
			ve::write<STDOUT_FILENO>("\x1b[0m\n");
		}

		/* warning */
		template <ve::size_t ___sz>
		auto warning(const char (&___msg)[___sz]) noexcept -> void {
			ve::write<STDOUT_FILENO>("\x1b[33m");
			ve::write<STDOUT_FILENO>(___msg);
			ve::write<STDOUT_FILENO>("\x1b[0m\n");
		}

		/* error */
		template <ve::size_t ___sz>
		auto error(const char (&___msg)[___sz]) noexcept -> void {
			ve::write<STDERR_FILENO>("\x1b[31m");
			ve::write<STDERR_FILENO>(___msg);
			ve::write<STDERR_FILENO>("\x1b[0m\n");
		}

		/* info */
		template <ve::size_t ___sz>
		auto info(const char (&___msg)[___sz]) noexcept -> void {
			ve::write<STDOUT_FILENO>("\x1b[34m");
			ve::write<STDOUT_FILENO>(___msg);
			ve::write<STDOUT_FILENO>("\x1b[0m\n");
		}

	} // namespace hint

} // namespace ve

#endif // ___ve_hint___
