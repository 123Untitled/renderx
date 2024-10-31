#include "ve/camera/projection.hpp"


// -- P R O J E C T I O N -----------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::projection::projection(void) noexcept
: _fov{120.0f}, _ratio{_4_3}, _near{0.0001f}, _far{10000.0f} {
}


// -- public accessors --------------------------------------------------------

/* matrix */
auto ve::projection::matrix(void) const noexcept -> glm::mat4 {

	const float ys = 1.0f / std::tan(((_fov / 180.0f) * static_cast<float>(M_PI)) * 0.5f);
	const float xs =   ys /  _ratio;
	const float zs = _far / (_near - _far);
	const float zt =   zs * _near;

	// return projection matrix
	return glm::mat4 {
		{+xs,   0,   0,   0},
		{  0, +ys,   0,   0},
		{  0,   0, -zs,   1},
		{  0,   0,  zt,   0}
	};
}

/* fov */
auto ve::projection::fov(void) const noexcept -> const float& {
	return _fov;
}

/* ratio */
auto ve::projection::ratio(void) const noexcept -> const float& {
	return _ratio;
}

/* near */
auto ve::projection::near(void) const noexcept -> const float& {
	return _near;
}

/* far */
auto ve::projection::far(void) const noexcept -> const float& {
	return _far;
}


// -- public modifiers --------------------------------------------------------

/* fov */
auto ve::projection::fov(const float& value) noexcept -> void {
	_fov = value;
}

/* ratio */
auto ve::projection::ratio(const float& value) noexcept -> void {
	_ratio = value;
}

/* near */
auto ve::projection::near(const float& value) noexcept -> void {
	_near = value;
}

/* far */
auto ve::projection::far(const float& value) noexcept -> void {
	_far = value;
}
