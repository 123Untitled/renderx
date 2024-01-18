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

			/* default constructor */
			surface(vulkan::instance& instance, glfw::window& window) noexcept
			: _surface{nullptr}, _instance{&instance} {
				::VkResult result = ::glfwCreateWindowSurface(instance, &window, nullptr, &_surface);
				if (result != VK_SUCCESS) {
					std::cerr << "failed to create vulkan surface: " << result << std::endl;
					return;
				}
			}

			/* deleted copy constructor */
			surface(const self&) = delete;

			/* move constructor */
			surface(self&& other) noexcept
			: _surface{other._surface}, _instance{other._instance} {
				other.init();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				free();
				 _surface = other._surface;
				_instance = other._instance;
				other.init();
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> ::VkSurfaceKHR {
				return _surface;
			}


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				if (_surface == nullptr)
					return;
				::vkDestroySurfaceKHR(*_instance, _surface, nullptr);
			}

			/* init */
			auto init(void) noexcept -> void {
				_surface = nullptr;
				_instance = nullptr;
			}


			// -- private members ---------------------------------------------

			/* surface */
			::VkSurfaceKHR _surface;

			/* instance pointer */
			vulkan::instance* _instance;

	};


}

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
