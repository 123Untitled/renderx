#ifndef ___ve_structures_vec___
#define ___ve_structures_vec___

#include "ve/math/sqrt.hpp"
#include <utility>
#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- V E C ---------------------------------------------------------------

	template <typename T, unsigned N>
	class vec final {


		// -- assertions ------------------------------------------------------

		/* check for zero size */
		static_assert(N > 0U, "size must be greater than zero");


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = T;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* size type */
			using size_type = decltype(N);


		private:


			// -- private structs ---------------------------------------------

			template <size_type... Is>
			struct _seq {


				// -- copy ----------------------------------------------------

				/* copy */
				static auto copy(const value_type (&v)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{v[Is]...};
				}

				/* copy (self) */
				static auto copy(value_type (&dst)[N], const value_type (&src)[N]) noexcept -> void {
					((dst[Is] = src[Is]), ...);
				}

				/* copy (self, scalar) */
				static auto copy(value_type (&dst)[N], const value_type& s) noexcept -> void {
					((dst[Is] = s), ...);
				}


				// -- arithmetic ----------------------------------------------

				/* add */
				static auto add(const value_type (&v1)[N],
								const value_type (&v2)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v1[Is] + v2[Is])...};
				}

				/* sub */
				static auto sub(const value_type (&v1)[N],
								const value_type (&v2)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v1[Is] - v2[Is])...};
				}

				/* mul */
				static auto mul(const value_type (&v1)[N],
								const value_type (&v2)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v1[Is] * v2[Is])...};
				}

				/* div */
				static auto div(const value_type (&v1)[N],
								const value_type (&v2)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v1[Is] / v2[Is])...};
				}


				// -- arithmetic (scalar) -------------------------------------

				/* add (scalar) */
				static auto add(const value_type (&v)[N],
								const value_type& s) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v[Is] + s)...};
				}

				/* sub (scalar) */
				static auto sub(const value_type (&v)[N],
								const value_type& s) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v[Is] - s)...};
				}

				/* mul (scalar) */
				static auto mul(const value_type (&v)[N],
								const value_type& s) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v[Is] * s)...};
				}

				/* div (scalar) */
				static auto div(const value_type (&v)[N],
								const value_type& s) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(v[Is] / s)...};
				}


				// -- arithmetic (self) ---------------------------------------

				/* add (self) */
				static auto add(value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> void {
					((lhs[Is] += rhs[Is]), ...);
				}

				/* sub (self) */
				static auto sub(value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> void {
					((lhs[Is] -= rhs[Is]), ...);
				}

				/* mul (self) */
				static auto mul(value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> void {
					((lhs[Is] *= rhs[Is]), ...);
				}

				/* div (self) */
				static auto div(value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> void {
					((lhs[Is] /= rhs[Is]), ...);
				}


				// -- arithmetic (self, scalar) -------------------------------

				/* add (self, scalar) */
				static auto add(value_type (&lhs)[N], const value_type& rhs) noexcept -> void {
					((lhs[Is] += rhs), ...);
				}

				/* sub (self, scalar) */
				static auto sub(value_type (&lhs)[N], const value_type& rhs) noexcept -> void {
					((lhs[Is] -= rhs), ...);
				}

				/* mul (self, scalar) */
				static auto mul(value_type (&lhs)[N], const value_type& rhs) noexcept -> void {
					((lhs[Is] *= rhs), ...);
				}

				/* div (self, scalar) */
				static auto div(value_type (&lhs)[N], const value_type& rhs) noexcept -> void {
					((lhs[Is] /= rhs), ...);
				}


				// -- functions -----------------------------------------------

				/* dot */
				static auto dot(const value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> value_type {
					return ((lhs[Is] * rhs[Is]) + ...);
				}

				/* lerp */
				static auto lerp(const value_type (&lhs)[N], const value_type (&rhs)[N], const value_type& t) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{(lhs[Is] + ((rhs[Is] - lhs[Is]) * t))...};
				}

				/* midpoint */
				static auto midpoint(const value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> ve::vec<value_type, N> {
					return ve::vec<value_type, N>{((lhs[Is] + rhs[Is]) * 0.5f)...};
				}


				// -- functions (self) ----------------------------------------

				/* normalize */
				static auto normalize(value_type (&v)[N]) noexcept -> void {
					const auto len = ve::sqrt(((v[Is] * v[Is]) + ...));

					if (len != 0.0f) { ((v[Is] /= len), ...); }
					else { ((v[Is] = 0.0f), ...); }
				}

		/*
		(lhs.y * rhs.z) - (lhs.z * rhs.y),
		(lhs.z * rhs.x) - (lhs.x * rhs.z),
		(lhs.x * rhs.y) - (lhs.y * rhs.x)

				// cross
				static auto cross(const value_type (&lhs)[N], const value_type (&rhs)[N]) noexcept -> ve::vec<value_type, 3U> {
					// not implemented yet...
					return {};
				}
		*/



				/* for each */
				template <typename F>
				static auto for_each(value_type (&lhs)[N], F&& f) noexcept -> void {
					((f(lhs[Is])), ...);
				}

				/* for each (const) */
				template <typename F>
				static auto for_each(const value_type (&lhs)[N], F&& f) noexcept -> void {
					((f(lhs[Is])), ...);
				}

			}; // struct _impl


			struct _make_sequence {

				template <size_type...>
				struct _impl;

				/* end of recursion */
				template <size_type I, size_type... Is> requires (I == 0U)
				struct _impl<I, Is...> {
					using type = _seq<Is...>;
				};

				/* recursive call */
				template <size_type I, size_type... Is> requires (I > 0U)
				struct _impl<I, Is...> {
					using type = typename _impl<I - 1U, I - 1U, Is...>::type;
				};

				using type = typename _impl<N>::type;
			};


			// -- private types -----------------------------------------------

			/* self type */
			using _self = ve::vec<T, N>;

			/* sequence type */
			using _sequence = typename _make_sequence::type;


			// -- private members ---------------------------------------------

			/* data */
			value_type _data[N];


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vec(void) noexcept = default;

			/* variadic constructor */
			template <typename... Ts> requires (sizeof...(Ts) <= N)
			vec(const Ts&... args) noexcept
			: _data{static_cast<value_type>(args)...} {
			}

			/* array constructor */
			vec(const value_type (&data)[N]) noexcept {
				_sequence::copy(data, _data);
			}

			/* copy constructor */
			vec(const _self&) noexcept = default;

			/* move constructor */
			vec(_self&&) noexcept = default;

			/* destructor */
			~vec(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const _self&) noexcept -> _self& = default;

			/* move assignment operator */
			auto operator=(_self&&) noexcept -> _self& = default;


			// -- public comparison operators ---------------------------------

			/* equality operator */
			auto operator==(const _self&) const noexcept -> bool = default;

			/* inequality operator */
			auto operator!=(const _self&) const noexcept -> bool = default;


			// -- public modifiers --------------------------------------------

			/* normalize */
			auto normalize(void) noexcept -> void {
				_sequence::normalize(_data);
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return N;
			}

			/* x */
			auto x(void) noexcept -> value_type& {
				return _data[0];
			}

			/* x */
			auto x(void) const noexcept -> const value_type& {
				return _data[0];
			}

			/* u */
			auto u(const value_type& value) noexcept -> void {
				_data[0U] = value;
			}

			/* u */
			auto u(void) const noexcept -> const value_type& {
				return _data[0];
			}

			/* y */
			auto y(void) noexcept -> value_type& requires (N > 1U) {
				return _data[1];
			}

			/* y */
			auto y(void) const noexcept -> const value_type& requires (N > 1U) {
				return _data[1];
			}

			/* v */
			auto v(const value_type& value) noexcept -> void requires (N > 1U) {
				_data[1U] = value;
			}

			/* v */
			auto v(void) const noexcept -> const value_type& requires (N > 1U) {
				return _data[1];
			}

			/* z */
			auto z(void) noexcept -> value_type& requires (N > 2U) {
				return _data[2];
			}

			/* z */
			auto z(void) const noexcept -> const value_type& requires (N > 2U) {
				return _data[2];
			}

			/* w */
			auto w(void) noexcept -> value_type& requires (N > 3U) {
				return _data[3];
			}

			/* w */
			auto w(void) const noexcept -> const value_type& requires (N > 3U) {
				return _data[3];
			}

			/* xy */
			auto xy(void) const noexcept -> ve::vec<value_type, 2U> requires (N > 1U) {
				return ve::vec<value_type, 2U>{_data[0U], _data[1U]};
			}

			/* xyz */
			auto xyz(void) const noexcept -> ve::vec<value_type, 3U> requires (N > 2U) {
				return ve::vec<value_type, 3U>{_data[0U], _data[1U], _data[2U]};
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type& i) noexcept -> value_type& {
				return _data[i];
			}

			/* subscript operator */
			auto operator[](const size_type& i) const noexcept -> const value_type& {
				return _data[i];
			}


			// -- public arithmetic operators ---------------------------------

			/* addition assignment operator */
			auto operator+=(const _self& rhs) noexcept -> _self& {
				_sequence::add(_data, rhs._data);
				return *this;
			}

			/* subtraction assignment operator */
			auto operator-=(const _self& rhs) noexcept -> _self& {
				_sequence::sub(_data, rhs._data);
				return *this;
			}

			/* multiplication assignment operator */
			auto operator*=(const _self& rhs) noexcept -> _self& {
				_sequence::mul(_data, rhs._data);
				return *this;
			}

			/* division assignment operator */
			auto operator/=(const _self& rhs) noexcept -> _self& {
				_sequence::div(_data, rhs._data);
				return *this;
			}

			/* scalar addition assignment operator */
			auto operator+=(const value_type& scalar) noexcept -> _self& {
				_sequence::add(_data, scalar);
				return *this;
			}

			/* scalar subtraction assignment operator */
			auto operator-=(const value_type& scalar) noexcept -> _self& {
				_sequence::sub(_data, scalar);
				return *this;
			}

			/* scalar multiplication assignment operator */
			auto operator*=(const value_type& scalar) noexcept -> _self& {
				_sequence::mul(_data, scalar);
				return *this;
			}

			/* scalar division assignment operator */
			auto operator/=(const value_type& scalar) noexcept -> _self& {
				_sequence::div(_data, scalar);
				return *this;
			}



			/* print */
			auto print(void) const noexcept -> void {
				_sequence::for_each(_data, [](const value_type& value) {
					std::cout << value << ' ';
				});
				std::cout << '\n';
			}

		private:


			// -- F R I E N D S -----------------------------------------------

			// -- arithmetic operators ----------------------------------------

			/* + operator as friend */
			template <typename U, size_type M>
			friend auto operator+(const ve::vec<U, M>&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* - operator as friend */
			template <typename U, size_type M>
			friend auto operator-(const ve::vec<U, M>&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* * operator as friend */
			template <typename U, size_type M>
			friend auto operator*(const ve::vec<U, M>&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* / operator as friend */
			template <typename U, size_type M>
			friend auto operator/(const ve::vec<U, M>&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;


			// -- arithmetic operators (scalar) -------------------------------

			/* + operator as friend (scalar) */
			template <typename U, size_type M>
			friend auto operator+(const ve::vec<U, M>&,
								  const U&) noexcept -> ve::vec<U, M>;

			/* + operator as friend (scalar, inverted) */
			template <typename U, size_type M>
			friend auto operator-(const U&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* - operator as friend (scalar) */
			template <typename U, size_type M>
			friend auto operator-(const ve::vec<U, M>&,
								  const U&) noexcept -> ve::vec<U, M>;

			/* - operator as friend (scalar, inverted) */
			template <typename U, size_type M>
			friend auto operator-(const U&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* * operator as friend (scalar) */
			template <typename U, size_type M>
			friend auto operator*(const ve::vec<U, M>&,
								  const U&) noexcept -> ve::vec<U, M>;

			/* * operator as friend (scalar, inverted) */
			template <typename U, size_type M>
			friend auto operator*(const U&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* / operator as friend (scalar) */
			template <typename U, size_type M>
			friend auto operator/(const ve::vec<U, M>&,
								  const U&) noexcept -> ve::vec<U, M>;

			/* / operator as friend (scalar, inverted) */
			template <typename U, size_type M>
			friend auto operator/(const U&,
								  const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;



			// -- non-member functions ----------------------------------------

			/* dot as friend */
			template <typename U, size_type M>
			friend auto dot(const ve::vec<U, M>&, const ve::vec<U, M>&) noexcept -> U;

			/* length as friend */
			template <typename U, size_type M>
			friend auto length(const ve::vec<U, M>&) noexcept -> U;

			/* normalize as friend */
			template <typename U, size_type M>
			friend auto normalize(const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

			/* distance as friend */
			template <typename U, size_type M>
			friend auto distance(const ve::vec<U, M>&, const ve::vec<U, M>&) noexcept -> U;

			/* lerp as friend */
			template <typename U, size_type M>
			friend auto lerp(const ve::vec<U, M>&, const ve::vec<U, M>&, const U) noexcept -> ve::vec<U, M>;

			/* midpoint as friend */
			template <typename U, size_type M>
			friend auto midpoint(const ve::vec<U, M>&, const ve::vec<U, M>&) noexcept -> ve::vec<U, M>;

	}; // class vector


	// -- non-member arithmetic operators -------------------------------------

	/* addition operator */
	template <typename T, unsigned N>
	auto operator+(const ve::vec<T, N>& v1, const ve::vec<T, N>& v2) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::add(v1._data, v2._data);
	}

	/* subtraction operator */
	template <typename T, unsigned N>
	auto operator-(const ve::vec<T, N>& v1, const ve::vec<T, N>& v2) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::sub(v1._data, v2._data);
	}

	/* multiplication operator */
	template <typename T, unsigned N>
	auto operator*(const ve::vec<T, N>& v1, const ve::vec<T, N>& v2) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::mul(v1._data, v2._data);
	}

	/* division operator */
	template <typename T, unsigned N>
	auto operator/(const ve::vec<T, N>& v1, const ve::vec<T, N>& v2) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::div(v1._data, v2._data);
	}


	// -- non-member arithmetic operators (scalar) ----------------------------

	/* addition operator (scalar) */
	template <typename T, unsigned N>
	auto operator+(const ve::vec<T, N>& v,
				   const T& s) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::add(v._data, s);
	}

	/* addition operator (scalar, inverted) */
	template <typename T, unsigned N>
	auto operator+(const T& s,
				   const ve::vec<T, N>& v) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::add(v._data, s);
	}

	/* subtraction operator (scalar) */
	template <typename T, unsigned N>
	auto operator-(const ve::vec<T, N>& v,
				   const T& s) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::sub(v._data, s);
	}

	/* subtraction operator (scalar, inverted) */
	template <typename T, unsigned N>
	auto operator-(const T& s,
				   const ve::vec<T, N>& v) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::sub(v._data, s);
	}

	/* multiplication operator (scalar) */
	template <typename T, unsigned N>
	auto operator*(const ve::vec<T, N>& v,
				   const T& s) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::mul(v._data, s);
	}

	/* multiplication operator (scalar, inverted) */
	template <typename T, unsigned N>
	auto operator*(const T& s,
				   const ve::vec<T, N>& v) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::mul(v._data, s);
	}

	/* division operator (scalar) */
	template <typename T, unsigned N>
	auto operator/(const ve::vec<T, N>& v,
				   const T& s) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::div(v._data, s);
	}

	/* division operator (scalar, inverted) */
	template <typename T, unsigned N>
	auto operator/(const T& s,
				   const ve::vec<T, N>& v) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::div(v._data, s);
	}


	// -- non-member functions ------------------------------------------------

	/* dot */
	template <typename T, unsigned N>
	auto dot(const ve::vec<T, N>& lhs, const ve::vec<T, N>& rhs) noexcept -> T {
		return ve::vec<T, N>::_sequence::dot(lhs._data, rhs._data);
	}

	/* length */
	template <typename T, unsigned N>
	auto length(const ve::vec<T, N>& lhs) noexcept -> T {
		return ve::sqrt(ve::vec<T, N>::_sequence::dot(lhs._data, lhs._data));
	}

	/* normalize */
	template <typename T, unsigned N>
	auto normalize(const ve::vec<T, N>& lhs) noexcept -> ve::vec<T, N> {
		const auto len = ve::length(lhs);
		return (len != 0.0f) ? vec<T, N>::_sequence::div(lhs._data, len)
							 : ve::vec<T, N>{};
	}

	/* distance */
	template <typename T, unsigned N>
	auto distance(const ve::vec<T, N>& lhs, const ve::vec<T, N>& rhs) noexcept -> T {
		return ve::length(lhs - rhs);
	}

	/* lerp (mix) */
	template <typename T, unsigned N>
	auto lerp(const ve::vec<T, N>& lhs, const ve::vec<T, N>& rhs, const T t) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::lerp(lhs._data, rhs._data, t);
	}

	/* midpoint */
	template <typename T, unsigned N>
	auto midpoint(const ve::vec<T, N>& lhs, const ve::vec<T, N>& rhs) noexcept -> ve::vec<T, N> {
		return ve::vec<T, N>::_sequence::midpoint(lhs._data, rhs._data);
	}

	/* cross */
	template <typename T>
	auto cross(const ve::vec<T, 3U>& lhs, const ve::vec<T, 3U>& rhs) noexcept -> ve::vec<T, 3U> {
		return ve::vec<T, 3U>{
			(lhs.y() * rhs.z()) - (lhs.z() * rhs.y()),
			(lhs.z() * rhs.x()) - (lhs.x() * rhs.z()),
			(lhs.x() * rhs.y()) - (lhs.y() * rhs.x())
		};
	}


	// -- aliases -------------------------------------------------------------

	/* vec2 */
	template <typename T>
	using vec2 = ve::vec<T, 2U>;

	/* vec3 */
	template <typename T>
	using vec3 = ve::vec<T, 3U>;

	/* vec4 */
	template <typename T>
	using vec4 = ve::vec<T, 4U>;

	/* vec2f */
	using vec2f = ve::vec<float, 2U>;

	/* vec3f */
	using vec3f = ve::vec<float, 3U>;

	/* vec4f */
	using vec4f = ve::vec<float, 4U>;

	/* vec2d */
	using vec2d = ve::vec<double, 2U>;

	/* vec3d */
	using vec3d = ve::vec<double, 3U>;

	/* vec4d */
	using vec4d = ve::vec<double, 4U>;

} // namespace ve

#endif // ___ve_structures_vector___
