#include "glfw_window.hpp"


/* default constructor */
glfw::window::window(void) noexcept
: _window{nullptr} {

	if (glfw::system::is_initialized() == false)
		return;

	::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	_window = ::glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	if (_window == nullptr)
		return;
	std::cout << "glfw window created." << std::endl;
}

/* destructor */
glfw::window::~window(void) noexcept {
	if (_window == nullptr)
		return;
	::glfwDestroyWindow(_window);
	std::cout << "glfw window destroyed." << std::endl;
}

/* should close */
auto glfw::window::should_close(void) const noexcept -> bool {
	return ::glfwWindowShouldClose(_window);
}

///* ::GLFWwindow* conversion operator */
//glfw::window::operator ::GLFWwindow*(void) noexcept {
//	return _window;
//}
