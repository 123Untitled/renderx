#include "renderx/vulkan/surface.hpp"

#include "renderx/vulkan/instance.hpp"
#include "renderx/exceptions.hpp"

#include "renderx/glfw/window.hpp"


// -- private static methods --------------------------------------------------

/* shared */
auto vulkan::surface::_shared(void) -> ___self& {
	static vulkan::surface ___ins{};
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::surface::surface(void)
/* uninitialized surface */ {

	auto& instance = vulkan::instance::shared();
	auto&   window = glfw::window::shared();

	// create surface
	if (::glfw_create_window_surface(instance, &window, nullptr, &_surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};

}

/* destructor */
vulkan::surface::~surface(void) noexcept {

	// free surface
	::vk_destroy_surface_khr(vulkan::instance::shared(), _surface, nullptr);
}


// -- public static accessors -------------------------------------------------

/* shared */
auto vulkan::surface::shared(void) -> vk::surface& {
	return ___self::_shared()._surface;
}
