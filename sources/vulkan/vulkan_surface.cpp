#include "vulkan_surface.hpp"
#include "vulkan_physical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void) noexcept
: _surface{VK_NULL_HANDLE} {}

/* window constructor */
vulkan::surface::surface(glfw::window& window)
: _surface{VK_NULL_HANDLE} {

	// create surface
	if (::glfwCreateWindowSurface(vulkan::instance::shared(),
								 window.underlying(), nullptr, &_surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};
}

/* move constructor */
vulkan::surface::surface(self&& other) noexcept
: _surface{other._surface} {
	other.init();
}

/* destructor */
vulkan::surface::~surface(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::surface::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	 _surface = other._surface;
	other.init();
	return *this;
}


// -- public conversion operators ---------------------------------------------

/* vk::surface conversion operator */
vulkan::surface::operator const vk::surface&(void) const noexcept {
	return _surface;
}


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::surface::free(void) noexcept -> void {
	if (_surface == VK_NULL_HANDLE)
		return;
	// destroy surface
	vk::destroy_surface(vulkan::instance::shared(), _surface);
}

/* init */
auto vulkan::surface::init(void) noexcept -> void {
	_surface = VK_NULL_HANDLE;
}

