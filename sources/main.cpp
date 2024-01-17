#define GLFW_INCLUDE_VULKAN

#include "os.hpp"

#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_queue_families.hpp"
#include <vulkan/vulkan.h>

#include <X11/Xlib.h>

namespace vulkan {


	class surface final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::surface;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			surface(vulkan::instance& instance, glfw::window& window) noexcept
			: _surface{self::create_platform_surface(instance, window)} {
			}


		private:

			// -- private methods ---------------------------------------------

			#if defined(ENGINE_OS_WINDOWS)
			static auto create_platform_surface(vulkan::instance& instance,
													glfw::window& window) noexcept -> ::VkSurfaceKHR {
				::VkWin32SurfaceCreateInfoKHR create{};
				create.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				create.hwnd = ::glfwGetWin32Window(window);
				/* create.hinstance = getModuleHandle(nullptr); */
				::VkSurfaceKHR surface = nullptr;

				VkResult result = ::vkCreateWin32SurfaceKHR(instance, &create, nullptr, &surface);

				if (result != VK_SUCCESS) {
					std::cerr << "failed to create vulkan surface" << std::endl;
					return nullptr;
				}

				return surface;
			}

			#elif defined(ENGINE_OS_LINUX)
			static auto create_platform_surface(vulkan::instance& instance,
													glfw::window& window) noexcept -> ::VkSurfaceKHR {
				::VkXcbSurfaceCreateInfoKHR create{};
				create.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
				//create.connection = ::XGetXCBConnection(
				//						::glfwGetX11Display()
				//					);
				::VkSurfaceKHR surface = nullptr;
				return surface;
			}

			#elif defined(ENGINE_OS_MACOS)
			static auto create_platform_surface(vulkan::instance& instance,
													glfw::window& window) noexcept -> ::VkSurfaceKHR {
				::VkMacOSSurfaceCreateInfoMVK create{};
				create.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
				create.pView = ::glfwGetCocoaWindow(window);
				::VkSurfaceKHR surface = nullptr;
				return surface;
			}
			#endif

			// -- private members ---------------------------------------------

			/* surface */
			::VkSurfaceKHR _surface;

	};
}


int main(void) {

	glfw::window win;
	glfw::events events;

	events.run(win);

	vulkan::instance instance;
	vulkan::physical_device device{instance};
	vulkan::queue_families families{device};

	return 0;
}
