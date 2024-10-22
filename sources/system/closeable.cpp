#include "ve/system/closeable.hpp"
#include <unistd.h>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
rx::closeable::closeable(void) noexcept
: _desc{INVALID_DESCRIPTOR} {
}

/* descriptor constructor */
rx::closeable::closeable(const int ___desc) noexcept
: _desc{___desc} {
}

/* move constructor */
rx::closeable::closeable(___self&& ___ot) noexcept
: _desc{___ot._desc} {
	___ot._desc = INVALID_DESCRIPTOR;
}

/* destructor */
rx::closeable::~closeable(void) noexcept {
	_close();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto rx::closeable::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self assignment
	if (this == &___ot)
		return *this;

	// close current descriptor
	_close();

	// get ownership
	_desc = ___ot._desc;
	___ot._desc = INVALID_DESCRIPTOR;

	// return self-reference
	return *this;
}

/* int assignment operator */
auto rx::closeable::operator=(const int ___desc) noexcept -> ___self& {

	// close current descriptor
	_close();

	// assign new descriptor
	_desc = ___desc;

	// return self-reference
	return *this;
}


// -- public conversion operators ---------------------------------------------

/* int conversion operator */
rx::closeable::operator int(void) const noexcept {
	return _desc;
}

/* bool conversion operator */
rx::closeable::operator bool(void) const noexcept {
	return _desc != INVALID_DESCRIPTOR;
}


// -- public operators --------------------------------------------------------

/* not operator */
auto rx::closeable::operator!(void) const noexcept -> bool {
	return _desc == INVALID_DESCRIPTOR;
}


// -- public modifiers --------------------------------------------------------

/* close */
auto rx::closeable::close(void) noexcept -> void {
	_close();
	_desc = INVALID_DESCRIPTOR;
}


// -- private methods ---------------------------------------------------------

/* close */
auto rx::closeable::_close(void) noexcept -> void {
	if (_desc == INVALID_DESCRIPTOR)
		return;
	::close(_desc);
}
