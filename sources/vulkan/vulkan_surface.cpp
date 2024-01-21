#include "vulkan_surface.hpp"
#include "vulkan_physical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void) noexcept
: _surface{nullptr} {}

/* window constructor */
vulkan::surface::surface(glfw::window& window)
: _surface{nullptr} {

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

/* VkSurfaceKHR conversion operator */
vulkan::surface::operator const ::VkSurfaceKHR&(void) const noexcept {
	return _surface;
}





// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::surface::free(void) noexcept -> void {
	if (_surface == nullptr)
		return;
	// destroy surface
	::vkDestroySurfaceKHR(vulkan::instance::shared(), _surface, nullptr);
}

/* init */
auto vulkan::surface::init(void) noexcept -> void {
	_surface = nullptr;
}

