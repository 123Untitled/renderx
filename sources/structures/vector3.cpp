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

#include "ve/structures/vector3.hpp"

#include "ve/math/sqrt.hpp"


// -- public lifecycle --------------------------------------------------------

/* constructor */
ve::vector3::vector3(const float f1, const float f2, const float f3) noexcept
: x{f1}, y{f2}, z{f3} {
}


// -- public arithmetic operators ---------------------------------------------


/* addition assignment operator */
auto ve::vector3::operator+=(const ___self& rhs) noexcept -> ___self& {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

/* subtraction assignment operator */
auto ve::vector3::operator-=(const ___self& rhs) noexcept -> ___self& {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

/* multiplication assignment operator */
auto ve::vector3::operator*=(const ___self& rhs) noexcept -> ___self& {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

/* division assignment operator */
auto ve::vector3::operator/=(const ___self& rhs) noexcept -> ___self& {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}


/* scalar multiplication assignment operator */
auto ve::vector3::operator*=(const float scalar) noexcept -> ___self& {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

/* scalar division assignment operator */
auto ve::vector3::operator/=(const float scalar) noexcept -> ___self& {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}


/* unary plus operator */
auto ve::vector3::operator+(void) noexcept -> ___self& {
	return *this;
}

/* unary minus operator */
auto ve::vector3::operator-(void) const noexcept -> ___self {
	return ___self{-x, -y, -z};
}


// -- public methods ----------------------------------------------------------

/* normalize */
auto ve::vector3::normalize(void) noexcept -> ___self& {

	// get the length
	const float len{ve::length(*this)};

	// normalize
	if (len != 0.0f) {
		x /= len;
		y /= len;
		z /= len;
	}

	// return self
	return *this;
}


// -- non-member functions ----------------------------------------------------

/* dot product */
auto ve::dot(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> float {
	return float{(lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z)};
}

/* cross product */
auto ve::cross(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{
		(lhs.y * rhs.z) - (lhs.z * rhs.y),
		(lhs.z * rhs.x) - (lhs.x * rhs.z),
		(lhs.x * rhs.y) - (lhs.y * rhs.x)
	};
}

/* length */
auto ve::length(const ve::vector3& v) noexcept -> float {
	return ve::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/* normalize */
auto ve::normalize(const ve::vector3& v) noexcept -> ve::vector3 {

	// get the length
	const float len{ve::length(v)};

	return len != 0.0f ? ve::vector3{v.x / len, v.y / len, v.z / len}
					   : ve::vector3{0.0f, 0.0f, 0.0f};
}

/* distance */
auto ve::distance(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> float {
	return ve::length(lhs - rhs);
}

/* lerp */
auto ve::lerp(const ve::vector3& lhs, const ve::vector3& rhs, const float t) noexcept -> ve::vector3 {
	return lhs + ((rhs - lhs) * t);
}

/* reflect */
auto ve::reflect(const ve::vector3& v, const ve::vector3& n) noexcept -> ve::vector3 {
	return v - (n * (2.0f * ve::dot(v, n)));
}

/* midpoint */
auto ve::midpoint(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{
		(lhs.x + rhs.x) / 2.0f,
		(lhs.y + rhs.y) / 2.0f,
		(lhs.z + rhs.z) / 2.0f
	};
}


// -- arithmetic non-member operators -----------------------------------------

/* addition operator */
auto ve::operator+(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

/* subtraction operator */
auto ve::operator-(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

/* multiplication operator */
auto ve::operator*(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

/* division operator */
auto ve::operator/(const ve::vector3& lhs, const ve::vector3& rhs) noexcept -> ve::vector3 {
	return ve::vector3{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

/* scalar multiplication operator */
auto ve::operator*(const ve::vector3& v, const float scalar) noexcept -> ve::vector3 {
	return ve::vector3{v.x * scalar, v.y * scalar, v.z * scalar};
}

/* scalar multiplication operator (reverse) */
auto ve::operator*(const float scalar, const ve::vector3& v) noexcept -> ve::vector3 {
	return ve::vector3{v.x * scalar, v.y * scalar, v.z * scalar};
}

/* scalar division operator */
auto ve::operator/(const ve::vector3& v, const float scalar) noexcept -> ve::vector3 {
	return ve::vector3{v.x / scalar, v.y / scalar, v.z / scalar};
}
