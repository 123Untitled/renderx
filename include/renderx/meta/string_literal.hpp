#ifndef ___RENDERX_STRING_LITERAL___
#define ___RENDERX_STRING_LITERAL___

#include "renderx/types.hpp"


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- S T R I N G  L I T E R A L ------------------------------------------

	template <rx::size_t ___size>
	struct string_literal final {


		// -- assertions ------------------------------------------------------

		/* check for null size */
		static_assert(___size > 0U,
			"string_literal: empty string literals are not allowed");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::string_literal<___size>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = char;

			/* const reference type */
			using const_reference = const value_type(&)[___size];

			/* size type */
			using size_type = decltype(___size);


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[___size];


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			string_literal(void) = delete;

			/* array constructor */
			template <size_type ___sz>
			consteval string_literal(const char (&___str)[___sz]) noexcept
			: _data{} {

				for (size_type i = 0U; i < ___sz; ++i)
					_data[i] = ___str[i];
			}


			/* copy constructor */
			consteval string_literal(const ___self&) noexcept = default;

			/* move constructor */
			consteval string_literal(___self&&) noexcept = default;

			/* destructor */
			constexpr ~string_literal(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			consteval auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			consteval auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* data */
			consteval auto data(void) const noexcept -> const_reference {
				return _data;
			}

			/* size */
			consteval auto size(void) const noexcept -> size_type {
				return ___size - 1U; // assume null-terminated
			}


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			constexpr operator const_reference(void) const noexcept {
				return _data;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <size_type ___sz>
			consteval auto operator==(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) == 0;
			}

			/* inequality operator */
			template <size_type ___sz>
			consteval auto operator!=(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) != 0;
			}

			/* less than operator */
			template <size_type ___sz>
			consteval auto operator<(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) < 0;
			}

			/* greater than operator */
			template <size_type ___sz>
			consteval auto operator>(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) > 0;
			}

			/* less than or equal to operator */
			template <size_type ___sz>
			consteval auto operator<=(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) <= 0;
			}

			/* greater than or equal to operator */
			template <size_type ___sz>
			consteval auto operator>=(const rx::string_literal<___sz>& other) const noexcept -> bool {
				return ___self::_compare(_data, other._data) >= 0;
			}


		private:

			/* compare implementation */
			template <size_type S, size_type I>
			static consteval auto _compare_impl(const char (&lhs)[S], const char (&rhs)[S]) noexcept -> signed int {

				if constexpr (I == S) {
					return 0;
				} else {
					return (lhs[I] == rhs[I])
						? (___self::_compare_impl<S, I + 1>(lhs, rhs))
						: (lhs[I] > rhs[I] ? +1 : -1);
				}
			}

			/* compare */
			template <size_type ls, size_type lr>
			static consteval auto _compare(const char (&lhs)[ls], const char (&rhs)[lr]) noexcept -> signed int {

				// check for equal size
				if constexpr (ls == lr) {
					return ___self::_compare_impl<ls, 0U>(lhs, rhs);
				}
				else {
					return (ls > lr) ? +1 : -1;
				}
			}
	};


	// -- deduction guides ----------------------------------------------------

	template <rx::size_t ___size>
	string_literal(const char (&)[___size]) -> string_literal<___size>;



	/* equality operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//consteval auto operator==(const xns::basic_string_literal<T1, L>& lhs,
	//								 const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) == 0;
	//}

	/* equality operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//consteval auto operator==(const T1 (&lhs)[L],
	//								 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) == 0;
	//}
	//
	///* inequality operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//consteval auto operator!=(const xns::basic_string_literal<T1, L>& lhs,
	//								 const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) != 0;
	//}
	//
	///* inequality operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator!=(const T1 (&lhs)[L],
	//								 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) != 0;
	//}
	//
	///* less than operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator<(const xns::basic_string_literal<T1, L>& lhs,
	//								const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) < 0;
	//}
	//
	///* less than operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator<(const T1 (&lhs)[L],
	//								const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) < 0;
	//}
	//
	///* greater than operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator>(const xns::basic_string_literal<T1, L>& lhs,
	//								const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) > 0;
	//}
	//
	///* greater than operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator>(const T1 (&lhs)[L],
	//								const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) > 0;
	//}
	//
	///* less than or equal to operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator<=(const xns::basic_string_literal<T1, L>& lhs,
	//								 const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) <= 0;
	//}
	//
	///* less than or equal to operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator<=(const T1 (&lhs)[L],
	//								 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) <= 0;
	//}
	//
	///* greater than or equal to operator */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator>=(const xns::basic_string_literal<T1, L>& lhs,
	//								 const T2 (&rhs)[R]) noexcept -> bool {
	//	return xns::compare(lhs._data, rhs) >= 0;
	//}
	//
	///* greater than or equal to operator (reverse) */
	//template <typename T1, typename T2,
	//		  decltype(sizeof(0)) L, decltype(L) R>
	//constexpr auto operator>=(const T1 (&lhs)[L],
	//								 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
	//	return xns::compare(lhs, rhs._data) >= 0;
	//}




} // namespace xns

#endif // XNS_STRING_LITERAL_HEADER
