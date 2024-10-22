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

#ifndef ___void_engine_index_sequence___
#define ___void_engine_index_sequence___

#include "ve/types.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- I N D E X  S E Q U E N C E ------------------------------------------

	template <rx::u32... ___indices>
	class index_sequence final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::index_sequence<___indices...>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr index_sequence(void) noexcept = default;

			/* copy constructor */
			constexpr index_sequence(const ___self&) noexcept = default;

			/* move constructor */
			constexpr index_sequence(___self&&) noexcept = default;

			/* destructor */
			~index_sequence(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto constexpr operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto constexpr operator=(___self&&) noexcept -> ___self& = default;

	}; // class index_sequence



	// -- M A K E  I N D E X  S E Q U E N C E ---------------------------------

	namespace ___impl {


		template <rx::u32 ___size>
		class ___make_index_sequence final {


			private:

				/* forward declaration */
				template <rx::u32...>
				struct ___impl;

				/* end of recursion */
				template <rx::u32 ___index, rx::u32... ___seq> requires (___index == 0U)
				struct ___impl<___index, ___seq...> {

					/* type of the integer sequence */
					using type = ve::index_sequence<___seq...>;
				};

				/* recursive call */
				template <rx::u32 ___index, rx::u32... ___seq> requires (___index > 0U)
				struct ___impl<___index, ___seq...> {

					/* recursive call of type */
					using type = typename ___impl<___index - 1U, ___index - 1U, ___seq...>::type;
				};


			public:

				// -- public types --------------------------------------------

				/* type of the integer sequence */
				using type = typename ___impl<___size>::type;

		}; // class ___make_index_sequence

	} // namespace ___impl


	/* make an index sequence of length N */
	template <rx::u32 ___size>
	using make_index_sequence = typename ___impl::___make_index_sequence<___size>::type;

} // namespace ve

#endif // ___void_engine_index_sequence___
