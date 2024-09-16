#ifndef ___ENGINE_WRITE_HPP___
#define ___ENGINE_WRITE_HPP___

#include "engine/os.hpp"

// use write() to print to stdout (Linux)
// use _write() to print to stdout (Windows)
// use write() to print to stdout (MacOS)

#if defined(ENGINE_OS_LINUX) || defined(ENGINE_OS_MACOS)
	#include <unistd.h>
#elif defined(ENGINE_OS_WINDOWS)
	#include <io.h>
#endif


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* write */
	template <decltype(sizeof(0)) ___size>
	auto write(const char (&___str)[___size]) -> void {
		#if defined(ENGINE_OS_LINUX) || defined(ENGINE_OS_MACOS)
			::write(STDOUT_FILENO, ___str, ___size - 1);
		#elif defined(ENGINE_OS_WINDOWS)
			::_write(STDOUT_FILENO, ___str, ___size - 1);
		#endif
	}

} // namespace vk

#endif // ___ENGINE_WRITE_HPP___
