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

			/* operator[] */
			auto operator[](const unsigned i) noexcept -> type(&)[cols] {
				return _mat[i];
			}

			/* const operator[] */
			auto operator[](const unsigned i) const noexcept -> const type(&)[cols] {
				return _mat[i];
			}

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


			// -- public arithmetic operators ---------------------------------

			enum _op_ {
				VE_MATRIX_ADD,
				VE_MATRIX_SUB,
				VE_MATRIX_MUL,
				VE_MATRIX_DIV
			};

			template <_op_ operation, size_type... indices>
			auto _operation(const ___self& other, ve::index_sequence<indices...>) noexcept -> void {
				if constexpr (operation == VE_MATRIX_ADD) {
					((_mat[indices] += other._mat[indices]), ...);
				}
				else if constexpr (operation == VE_MATRIX_SUB) {
					((_mat[indices] -= other._mat[indices]), ...);
				}
				else if constexpr (operation == VE_MATRIX_MUL) {
					((_mat[indices] *= other._mat[indices]), ...);
				}
				else if constexpr (operation == VE_MATRIX_DIV) {
					((_mat[indices] /= other._mat[indices]), ...);
				}
			}

			/* += operator */
			auto operator+=(const ___self& other) noexcept -> ___self& {
				___self::_operation<VE_MATRIX_ADD>(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* -= operator */
			auto operator-=(const ___self& other) noexcept -> ___self& {
				___self::_operation<VE_MATRIX_SUB>(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* *= operator */
			auto operator*=(const ___self& other) noexcept -> ___self& {
				___self::_operation<VE_MATRIX_MUL>(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

			/* /= operator */
			auto operator/=(const ___self& other) noexcept -> ___self& {
				___self::_operation<VE_MATRIX_DIV>(other, ve::make_index_sequence<VE_MATRIX_SIZE>{});
				return *this;
			}

	}; // class matrix



} // namespace ve

#endif // ___ve_structures_matrix___
