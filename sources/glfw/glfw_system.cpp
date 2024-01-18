#include "glfw_system.hpp"
#include <vulkan/vulkan.h>


/* default constructor */
glfw::system::system(void)
: _initialized{false} {
	if (::glfwInit() != GLFW_TRUE)
		throw engine::exception{"failed to initialize glfw."};
	_initialized = true;
	static_cast<void>(::glfwSetErrorCallback(glfw::system::error_callback));
}

/* destructor */
glfw::system::~system(void) noexcept {
	if (_initialized == false)
		return;
	::glfwTerminate();
}

/* is initialized */
auto glfw::system::is_initialized(void) noexcept -> bool {
	return shared()._initialized;
}

/* vulkan required extensions */
auto glfw::system::vulkan_required_extensions(void) -> std::vector<const char*> {

	if (glfw::system::is_initialized() == false)
		return {};

	::uint32_t        count = 0;
	const char** extensions = ::glfwGetRequiredInstanceExtensions(&count);

	if (extensions == nullptr) {
		throw engine::exception{"failed to get glfw required instance extensions."};
	}

	std::vector<const char*> result;
	result.resize(count);
	for (::uint32_t i = 0; i < count; ++i)
		result[i] = extensions[i];

// check macos system
#if defined(ENGINE_OS_MACOS)
	result.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

	return result;
}

/* is vulkan supported */
auto glfw::system::is_vulkan_supported(void) -> bool {
	self& instance = shared();
	if (instance._initialized == false)
		return false;
	return ::glfwVulkanSupported() == GLFW_TRUE;
}

/* shared */
auto glfw::system::shared(void) noexcept -> self& {
	static self instance;
	return instance;
}

/* error callback */
void glfw::system::error_callback(int error_code, const char* description) noexcept {
	std::cerr << "error: glfw error " << error_code << ": " << description << std::endl;
}
