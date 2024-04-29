#include "engine/glfw/window.hpp"
#include "engine/glfw/system.hpp"
#include "engine/exceptions.hpp"


/* default constructor */
glfw::window::window(void) noexcept
: _window{nullptr} {}

/* width and height constructor */
glfw::window::window(const int width, const int height)
: _window{nullptr} {

	auto& system = glfw::system::shared();

	::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	_window = system.new_window(width, height, "engine", nullptr, nullptr);

	if (_window == nullptr)
		throw engine::exception{"failed to create glfw window."};

	static void* user_data = nullptr;
	::glfwSetWindowUserPointer(_window, user_data);

	// set resize callback
	static_cast<void>(::glfwSetWindowSizeCallback(_window, self::resize_callback));


}

/* move constructor */
glfw::window::window(self&& other) noexcept
: _window{other._window} {
	other.init();
}

/* destructor */
glfw::window::~window(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto glfw::window::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	_window = other._window;
	other.init();
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying pointer */
auto glfw::window::underlying(void) noexcept -> ::GLFWwindow* {
	return _window;
}

/* const underlying pointer */
auto glfw::window::underlying(void) const noexcept -> const ::GLFWwindow* {
	return _window;
}

/* should close */
auto glfw::window::should_close(void) const noexcept -> bool {
	return ::glfwWindowShouldClose(_window);
}


// -- private static methods --------------------------------------------------

/* resize callback */
auto glfw::window::resize_callback(::GLFWwindow* window,
									   const int width,
									   const int height) noexcept -> void {

	// get user pointer
	void* user = ::glfwGetWindowUserPointer(window);

	std::cout << "resize callback [" << width << ", " << height << "]" << std::endl;
}


// -- private methods ---------------------------------------------------------

/* free */
auto glfw::window::free(void) noexcept -> void {
	if (_window == nullptr)
		return;
	::glfwDestroyWindow(_window);
}

/* init */
auto glfw::window::init(void) noexcept -> void {
	_window = nullptr;
}
