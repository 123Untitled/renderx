#include "ve/glfw/window.hpp"
#include "ve/glfw/system.hpp"
#include "ve/exceptions.hpp"

#include "ve/running.hpp"

// -- private static methods --------------------------------------------------

/* shared */
auto glfw::window::_shared(void) noexcept -> ___self& {
	static ___self ___ins;
	return ___ins;
}

/* size callback */
auto glfw::window::_size_callback(::glfw_window* window,
									const int width,
									const int height) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	//std::cout << "resize callback [" << width << ", " << height << "]" << std::endl;
}

/* close callback */
auto glfw::window::_close_callback(::glfw_window* window) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);


	ve::running::stop();

	//if (user != nullptr)
		//::glfw_set_window_should_close(window, GLFW_TRUE);

	std::cout << "close callback" << std::endl;
}

/* iconify callback */
auto glfw::window::_iconify_callback(::glfw_window* window,
									 const int iconified) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	std::cout << "iconify callback [" << iconified << "]" << std::endl;
}

/* focus callback */
auto glfw::window::_focus_callback(::glfw_window* window,
								   const int focused) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	std::cout << "focus callback [" << focused << "]" << std::endl;
}

/* maximize callback */
auto glfw::window::_maximize_callback(::glfw_window* window,
									  const int maximized) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	std::cout << "maximize callback [" << maximized << "]" << std::endl;
}

/* refresh callback */
auto glfw::window::_refresh_callback(::glfw_window* window) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	std::cout << "refresh callback" << std::endl;
}

/* framebuffer size callback */
auto glfw::window::_framebuffer_size_callback(::glfw_window* window,
											  const int width,
											  const int height) noexcept -> void {

	// get user pointer
	___self& win = *static_cast<___self*>(::glfw_get_window_user_pointer(window));

	//std::cout << "framebuffer size callback [" << width << ", " << height << "]" << std::endl;

	// set resize flag
	win._resize = true;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
glfw::window::window(void)
: _window{nullptr}, _resize{false} {


	// initialize glfw
	glfw::system::init();


	// set client api
	::glfw_window_hint(GLFW_CLIENT_API, GLFW_NO_API);

	// set resizable
	::glfw_window_hint(GLFW_RESIZABLE, GLFW_TRUE);

	// set visible
	::glfw_window_hint(GLFW_VISIBLE, GLFW_TRUE);

	// transparent
	//::glfw_window_hint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	// no decorations
	//::glfw_window_hint(GLFW_DECORATED, GLFW_FALSE);

	// focus on show
	::glfw_window_hint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);



	// compute window size with 2:39 aspect ratio
	const float width = 1000;
	const float height = width / 2.39f;




	// create window
	_window = ::glfw_create_window((int)width,
								   (int)height,
								   "グラフィックエンジン",
								   nullptr, nullptr);

	if (_window == nullptr)
		throw ve::exception{"failed to create glfw window."};


	::glfw_set_window_user_pointer(_window, this);


	//::glfw_set_window_opacity(_window, 0.95f);


	// -- setup callbacks -----------------------------------------------------

	// set size callback
	static_cast<void>(::glfw_set_window_size_callback(_window,
						___self::_size_callback));

	// set close callback
	static_cast<void>(::glfw_set_window_close_callback(_window,
						___self::_close_callback));

	// set iconify callback
	static_cast<void>(::glfw_set_window_iconify_callback(_window,
						___self::_iconify_callback));

	// set focus callback
	static_cast<void>(::glfw_set_window_focus_callback(_window,
						___self::_focus_callback));

	// set maximize callback
	static_cast<void>(::glfw_set_window_maximize_callback(_window,
						___self::_maximize_callback));

	// set refresh callback
	static_cast<void>(::glfw_set_window_refresh_callback(_window,
						___self::_refresh_callback));

	// set framebuffer size callback
	static_cast<void>(::glfw_set_framebuffer_size_callback(_window,
						___self::_framebuffer_size_callback));
}

//_glfwInputFramebufferSize


/* destructor */
glfw::window::~window(void) noexcept {

	// free window
	::glfw_destroy_window(_window);
}



// -- public static accessors -------------------------------------------------

/* shared */
auto glfw::window::shared(void) noexcept -> ::glfw_window& {
	return *(___self::_shared()._window);
}

/* should close */
auto glfw::window::should_close(void) noexcept -> bool {
	return ::glfw_window_should_close(___self::_shared()._window);
}

// -- public static methods ---------------------------------------------------

/* hide */
auto glfw::window::hide(void) noexcept -> void {
	::glfw_hide_window(___self::_shared()._window);
}

/* show */
auto glfw::window::show(void) noexcept -> void {
	::glfw_show_window(___self::_shared()._window);
}

/* framebuffer size */
auto glfw::window::framebuffer_size(void) -> vk::extent2D {

	int x, y;

	// get framebuffer size
	::glfw_get_framebuffer_size(___self::_shared()._window, &x, &y);

	// check for error
	if (x == 0 || y == 0)
		throw ve::exception{"failed to get framebuffer size."};

	// return extent
	return vk::extent2D{
		static_cast<vk::u32>(x),
		static_cast<vk::u32>(y)
	};
}

/* resized */
auto glfw::window::resized(void) noexcept -> bool {

	const bool resize = ___self::_shared()._resize;

	___self::_shared()._resize = false;

	return resize;
}
