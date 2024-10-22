#include "ve/exceptions.hpp"
#include "ve/vulkan/surface.hpp"

#include "ve/vulkan/instance.hpp"
#include "ve/vk/exception.hpp"

#include "ve/glfw/window.hpp"

#include "ve/os.hpp"

#if defined(RENDERX_OS_LINUX)
#include "ve/wayland/window.hpp"
#endif // RENDERX_OS_LINUX



// -- private static methods --------------------------------------------------

/* shared */
auto vulkan::surface::_shared(void) -> ___self& {
	static vulkan::surface ___ins{};
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

//#if defined(RENDERX_OS_LINUX)
///* default constructor */
//vulkan::surface::surface(void)
///* uninitialized surface */ {
//
//	// get instance and window
//	auto& instance = vulkan::instance::shared();
//	//auto&   window = wl::window::shared();
//
//	// create info
//	const vk::wayland_surface_create_info_khr info {
//		// structure type
//		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
//		// next structure
//		.pNext = nullptr,
//		// flags
//		.flags = 0U,
//		// wayland display
//		.display = &(wl::window::display().get()),
//		// wayland surface (window)
//		.surface = &(wl::window::surface().get())
//	};
//
//	// create surface
//    const vk::result state = ::vk_create_wayland_surface_khr(
//									instance,
//									&info,
//									nullptr,
//									&_surface);
//
//	// check state
//	if (state != VK_SUCCESS)
//		throw vk::exception{"failed to create wayland surface khr", state};
//}
//
//#else

/* default constructor */
vulkan::surface::surface(void)
/* uninitialized surface */ {

	auto& instance = vulkan::instance::shared();
	auto&   window = glfw::window::shared();

	// create surface
	if (::glfw_create_window_surface(instance, &window, nullptr, &_surface) != VK_SUCCESS)
		throw engine::exception{"failed to create vulkan surface."};

}
//#endif // RENDERX_OS_LINUX

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
