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

#ifndef ___ve_math_sqrt___
#define ___ve_math_sqrt___

#include "ve/config.hpp"

#if !___ve_has_builtin(__builtin_elementwise_sqrt)
#	include <math.h>
#endif

#include <concepts>
#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	/* sqrt */
	template <typename ___type> requires std::floating_point<___type>
	constexpr auto sqrt(const ___type x) noexcept -> ___type {

		#if ___ve_has_builtin(__builtin_elementwise_sqrt)
			return __builtin_elementwise_sqrt(x);

		//#elif ___ve_has_builtin(__builtin_sqrt)
		//	return __builtin_sqrt(x);

		#else

			if constexpr (std::same_as<___type, float>) {
				return sqrtf(x);
			}
			else if constexpr (std::same_as<___type, double>) {
				return sqrt(x);
			}
			else if constexpr (std::same_as<___type, long double>) {
				return sqrtl(x);
			}

		#endif
	}


	template <typename ___type>
	consteval auto sqrt_compile_time(const ___type x) -> ___type {

		___type y;
		int p, square, c;

		/* find the surrounding perfect squares */
		p = 0;
		do {
			++p;
			square = (p + 1) * (p + 1);
		}
		while (x > square);

		/* process the root */
		y = static_cast<___type>(p);
		c = 0;

		while (c < 10) {

			/* divide and average */
			y = ((x / y) + y) / 2;

			/* test for success */
			if (y * y == x)
				return y;

			++c;
		}

		return y;
	}


} // namespace ve

#endif // ___ve_math_sqrt___
