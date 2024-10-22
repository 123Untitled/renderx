#ifndef ___CONTAINERS_STATIC_MAP___
#define ___CONTAINERS_STATIC_MAP___

#include "ve/meta/string_literal.hpp"
#include <utility>


// -- X  E N G I N E  N A M E S P A C E ---------------------------------------

namespace xe {


	// -- S T A T I C  M A P --------------------------------------------------

	template <typename ___type, rx::string_literal... ___keys>
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
			using ___self = xe::static_map<___type, ___keys...>;


			template <rx::string_literal>
			struct wrapper {
				value_type _value;
			};


			// -- private classes ---------------------------------------------

			/* implementation */
			class ___impl : public wrapper<___keys>... {


				public:

					// -- public lifecycle ------------------------------------

					/* default constructor */
					___impl(void) = default;

					/* parameter constructor */
					template <typename... ___params>
					___impl(___params&&... ___args)
					: ___self::wrapper<___keys>{std::forward<___params>(___args)}... {
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
			template <rx::string_literal ___key>
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
			template <rx::string_literal ___key>
			auto get(void) noexcept -> value_type& {

				// check if key exists
				static_assert(___self::_have_key<___key>(), "key not found");

				// retrieve value
				return static_cast<___self::wrapper<___key>&>(_impl)._value;
			}

			/* const get */
			template <rx::string_literal ___key>
			auto get(void) const noexcept -> const value_type& {

				// check if key exists
				static_assert(___self::_have_key<___key>(), "key not found");

				// retrieve value
				return static_cast<const ___self::wrapper<___key>&>(_impl)._value;
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

	}; // class static_map

} // namespace xe

#endif // ___CONTAINERS_STATIC_MAP___
