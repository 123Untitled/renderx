#ifndef ___RENDERX_MEMORY_MEMCPY___
#define ___RENDERX_MEMORY_MEMCPY___

#include <cstddef>
#include "engine/types.hpp"


// -- R X  N A M E S P A C E --------------------------------------------------

namespace rx {

	/* memcpy */
	template <typename ___type>
	auto memcpy(void* dst, const ___type* src, const rx::size_t count) noexcept -> void {
		__builtin_memcpy(dst, src, count * sizeof(___type));
	}

} // namespace rx

#endif // ___RENDERX_MEMORY_MEMCPY___
