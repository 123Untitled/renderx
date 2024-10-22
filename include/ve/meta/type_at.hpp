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

#ifndef ___void_engine_type_at___
#define ___void_engine_type_at___


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- T Y P E  A T --------------------------------------------------------

	namespace ___impl {


		template <unsigned ___idx, typename... ___params>
		class ___type_at final {


			// -- assertions --------------------------------------------------

			/* check if pack is not empty */
			static_assert(sizeof...(___params) > 0, "parameter pack is empty");

			/* check if index is valid */
			static_assert(___idx < sizeof...(___params), "index out of bounds");


			private:

				// -- private implementation ----------------------------------

				/* forward declaration */
				template <unsigned, typename...>
				struct ___;

				/* specialization for ___n == ___idx */
				template <unsigned i, typename ___type, typename... ___types> requires (i == ___idx)
				struct ___<i, ___type, ___types...> final {
					using type = ___type;
				};

				/* specialization for ___n < ___idx */
				template <unsigned i, typename ___type, typename... ___types> requires (i < ___idx)
				struct ___<i, ___type, ___types...> final {
					using type = typename ___<i + 1U, ___types...>::type;
				};


			public:

				// -- public types --------------------------------------------

				/* type indexed by IDX */
				using type = typename ___<0U, ___params...>::type;


		}; // class ___type_at

	} // namespace ___impl


	/* type at */
	template <unsigned ___idx, typename... ___params>
	using type_at = typename ve::___impl::___type_at<___idx, ___params...>::type;

} // namespace ve

#endif // ___void_engine_type_at___
