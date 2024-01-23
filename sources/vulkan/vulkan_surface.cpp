#include "vulkan_surface.hpp"
#include "vulkan_physical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void) noexcept
: _surface{} {}

/* instance and window constructor */
vulkan::surface::surface(const vulkan::shared<vk::instance>& instance,
						 glfw::window& window)
: _surface{} {

	vk::surface surface;

	// create surface
	if (::glfwCreateWindowSurface(instance,
								 window.underlying(), nullptr, &surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};


	_surface = vulkan::make_managed(surface, instance);
}

/* copy constructor */
vulkan::surface::surface(const self& other) noexcept
: _surface{other._surface} {
}

/* move constructor */
vulkan::surface::surface(self&& other) noexcept
: _surface{xns::move(other._surface)} {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::surface::operator=(const self& other) noexcept -> self& {
	_surface = other._surface;
	return *this;
}

/* move assignment operator */
auto vulkan::surface::operator=(self&& other) noexcept -> self& {
	_surface = xns::move(other._surface);
	return *this;
}


// -- public conversion operators ---------------------------------------------

/* vk::surface conversion operator */
vulkan::surface::operator const vk::surface&(void) const noexcept {
	return _surface;
}

/* vulkan::managed<vk::surface> conversion operator */
vulkan::surface::operator const vulkan::managed<vk::surface,
											   vulkan::shared<vk::instance>>&() const noexcept {
	return _surface;
}

