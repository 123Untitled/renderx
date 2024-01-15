#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>
#include <iostream>


namespace glfw {

	class window final {

		public:

			window(void) noexcept
			: _initialized{false} {
				if (::glfwInit() != GLFW_TRUE)
					return;
				_initialized = true;
				::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
				_window = ::glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
				if (_window == nullptr)
					return;

				while (!::glfwWindowShouldClose(_window)) {
					::glfwPollEvents();
				}
			}

			~window(void) noexcept {
				if (_window != nullptr)
					::glfwDestroyWindow(_window);
				if (_initialized == true)
					::glfwTerminate();
			}

		private:

			// -- private members -------------------------------------------------

			/* initialized */
			bool _initialized;

			/* window */
			::GLFWwindow* _window;
	};

}

namespace vulkan {

	class instance final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::instance;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			instance(void) noexcept
			: _instance{nullptr} {

				::VkApplicationInfo info{};
				info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				info.pApplicationName   = "application";
				info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				info.pEngineName        = "engine";
				info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);

				::VkInstanceCreateInfo create{};
				create.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				create.pApplicationInfo = &info;

				::uint32_t        count = 0;
				const char** extensions = ::glfwGetRequiredInstanceExtensions(&count);

				std::cout << "extensions: " << count << std::endl;

				// print extensions
				for (::uint32_t i = 0; i < count; ++i)
					std::cout << extensions[i] << std::endl;

				create.enabledExtensionCount   = count;
				create.ppEnabledExtensionNames = extensions;

				create.enabledLayerCount       = 0;

				::VkResult result = ::vkCreateInstance(&create, nullptr, &_instance);

				if (result != VK_SUCCESS)
					std::cerr << "error: failed to create vulkan instance" << std::endl;
			}

			/* deleted copy constructor */
			instance(const self&) = delete;

			/* move constructor */
			instance(self&& other) noexcept
			: _instance{other._instance} {
				other._instance = nullptr;
			}

			/* destructor */
			~instance(void) noexcept {
				if (_instance == nullptr)
					return;
				::vkDestroyInstance(_instance, nullptr);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				if (_instance != nullptr)
					::vkDestroyInstance(_instance, nullptr);
				_instance = other._instance;
				other._instance = nullptr;
				return *this;
			}


		private:

			// -- private members ---------------------------------------------

			/* instance */
			::VkInstance _instance;

	};


	class device final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::device;



		private:

			// -- private members ---------------------------------------------

			/* device */
			::VkDevice _device;

	};

}



int main(void) {

	//glfw::window win;
	vulkan::instance instance;


	return 0;
}
