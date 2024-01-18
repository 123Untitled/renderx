#include "vulkan_surface.hpp"


// -- public lifecycle --------------------------------------------------------

/* instance and window constructor */
vulkan::surface::surface(const vulkan::instance& instance, glfw::window& window)
: _surface{nullptr}, _instance{instance.underlying()} {
	// create surface
	if (::glfwCreateWindowSurface(instance.underlying(),
								 &window, nullptr, &_surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};
}

/* move constructor */
vulkan::surface::surface(self&& other) noexcept
: _surface{other._surface}, _instance{other._instance} {
	other.init();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::surface::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	 _surface = other._surface;
	_instance = other._instance;
	other.init();
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::surface::underlying(void) noexcept -> ::VkSurfaceKHR& {
	return _surface;
}

/* const underlying */
auto vulkan::surface::underlying(void) const noexcept -> const ::VkSurfaceKHR& {
	return _surface;
}


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::surface::free(void) noexcept -> void {
	if (_surface == nullptr)
		return;
	::vkDestroySurfaceKHR(_instance, _surface, nullptr);
}

/* init */
auto vulkan::surface::init(void) noexcept -> void {
	_surface = nullptr;
	_instance = nullptr;
}

