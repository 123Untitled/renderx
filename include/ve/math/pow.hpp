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

#ifndef ___ve_math_pow___
#define ___ve_math_pow___

#include <concepts>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	/* unsigned power */
	template <typename ___type> requires std::unsigned_integral<___type>
	constexpr auto pow(___type base, ___type exp) noexcept -> ___type {

		___type result{1U};

		while (exp > 0U) {

			if (exp & 1U)
				result *= base;

			exp >>= 1U;
			base *= base;
		}
		return result;
	}


} // namespace ve

#endif // ___ve_math_pow___
