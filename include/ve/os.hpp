#ifndef ___ve_os___
#define ___ve_os___

#if defined(_WIN32) || defined(_WIN64)
	#define ___ve_windows___
	#define ENGINE_OS_WINDOWS
	#define RENDERX_OS_WINDOWS

#elif defined(__linux__)
	#define ___ve_linux___
	#define ENGINE_OS_LINUX
	#define RENDERX_OS_LINUX

#elif defined(__APPLE__) && defined(__MACH__)
	#define ___ve_macos___
	#define ENGINE_OS_MACOS
	#define RENDERX_OS_MACOS

#endif

#endif // ___ve_os___
