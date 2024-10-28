#ifndef ___void_engine_memory_malloc___
#define ___void_engine_memory_malloc___

#include "ve/types.hpp"
#include <cstdlib>
#include <new>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


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
	template <typename T>
	auto realloc(T* const ptr, const ve::size_t count) -> T* {

		// reallocate memory
		T* const new_ptr = static_cast<T*>(::realloc(ptr, count * sizeof(T)));

		// check if reallocation was successful
		if (new_ptr == nullptr)
			throw std::bad_alloc();

		// return pointer
		return new_ptr;
	}

} // namespace ve

#endif // ___void_engine_memory_malloc___
