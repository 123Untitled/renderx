#include "glfw_system.hpp"


/* default constructor */
glfw::system::system(void) noexcept
: _initialized{false} {
	if (::glfwInit() != GLFW_TRUE)
		return;
	_initialized = true;
	static_cast<void>(glfwSetErrorCallback(glfw::system::error_callback));
	std::cout << "glfw initialized." << std::endl;
}

/* destructor */
glfw::system::~system(void) noexcept {
	if (_initialized == false)
		return;
	::glfwTerminate();
	std::cout << "glfw terminated." << std::endl;
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
		std::cerr << "error: failed to get glfw required instance extensions" << std::endl;
		return {};
	}

	std::vector<const char*> result;
	result.resize(count);
	for (::uint32_t i = 0; i < count; ++i)
		result[i] = extensions[i];

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
