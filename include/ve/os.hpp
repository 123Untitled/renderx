/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_OS_HEADER
#define ENGINE_OS_HEADER

#if defined(_WIN32) || defined(_WIN64)
	#define ENGINE_OS_WINDOWS
	#define RENDERX_OS_WINDOWS
	#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(__linux__)
	#define ENGINE_OS_LINUX
	#define RENDERX_OS_LINUX
	#define VK_USE_PLATFORM_XCB_KHR
#elif defined(__APPLE__) && defined(__MACH__)
	#define ENGINE_OS_MACOS
	#define RENDERX_OS_MACOS
	#define VK_USE_PLATFORM_MACOS_MVK
#endif

#endif // ENGINE_OS_HEADER
