#include "glfw_window.hpp"


glfw::window::window(void) noexcept
: _window{nullptr} {

	if (glfw::system::is_initialized() == false)
		return;

	::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	_window = ::glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	if (_window == nullptr)
		return;

	while (!::glfwWindowShouldClose(_window)) {
		::glfwPollEvents();
	}
}



glfw::window::~window(void) noexcept {
	if (_window != nullptr)
		::glfwDestroyWindow(_window);
}
