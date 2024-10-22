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

#ifndef ___ve_structures_vector3___
#define ___ve_structures_vector3___

#include "ve/config.hpp"

#if !___ve_has_attribute(__ext_vector_type__) || !___ve_has_attribute(__overloadable__)
#	error "compiler does not support built-in vector types"
#endif



// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- V E C T O R 3 -------------------------------------------------------

	class vector3 final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::vector3;


		public:

			// -- public members ----------------------------------------------

			/* x, y, z */
			float x, y, z;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vector3(void) noexcept = default;

			/* constructor */
			vector3(const float, const float, const float) noexcept;

			/* copy constructor */
			vector3(const ___self&) noexcept = default;

			/* move constructor */
			vector3(___self&&) noexcept = default;

			/* destructor */
			~vector3(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public comparison operators ---------------------------------

			/* equality operator */
			auto operator==(const ___self&) const noexcept -> bool = default;

			/* inequality operator */
			auto operator!=(const ___self&) const noexcept -> bool = default;


			// -- public arithmetic operators ---------------------------------

			/* addition assignment operator */
			auto operator+=(const ___self&) noexcept -> ___self&;

			/* subtraction assignment operator */
			auto operator-=(const ___self&) noexcept -> ___self&;

			/* multiplication assignment operator */
			auto operator*=(const ___self&) noexcept -> ___self&;

			/* division assignment operator */
			auto operator/=(const ___self&) noexcept -> ___self&;

			/* scalar multiplication assignment operator */
			auto operator*=(const float) noexcept -> ___self&;

			/* scalar division assignment operator */
			auto operator/=(const float) noexcept -> ___self&;


			/* unary plus operator */
			auto operator+(void) noexcept -> ___self&;

			/* unary minus operator */
			auto operator-(void) const noexcept -> ___self;


			// -- public methods ----------------------------------------------

			/* normalize */
			auto normalize(void) noexcept -> ___self&;


	}; // class vector3


	// -- non-member functions ------------------------------------------------

	/* dot product */
	auto dot(const ve::vector3&, const ve::vector3&) noexcept -> float;

	/* cross product */
	auto cross(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;

	/* length */
	auto length(const ve::vector3&) noexcept -> float;

	/* normalize */
	auto normalize(const ve::vector3&) noexcept -> ve::vector3;

	/* distance */
	auto distance(const ve::vector3&, const ve::vector3&) noexcept -> float;

	/* lerp */
	auto lerp(const ve::vector3&, const ve::vector3&, const float) noexcept -> ve::vector3;

	/* reflect */
	auto reflect(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;

	/* midpoint */
	auto midpoint(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;




	// -- non-member arithmetic operators -------------------------------------

	/* addition operator */
	auto operator+(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;

	/* subtraction operator */
	auto operator-(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;

	/* multiplication operator */
	auto operator*(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;

	/* division operator */
	auto operator/(const ve::vector3&, const ve::vector3&) noexcept -> ve::vector3;


	/* scalar multiplication operator */
	auto operator*(const ve::vector3&, const float) noexcept -> ve::vector3;

	/* scalar multiplication operator (reverse) */
	auto operator*(const float, const ve::vector3&) noexcept -> ve::vector3;

	/* scalar division operator */
	auto operator/(const ve::vector3&, const float) noexcept -> ve::vector3;

} // namespace ve

#endif // ___ve_structures_vector3___
