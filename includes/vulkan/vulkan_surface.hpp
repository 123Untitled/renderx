#ifndef ENGINE_VULKAN_SURFACE_HPP
#define ENGINE_VULKAN_SURFACE_HPP

#include "glfw_window.hpp"
#include "vulkan_instance.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S U R F A C E -------------------------------------------------------

	class surface final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::surface;


			// -- public lifecycle --------------------------------------------

			/* instance and window constructor */
			surface(const vulkan::instance&, glfw::window&);

			/* deleted copy constructor */
			surface(const self&) = delete;

			/* move constructor */
			surface(self&&) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkSurfaceKHR&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkSurfaceKHR&;


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* surface */
			::VkSurfaceKHR _surface;

			/* instance */
			::VkInstance _instance;

	}; // class surface

} // namespace vulkan

#endif // ENGINE_VULKAN_SURFACE_HPP


			//// -- private methods ---------------------------------------------
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
