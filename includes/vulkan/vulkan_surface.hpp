#ifndef ENGINE_VULKAN_SURFACE_HPP
#define ENGINE_VULKAN_SURFACE_HPP

#include "glfw_window.hpp"
#include "vulkan_instance.hpp"
//#include "vulkan_physical_device.hpp"

#include "vk_typedefs.hpp"
#include "vk_functions.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* physical device */
	class physical_device;


	// -- S U R F A C E -------------------------------------------------------

	class surface final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::surface;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			surface(void) noexcept;

			/* window constructor */
			surface(const vulkan::shared<vk::instance>&,
					glfw::window&);

			/* copy constructor */
			surface(const self&) noexcept;

			/* move constructor */
			surface(self&&) noexcept;

			/* destructor */
			~surface(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* vk::surface conversion operator */
			operator const vk::surface&() const noexcept;

			/* vulkan::managed<vk::surface> conversion operator */
			operator const vulkan::managed<vk::surface,
										 vulkan::shared<vk::instance>>&() const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* surface */
			vulkan::managed<vk::surface,
							vulkan::shared<vk::instance>> _surface;

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
