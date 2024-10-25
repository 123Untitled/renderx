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

#ifndef ___ve_containers_static_map___
#define ___ve_containers_static_map___

#include "ve/meta/string_literal.hpp"
#include <utility>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S T A T I C  M A P --------------------------------------------------

	template <typename ___type, ve::literal... ___keys>
	class static_map final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* reference */
			using reference = value_type&;

			/* const reference */
			using const_reference = const value_type&;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::static_map<___type, ___keys...>;


			template <ve::literal>
			struct ___wrapper {
				value_type _value;
			};


			// -- private classes ---------------------------------------------

			/* implementation */
			class ___impl : public ___wrapper<___keys>... {


				public:

					// -- public lifecycle ------------------------------------

					/* default constructor */
					___impl(void) = default;

					/* parameter constructor */
					template <typename... ___params>
					___impl(___params&&... ___args)
					: ___self::___wrapper<___keys>{std::forward<___params>(___args)}... {
					}

					/* copy constructor */
					___impl(const ___impl&) = default;

					/* move constructor */
					___impl(___impl&&) noexcept = default;

					/* destructor */
					~___impl(void) noexcept = default;


					// -- public assignment operators -------------------------

					/* copy assignment operator */
					auto operator=(const ___impl&) -> ___impl& = default;

					/* move assignment operator */
					auto operator=(___impl&&) -> ___impl& = default;

			}; // class ___impl


			// -- private members ---------------------------------------------

			/* implementation */
			___impl _impl;


			// -- private static methods --------------------------------------

			/* have key */
			template <ve::literal ___key>
			static consteval auto _have_key(void) noexcept -> bool {
				return ((___key == ___keys) || ...);
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			static_map(void) = default;

			/* parameter constructor */
			template <typename... ___params>
			static_map(___params&&... ___args)
			: _impl{std::forward<___params>(___args)...} {
			}


			// -- public accessors --------------------------------------------

			/* get */
			template <ve::literal ___key>
			auto get(void) noexcept -> value_type& {

				// check if key exists
				static_assert(___self::_have_key<___key>(), "key not found");

				// retrieve value
				return static_cast<___self::___wrapper<___key>&>(_impl)._value;
			}

			/* const get */
			template <ve::literal ___key>
			auto get(void) const noexcept -> const value_type& {

				// check if key exists
				static_assert(___self::_have_key<___key>(), "key not found");

				// retrieve value
				return static_cast<const ___self::___wrapper<___key>&>(_impl)._value;
			}


			// -- public loop methods -----------------------------------------

			/* for each */
			template <typename ___fn>
			auto for_each(___fn&& fn) -> void {

				// for each key
				((fn(___self::get<___keys>()), ...));
			}

			/* const for each */
			template <typename ___fn>
			auto for_each(___fn&& fn) const -> void {

				// for each key
				((fn(___self::get<___keys>()), ...));
			}


		// -- friends ---------------------------------------------------------

		/* get as friend */
		template <ve::literal, typename ___tp, ve::literal... ___ks>
		friend auto get(const ve::static_map<___tp, ___ks...>&) noexcept -> const ___tp&;

		/* get as friend */
		template <ve::literal, typename ___tp, ve::literal... ___ks>
		friend auto get(ve::static_map<___tp, ___ks...>&) noexcept -> ___tp&;

	}; // class static_map


	// -- non-member functions ------------------------------------------------

	/* get */
	template <ve::literal ___key, typename ___type, ve::literal... ___keys>
	auto get(const ve::static_map<___type, ___keys...>& map) noexcept -> const ___type& {

		// map type
		using ___map = ve::static_map<___type, ___keys...>;

		// check if key exists
		static_assert(___map::template _have_key<___key>(), "key not found");

		// retrieve value
		return static_cast<const typename ___map::template ___wrapper<___key>&>(map._impl)._value;
	}

	/* get */
	template <ve::literal ___key, typename ___type, ve::literal... ___keys>
	auto get(ve::static_map<___type, ___keys...>& map) noexcept -> ___type& {

		// map type
		using ___map = ve::static_map<___type, ___keys...>;

		// check if key exists
		static_assert(___map::template _have_key<___key>(), "key not found");

		// retrieve value
		return static_cast<typename ___map::template ___wrapper<___key>&>(map._impl)._value;
	}


} // namespace ve

#endif // ___ve_containers_static_map___
