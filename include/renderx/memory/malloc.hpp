#ifndef ___RENDERX_MEMORY_MALLOC___
#define ___RENDERX_MEMORY_MALLOC___

#include "engine/types.hpp"
#include <cstdlib>
#include <new>


// -- R X  N A M E S P A C E --------------------------------------------------

namespace rx {


	/* malloc */
	template <typename ___type>
	auto malloc(const rx::size_t ___cnt) -> ___type* {

		// allocate memory
		___type* const ___ptr = static_cast<___type*>(::malloc(___cnt * sizeof(___type)));

		// check if allocation was successful
		if (___ptr == nullptr)
			throw std::bad_alloc();

		// return pointer
		return ___ptr;
	}

	/* free */
	template <typename ___type>
	auto free(___type* const ___ptr) noexcept -> void {
		// free memory
		::free(___ptr);
	}

	/* realloc */
	template <typename ___type>
	auto realloc(___type* const ___ptr, const rx::size_t ___cnt) -> ___type* {

		// reallocate memory
		___type* const ___new_ptr = static_cast<___type*>(::realloc(___ptr, ___cnt * sizeof(___type)));

		// check if reallocation was successful
		if (___new_ptr == nullptr)
			throw std::bad_alloc();

		// return pointer
		return ___new_ptr;
	}


} // namespace rx

#endif // ___RENDERX_MEMORY_MALLOC___
