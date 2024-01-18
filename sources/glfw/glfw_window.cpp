#include "glfw_window.hpp"


/* default constructor */
glfw::window::window(void)
: _window{nullptr} {

	if (glfw::system::is_initialized() == false)
		return;

	::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	_window = ::glfwCreateWindow(640, 480, "engine", nullptr, nullptr);

	if (_window == nullptr)
		throw engine::exception{"failed to create glfw window."};
}

/* destructor */
glfw::window::~window(void) noexcept {
	if (_window == nullptr)
		return;
	::glfwDestroyWindow(_window);
}

/* should close */
auto glfw::window::should_close(void) const noexcept -> bool {
	return ::glfwWindowShouldClose(_window);
}

///* ::GLFWwindow* conversion operator */
//glfw::window::operator ::GLFWwindow*(void) noexcept {
//	return _window;
//}
