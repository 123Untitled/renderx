/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_SURFACE___
#define ___ENGINE_VULKAN_SURFACE___

#include "ve/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- S U R F A C E -------------------------------------------------------

	class surface final {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using ___self = vulkan::surface;


			// -- private members ---------------------------------------------

			/* surface */
			vk::surface _surface;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			surface(void);

			/* deleted copy constructor */
			surface(const ___self&) = delete;

			/* deleted move constructor */
			surface(___self&&) = delete;

			/* destructor */
			~surface(void) noexcept;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static accessors -------------------------------------

			/* shared */
			static auto shared(void) -> vk::surface&;

	}; // class surface

} // namespace vulkan

#endif // ___ENGINE_VULKAN_SURFACE___





			// -- private methods ---------------------------------------------
			//
			//#if defined(ENGINE_OS_WINDOWS)
			//static auto create_platform_surface(vulkan::instance& instance,
			//										glfw::window& window) noexcept -> ::VkSurfaceKHR {
			//	::VkWin32SurfaceCreateInfoKHR create{};
			//	create.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			//	create.hwnd = ::glfwGetWin32Window(window);
			//	/* create.hinstance = getModuleHandle(nullptr); */
			//	::VkSurfaceKHR surface = nullptr;
			//
			//	VkResult result = ::vkCreateWin32SurfaceKHR(instance, &create, nullptr, &surface);
			//
			//	if (result != VK_SUCCESS) {
			//		std::cerr << "failed to create vulkan surface" << std::endl;
			//		return nullptr;
			//	}
			//
			//	return surface;
			//}
			//
			//#elif defined(ENGINE_OS_LINUX)
			//static auto create_platform_surface(vulkan::instance& instance,
			//										glfw::window& window) noexcept -> ::VkSurfaceKHR {
			//	::VkSurfaceKHR surface = nullptr;
			//	::VkXcbSurfaceCreateInfoKHR create{};
			//	create.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			//	//create.connection = ::XGetXCBConnection(
			//	//						::glfwGetX11Display()
			//	//					);
			//
			//	return surface;
			//}
			//
			//#elif defined(ENGINE_OS_MACOS)
			//static auto create_platform_surface(vulkan::instance& instance,
			//										glfw::window& window) noexcept -> ::VkSurfaceKHR {
			//	::VkSurfaceKHR surface = nullptr;
			//	::VkMacOSSurfaceCreateInfoMVK create{};
			//	create.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
			//	create.pView = &window;
			//	create.pNext = nullptr;
			//	create.flags = 0;
			//
			//	::VkResult result = ::vkCreateMacOSSurfaceMVK(instance, &create, nullptr, &surface);
			//
			//	if (result != VK_SUCCESS) {
			//		std::cerr << "failed to create vulkan surface: " << result << std::endl;
			//		return nullptr;
			//	}
			//	return surface;
			//}
			//#endif
