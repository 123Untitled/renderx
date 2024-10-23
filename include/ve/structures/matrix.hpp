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

#ifndef ___ve_structures_matrix___
#define ___ve_structures_matrix___

#include "ve/structures/vector3.hpp"
#include "ve/memory/memcpy.hpp"
#include "ve/types.hpp"
#include "ve/meta/index_sequence.hpp"

#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- M A T R I X ---------------------------------------------------------

	template <typename type, unsigned rows, unsigned cols>
	class matrix final {


		public:

			// -- public types ------------------------------------------------

			/* type */
			using value_type = type;

			/* row type */
			using row = value_type[cols];

			/* column type */
			using col = value_type[rows];

			/* reference */
			using reference = value_type&;

			/* const reference */
			using const_reference = const value_type&;

			/* size type */
			using size_type = decltype(rows * cols);


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::matrix<type, rows, cols>;


			// -- private constants -------------------------------------------

			enum : size_type {
				VE_MATRIX_SIZE = rows * cols
			};


			// -- public members ----------------------------------------------

			/* matrix */
			type _mat[VE_MATRIX_SIZE];


			// -- private methods ---------------------------------------------

			template <size_type... indices>
			auto _copy(const type(&mat)[VE_MATRIX_SIZE],
					   ve::index_sequence<indices...>) noexcept -> void {
				((this->_mat[indices] = mat[indices]), ...);
			}

			template <size_type... indices>
			struct __impl final {


				static auto _copy(const value_type(&m1)[VE_MATRIX_SIZE],
								  const value_type(&m2)[VE_MATRIX_SIZE]) noexcept -> void {
					((m1[indices] = m2[indices]), ...);
				}

				static auto _copy(const value_type(&m1)[VE_MATRIX_SIZE],
								  const value_type& scalar) noexcept -> void {
					((m1[indices] = scalar), ...);
				}

				static auto _add(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type(&m2)[VE_MATRIX_SIZE]) noexcept -> void {
					((m1[indices] += m2[indices]), ...);
				}

				static auto _sub(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type(&m2)[VE_MATRIX_SIZE]) noexcept -> void {
					((m1[indices] -= m2[indices]), ...);
				}

				static auto _mul(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type(&m2)[VE_MATRIX_SIZE]) noexcept -> void {
					((m1[indices] *= m2[indices]), ...);
				}

				static auto _div(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type(&m2)[VE_MATRIX_SIZE]) noexcept -> void {
					((m1[indices] /= m2[indices]), ...);
				}

				static auto _add(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type& scalar) noexcept -> void {
					((m1[indices] += scalar), ...);
				}

				static auto _sub(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type& scalar) noexcept -> void {
					((m1[indices] -= scalar), ...);
				}

				static auto _mul(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type& scalar) noexcept -> void {
					((m1[indices] *= scalar), ...);
				}

				static auto _div(const value_type(&m1)[VE_MATRIX_SIZE],
								 const value_type& scalar) noexcept -> void {
					((m1[indices] /= scalar), ...);
				}



			};

		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			matrix(void) noexcept = default;

			/* array constructor */
			matrix(const type(&array)[VE_MATRIX_SIZE]) noexcept {
				___self::_copy(array, ve::make_index_sequence<VE_MATRIX_SIZE>{});
			}

			/* multi-dimensional array constructor */
			matrix(const type(&multi)[rows][cols]) noexcept {
				___self::_copy(reinterpret_cast<const type(&)[VE_MATRIX_SIZE]>(multi),
						ve::make_index_sequence<VE_MATRIX_SIZE>{});
			}

			/* variadic constructor */
			template <typename... types> requires ((sizeof...(types) <= VE_MATRIX_SIZE)
												&& (std::same_as<type, std::remove_cvref_t<types>> && ...))
			matrix(types&&... args) noexcept
			: _mat{static_cast<type>(/*forward*/args)...} {
			}

			/* rows constructor */
			template <size_type... sizes> requires ((sizeof...(sizes) == cols)
													&& ((sizes == rows) && ...) && false) // NOT IMPLEMENTED YET...
			matrix(const type (&...arrays)[sizes]) noexcept {
			}



			/* copy constructor */
			matrix(const ___self&) noexcept = default;

			/* move constructor */
			matrix(___self&&) noexcept = default;

			/* destructor */
			~matrix(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public subscript operators ----------------------------------


			template <size_type... indices>
			auto _print(ve::index_sequence<indices...>) const noexcept -> void {
				((std::cout << _mat[indices] << ((indices % cols == cols - 1) ? '\n' : ' ')), ...);
			}

			/* print */
			auto print(void) const noexcept -> void {

				std::cout.precision(2);
				std::cout << std::fixed;
				___self::_print(ve::make_index_sequence<VE_MATRIX_SIZE>{});

			}


		private:

			// -- private arithmetic methods ----------------------------------

			/* add */
			template <size_type... indices>
			auto _add(const ___self& other, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] += other._mat[indices]), ...);
			}

			/* sub */
			template <size_type... indices>
			auto _sub(const ___self& other, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] -= other._mat[indices]), ...);
			}


			/* add scalar */
			template <size_type... indices>
			auto _add_scalar(const type& scalar, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] += scalar), ...);
			}

			/* sub scalar */
			template <size_type... indices>
			auto _sub_scalar(const type& scalar, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] -= scalar), ...);
			}

			/* mul scalar */
			template <size_type... indices>
			auto _mul_scalar(const type& scalar, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] *= scalar), ...);
			}

			/* div scalar */
			template <size_type... indices>
			auto _div_scalar(const type& scalar, ve::index_sequence<indices...>) noexcept -> void {
				((_mat[indices] /= scalar), ...);
			}

			template <size_type value>
			static constexpr size_type compute = value;

			/* mul element */
			template <size_type row, size_type col, typename t1, typename t2, size_type... idx>
			static auto _mul_element(const t1& m1, const t2& m2, ve::index_sequence<idx...>) noexcept -> value_type {
				return ((m1._mat[compute<row * cols + idx>] * m2._mat[compute<idx * cols + col>]) + ...);
			}

			/* mul */
			template <size_type row, size_type col, typename t1, typename t2, size_type... idx>
			static auto _mul(const t1& m1, const t2& m2, ve::index_sequence<idx...>) noexcept -> void {
				m1._mat[compute<row * cols + col>] = _mul_element<row, col>(m1, m2, ve::make_index_sequence<cols>{});
			}
			/*
			   lhs (row) sequence: 000 111 222
			   rhs (col) sequence: 012 012 012
			   */

			/*
			   matrix multiplication
			   try something like this:
				3x index sequences (result, lhs, rhs)

				*/

				template <typename m1, typename m2, size_type... s1, size_type... s2, size_type... s3>
				static auto _multiply(const m1& lhs, const m2& rhs, index_sequence<s1...>,
																	index_sequence<s2...>,
																	index_sequence<s3...>) noexcept -> void {

					___self result;

					((result[s1] = ((lhs[s2] * rhs[s3]) + ...)), ...);
				}

				/* make matrix sequence */
				template <size_type s1, size_type s2, size_type s3>
				class make_matrix_sequence {


					public:

						/* lhs type */
						using lhs_type = ve::matrix<type, s1, s2>;

						/* rhs type */
						using rhs_type = ve::matrix<type, s2, s3>;

						/* ret type */
						using ret_type = ve::matrix<type, s1, s3>;


					private:

						constexpr static size_type ret_size = s1 * s3;


						/* example of sequences for
						lhs {0, 1}
							{2, 3}
							{4, 5}

						rhs {0, 1, 2}
							{3, 4, 5}

						ret {0, 0, 0}
							{0, 0, 0}
							{0, 0, 0}

						ret sequence: 0, 1, 2, 3, 4, 5, 6, 7, 8
						lhs sequence: 0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 3, 4, 5, 4, 5, 4, 5
						rhs sequence: 0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5, 0, 3, 1, 4, 2, 5
						*/



						/* result sequence */
						template <size_type...>
						struct _ret_seq;

						template <size_type i, size_type... seq> requires (i > 0U)
						struct _ret_seq<i, seq...> {
							using _type = typename _ret_seq<i - 1U, i - 1U, seq...>::_type;
						};

						template <size_type... seq> requires (sizeof...(seq) == ret_size)
						struct _ret_seq<seq...> {
							using _type = ve::index_sequence<seq...>;
						};




						/* result sequence */
						// not implemented yet...

						/* lhs sequence */
						// not implemented yet...

						/* rhs sequence */
						// not implemented yet...
				};


		public:

			// -- public arithmetic operators ---------------------------------

			/* += operator */
			auto operator+=(const ___self& other) noexcept -> ___self& {
				___self::_add(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* -= operator */
			auto operator-=(const ___self& other) noexcept -> ___self& {
				___self::_sub(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* *= operator */
			/* on this operator, the matrix must be square, because the result matrix
			 * will have the same number of rows as the left matrix and the same number
			 * of columns as the right matrix */
			auto operator*=(const ___self& other) noexcept -> ___self& {

				// result matrix
				___self result;
				// test multiplication
				_mul_element<0, 0>(result, other, ve::make_index_sequence<cols>{});

				return *this;
				// multiply matrices
				//result._mul(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
			}



			/* += operator (scalar) */
			auto operator+=(const type& scalar) noexcept -> ___self& {
				___self::_add_scalar(scalar, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* -= operator (scalar) */
			auto operator-=(const type& scalar) noexcept -> ___self& {
				___self::_sub_scalar(scalar, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* *= operator (scalar) */
			auto operator*=(const type& scalar) noexcept -> ___self& {
				___self::_mul_scalar(scalar, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* /= operator (scalar) */
			auto operator/=(const type& scalar) noexcept -> ___self& {
				___self::_div_scalar(scalar, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}


	}; // class matrix


	// -- non-member arithmetic operators -------------------------------------

	/* + operator */
	template <typename type, unsigned rows, unsigned cols>
	auto operator+(const ve::matrix<type, rows, cols>& lhs,
				   const ve::matrix<type, rows, cols>& rhs) noexcept -> ve::matrix<type, rows, cols> {

		// copy lhs matrix and add rhs matrix
		return ve::matrix<type, rows, cols>{lhs} += rhs;
	}

	/* - operator */
	template <typename type, unsigned rows, unsigned cols>
	auto operator-(const ve::matrix<type, rows, cols>& lhs,
				   const ve::matrix<type, rows, cols>& rhs) noexcept -> ve::matrix<type, rows, cols> {

		// copy lhs matrix and subtract rhs matrix
		return ve::matrix<type, rows, cols>{lhs} -= rhs;
	}

	/* * operator */
	template <typename type, unsigned rows, unsigned cols>
	auto operator*(const ve::matrix<type, rows, cols>& lhs,
				   const ve::matrix<type, rows, cols>& rhs) noexcept -> ve::matrix<type, rows, cols> {

		// copy lhs matrix and multiply rhs matrix
		return ve::matrix<type, rows, cols>{lhs} *= rhs;
	}

	/* / operator */
	template <typename type, unsigned rows, unsigned cols>
	auto operator/(const ve::matrix<type, rows, cols>& lhs,
				   const ve::matrix<type, rows, cols>& rhs) noexcept -> ve::matrix<type, rows, cols> {

		// copy lhs matrix and divide rhs matrix
		return ve::matrix<type, rows, cols>{lhs} /= rhs;
	}





} // namespace ve

#endif // ___ve_structures_matrix___
