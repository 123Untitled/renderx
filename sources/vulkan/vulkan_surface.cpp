#include "vulkan/vulkan_surface.hpp"
#include "vulkan/global/instance.hpp"

#include "vulkan/vk_destroy.hpp"
#include "glfw_window.hpp"

#include <GLFW/glfw3.h>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void) noexcept
: _surface{VK_NULL_HANDLE} {
}

/* window constructor */
vulkan::surface::surface(glfw::window& window)
: _surface{VK_NULL_HANDLE} {

	auto& instance = vulkan::instance::shared();

	// create surface
	if (::glfwCreateWindowSurface(instance,
								 window.underlying(), nullptr, &_surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};
}

/* move constructor */
vulkan::surface::surface(self&& other) noexcept
: _surface{other._surface} {
	other._surface = VK_NULL_HANDLE;
}

/* destructor */
vulkan::surface::~surface(void) noexcept {
	if (_surface == VK_NULL_HANDLE)
		return;
	vk::destroy(_surface, vulkan::instance::shared());
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::surface::operator=(self&& other) noexcept -> self& {

	// check for self-assignment
	if (this == &other)
		return *this;

	// destroy surface
	if (_surface != VK_NULL_HANDLE)
		vk::destroy(_surface, vulkan::instance::shared());

	// move from other
		  _surface = other._surface;
	other._surface = VK_NULL_HANDLE;

	return *this;
}


// -- public conversion operators ---------------------------------------------

/* vk::surface conversion operator */
vulkan::surface::operator const vk::surface&(void) const noexcept {
	return _surface;
}
