#ifndef ___RENDERX_SYSTEM_OPEN___
#define ___RENDERX_SYSTEM_OPEN___

#include "ve/types.hpp"
#include "ve/system/closeable.hpp"
#include <fcntl.h>
#include <stdexcept>


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	/* open */
	template <rx::size_t sz, typename... fl>
	auto open(const char (&path)[sz], const fl... flags) -> rx::closeable {

		const int desc = ::open(path, flags...);

		if (desc == rx::closeable::INVALID_DESCRIPTOR)
			throw std::runtime_error("rx::open() failed");

		return rx::closeable(desc);
	}

} // namespace rx

#endif // ___RENDERX_SYSTEM_OPEN___
