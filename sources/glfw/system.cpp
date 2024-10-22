#include "ve/glfw/system.hpp"
#include "ve/exceptions.hpp"
#include "ve/os.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/glfw/typedefs.hpp"

#include <vulkan/vulkan.h>
#include "ve/glfw/glfw.hpp"

#include <iostream>


// -- private static methods --------------------------------------------------

/* shared */
auto glfw::system::_shared(void) noexcept -> ___self& {
	static ___self ___ins;
	return ___ins;
}

/* error callback */
void glfw::system::_error_callback(int error_code, const char* description) noexcept {
	std::cerr << "error: glfw error " << error_code << ": " << description << std::endl;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
glfw::system::system(void)
: _init{} {

	// check vulkan support
	if (::glfw_vulkan_supported() == GLFW_FALSE)
		throw engine::exception{"glfw: vulkan is not supported."};

	// set error callback
	static_cast<void>(::glfw_set_error_callback(___self::_error_callback));
}


// -- private methods ---------------------------------------------------------

/* vulkan required extensions */
auto glfw::system::_vulkan_required_extensions(void) -> std::vector<const char*> {

	vk::u32           count = 0U;
	const char** extensions = ::glfw_get_required_instance_extensions(&count);

	if (extensions == nullptr)
		throw engine::exception{"failed to get glfw required instance extensions."};

	std::vector<const char*> result;
	result.reserve(count);

// check macos system
#if defined(ENGINE_OS_MACOS)
	result.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	result.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif
// validation layers check
#if defined(ENGINE_VL_DEBUG)
	result.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	for (vk::u32 i = 0U; i < count; ++i)
		result.push_back(extensions[i]);

	return result;
}


// -- public static methods ---------------------------------------------------

/* init */
auto glfw::system::init(void) -> void {
	static_cast<void>(___self::_shared());
}

/* vulkan required extensions */
auto glfw::system::vulkan_required_extensions(void) -> std::vector<const char*> {
	return ___self::_shared()._vulkan_required_extensions();
}



