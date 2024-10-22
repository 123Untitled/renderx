#include "ve/structures/vector2.hpp"

#include "ve/math/sqrt.hpp"


// -- public lifecycle --------------------------------------------------------

/* constructor */
ve::vector2::vector2(const float f1, const float f2) noexcept
: x{f1}, y{f2} {
}


// -- public arithmetic operators ---------------------------------------------

/* addition assignment operator */
auto ve::vector2::operator+=(const ___self& rhs) noexcept -> ___self& {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

/* subtraction assignment operator */
auto ve::vector2::operator-=(const ___self& rhs) noexcept -> ___self& {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

/* multiplication assignment operator */
auto ve::vector2::operator*=(const ___self& rhs) noexcept -> ___self& {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

/* division assignment operator */
auto ve::vector2::operator/=(const ___self& rhs) noexcept -> ___self& {
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}


/* scalar multiplication assignment operator */
auto ve::vector2::operator*=(const float scalar) noexcept -> ___self& {
	x *= scalar;
	y *= scalar;
	return *this;
}

/* scalar division assignment operator */
auto ve::vector2::operator/=(const float scalar) noexcept -> ___self& {
	x /= scalar;
	y /= scalar;
	return *this;
}


/* unary plus operator */
auto ve::vector2::operator+(void) noexcept -> ___self& {
	return *this;
}

/* unary minus operator */
auto ve::vector2::operator-(void) const noexcept -> ___self {
	return ___self{-x, -y};
}


// -- non-member functions ----------------------------------------------------

/* dot product */
auto ve::dot(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> float {
	return float{(lhs.x * rhs.x) + (lhs.y * rhs.y)};
}

/* cross product */
auto ve::cross(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> float {
	return float{(lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

/* length */
auto ve::length(const ve::vector2& v) noexcept -> float {
	return ve::sqrt((v.x * v.x) + (v.y * v.y));
}

/* normalize */
auto ve::normalize(const ve::vector2& v) noexcept -> ve::vector2 {

	// get the length
	const float len{ve::length(v)};

	return len != 0.0f ? ve::vector2{v.x / len, v.y / len}
					   : ve::vector2{0.0f, 0.0f};
}

/* distance */
auto ve::distance(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> float {
	return ve::length(lhs - rhs);
}

/* lerp */
auto ve::lerp(const ve::vector2& lhs, const ve::vector2& rhs, const float t) noexcept -> ve::vector2 {
	return lhs + ((rhs - lhs) * t);
}

/* reflect */
auto ve::reflect(const ve::vector2& v, const ve::vector2& n) noexcept -> ve::vector2 {
	return v - (n * (2.0f * ve::dot(v, n)));
}

/* midpoint */
auto ve::midpoint(const ve::vector2& v1, const ve::vector2& v2) noexcept -> ve::vector2 {
	return ve::vector2{
		(v1.x + v2.x) / 2.0f,
		(v1.y + v2.y) / 2.0f
	};
}


// -- arithmetic non-member operators -----------------------------------------

/* addition operator */
auto ve::operator+(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> ve::vector2 {
	return ve::vector2{lhs.x + rhs.x, lhs.y + rhs.y};
}

/* subtraction operator */
auto ve::operator-(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> ve::vector2 {
	return ve::vector2{lhs.x - rhs.x, lhs.y - rhs.y};
}

/* multiplication operator */
auto ve::operator*(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> ve::vector2 {
	return ve::vector2{lhs.x * rhs.x, lhs.y * rhs.y};
}

/* division operator */
auto ve::operator/(const ve::vector2& lhs, const ve::vector2& rhs) noexcept -> ve::vector2 {
	return ve::vector2{lhs.x / rhs.x, lhs.y / rhs.y};
}

/* scalar multiplication operator */
auto ve::operator*(const ve::vector2& v, const float scalar) noexcept -> ve::vector2 {
	return ve::vector2{v.x * scalar, v.y * scalar};
}

/* scalar multiplication operator (reverse) */
auto ve::operator*(const float scalar, const ve::vector2& v) noexcept -> ve::vector2 {
	return ve::vector2{v.x * scalar, v.y * scalar};
}

/* scalar division operator */
auto ve::operator/(const ve::vector2& v, const float scalar) noexcept -> ve::vector2 {
	return ve::vector2{v.x / scalar, v.y / scalar};
}
