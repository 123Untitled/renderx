#include "renderx/glfw/window.hpp"
#include "renderx/glfw/system.hpp"
#include "engine/exceptions.hpp"


// -- private static methods --------------------------------------------------

/* shared */
auto glfw::window::_shared(void) noexcept -> ___self& {
	static ___self ___ins;
	return ___ins;
}

/* resize callback */
auto glfw::window::_resize_callback(::glfw_window* window,
									const int width,
									const int height) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

	std::cout << "resize callback [" << width << ", " << height << "]" << std::endl;
}

/* close callback */
auto glfw::window::_close_callback(::glfw_window* window) noexcept -> void {

	// get user pointer
	void* user = ::glfw_get_window_user_pointer(window);

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


// -- private lifecycle -------------------------------------------------------

/* default constructor */
glfw::window::window(void)
: _window{nullptr} {


	// initialize glfw
	glfw::system::init();


	// set client api
	::glfw_window_hint(GLFW_CLIENT_API, GLFW_NO_API);
	// set resizable
	::glfw_window_hint(GLFW_RESIZABLE, GLFW_TRUE);
	// set visible
	::glfw_window_hint(GLFW_VISIBLE, GLFW_TRUE);

	::glfw_window_hint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	// no decorations
	::glfw_window_hint(GLFW_DECORATED, GLFW_TRUE);
	// focus on show
	::glfw_window_hint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);


	// create window
	_window = ::glfw_create_window(800, 600, "グラフィックエンジン", nullptr, nullptr);


	if (_window == nullptr)
		throw engine::exception{"failed to create glfw window."};

	static void* user_data = nullptr;
	::glfw_set_window_user_pointer(_window, user_data);


	::glfw_set_window_opacity(_window, 0.9f);


	// -- setup callbacks -----------------------------------------------------

	// set resize callback
	static_cast<void>(::glfw_set_window_size_callback(_window,
						___self::_resize_callback));

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

}


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
