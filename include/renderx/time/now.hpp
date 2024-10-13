#ifndef ___RENDERX_TIME_NOW___
#define ___RENDERX_TIME_NOW___

#include "renderx/types.hpp"
#include <time.h>


// -- R X ---------------------------------------------------------------------

namespace rx {


	/* now */
	inline auto now(void) -> rx::umax {

		// get current time
		struct ::timespec ___ts;

		// get current time
		static_cast<void>(::clock_gettime(CLOCK_MONOTONIC_RAW, &___ts));
		//::clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW);

		// [EINVAL] clock_id is not a valid value.
		// [EFAULT] The tp argument address referenced invalid memory.

		// return time in nanoseconds
		return (static_cast<rx::umax>(___ts.tv_sec) * 1'000'000'000)
			+ static_cast<rx::umax>(___ts.tv_nsec);
	}

} // namespace rx

#endif // ___RENDERX_TIME_NOW___
