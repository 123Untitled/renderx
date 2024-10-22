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

#ifndef ___ve_structures_vector2___
#define ___ve_structures_vector2___



// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- V E C T O R 2 -------------------------------------------------------

	class vector2 final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::vector2;


		public:

			// -- public members ----------------------------------------------

			/* x, y */
			float x, y;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vector2(void) noexcept = default;

			/* constructor */
			vector2(const float, const float) noexcept;

			/* copy constructor */
			vector2(const ___self&) noexcept = default;

			/* destructor */
			~vector2(void) noexcept = default;


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


	}; // class vector2


	// -- non-member functions ------------------------------------------------

	/* dot product */
	auto dot(const ve::vector2&, const ve::vector2&) noexcept -> float;

	/* cross product */
	auto cross(const ve::vector2&, const ve::vector2&) noexcept -> float;

	/* length */
	auto length(const ve::vector2&) noexcept -> float;

	/* normalize */
	auto normalize(const ve::vector2&) noexcept -> ve::vector2;

	/* distance */
	auto distance(const ve::vector2&, const ve::vector2&) noexcept -> float;

	/* lerp */
	auto lerp(const ve::vector2&, const ve::vector2&, const float) noexcept -> ve::vector2;

	/* reflect */
	auto reflect(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;

	/* midpoint */
	auto midpoint(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;


	// -- non-member arithmetic operators -------------------------------------

	/* addition operator */
	auto operator+(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;

	/* subtraction operator */
	auto operator-(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;

	/* multiplication operator */
	auto operator*(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;

	/* division operator */
	auto operator/(const ve::vector2&, const ve::vector2&) noexcept -> ve::vector2;


	/* scalar multiplication operator */
	auto operator*(const ve::vector2&, const float) noexcept -> ve::vector2;

	/* scalar multiplication operator (reverse) */
	auto operator*(const float, const ve::vector2&) noexcept -> ve::vector2;

	/* scalar division operator */
	auto operator/(const ve::vector2&, const float) noexcept -> ve::vector2;

} // namespace ve

#endif // ___ve_structures_vector2___
