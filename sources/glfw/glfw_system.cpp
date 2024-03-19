#include "glfw_system.hpp"
#include "exceptions.hpp"
#include "os.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>


/* default constructor */
glfw::system::system(void) {

	// initialize glfw
	if (::glfwInit() != GLFW_TRUE)
		throw engine::exception{"failed to initialize glfw."};

	// check vulkan support
	if (::glfwVulkanSupported() == GLFW_FALSE) {
		::glfwTerminate();
		throw engine::exception{"glfw: vulkan is not supported."};
	}

	// set error callback
	static_cast<void>(::glfwSetErrorCallback(glfw::system::error_callback));
}

/* destructor */
glfw::system::~system(void) noexcept {
	::glfwTerminate();
}

/* vulkan required extensions */
auto glfw::system::vulkan_required_extensions(void) -> xns::vector<const char*> {

	::uint32_t        count = 0;
	const char** extensions = ::glfwGetRequiredInstanceExtensions(&count);

	if (extensions == nullptr)
		throw engine::exception{"failed to get glfw required instance extensions."};

	xns::vector<const char*> result;
	result.reserve(count);

// check macos system
#if defined(ENGINE_OS_MACOS)
	result.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	result.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif
// validation layers check
#if defined(ENGINE_VL_DEBUG)
	result.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	for (::uint32_t i = 0; i < count; ++i)
		result.push_back(extensions[i]);



	return result;
}


// -- private methods ---------------------------------------------------------

/* new window */
auto glfw::system::new_window(const int width,
							  const int height,
							  const char* title, GLFWmonitor* monitor, GLFWwindow* share) -> GLFWwindow* {
	return ::glfwCreateWindow(width, height, title, monitor, share);
}


// -- private static methods --------------------------------------------------

/* shared */
auto glfw::system::shared(void) noexcept -> self& {
	static self instance;
	return instance;
}

/* error callback */
void glfw::system::error_callback(int error_code, const char* description) noexcept {
	std::cerr << "error: glfw error " << error_code << ": " << description << std::endl;
}
