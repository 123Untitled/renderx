#ifndef ___ve_vulkan___
#define ___ve_vulkan___

#include "ve/os.hpp"

// linux
#if defined(___ve_linux___)
#define VK_USE_PLATFORM_XCB_KHR

// win32 header
#elif defined(___ve_windows___)
#define VK_USE_PLATFORM_WIN32_KHR

// macos header
#elif defined(___ve_macos___)
#define VK_USE_PLATFORM_MACOS_MVK

#endif

// vulkan header
#include <vulkan/vulkan.h>

#endif // ___ve_vulkan___
