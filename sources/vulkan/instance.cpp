#include "engine/vulkan/instance.hpp"
#include "engine/vk/destroy.hpp"
#include "engine/vk/create.hpp"
#include "engine/glfw/system.hpp"

#include "engine/vulkan/debug_utils_messenger.hpp"
#include "engine/vulkan/validation_layers.hpp"
#include "engine/os.hpp"



// -- public conversion operators ---------------------------------------------

/* vk::instance conversion operator */
vulkan::instance::operator const vk::instance&(void) const noexcept {
	return _instance;
}


// -- public static methods ---------------------------------------------------

/* shared */
auto vulkan::instance::shared(void) -> ___self& {
	static ___self __self{};
	return __self;
}

/* physical devices */
auto vulkan::instance::physical_devices(void) -> const vk::vector<vulkan::physical_device>& {
	static auto __pdevices = vk::enumerate_physical_devices<vulkan::physical_device>(___self::shared());
	return __pdevices;
}


static auto create_instance(void) -> vk::shared<vk::instance> {

	// create application info
	constexpr vk::application_info app_info{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = nullptr,
		.pApplicationName   = "application",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName        = "engine",
		.engineVersion      = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion         = VK_API_VERSION_1_0
	};

	// get required extensions
	auto extensions = glfw::system::shared().vulkan_required_extensions();

	#if defined(ENGINE_VL_DEBUG)

	// get debug info
	constexpr auto debug_info = vulkan::debug_utils_messenger::debug_info();

	// get validation layers
	constexpr auto layers = vulkan::validation_layers::layers();

	#endif // ENGINE_VL_DEBUG

	// create instance info
	const vk::instance_info create {

		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

		#if defined(ENGINE_VL_DEBUG)
		.pNext                   = &debug_info,
		#else
		.pNext                   = nullptr,
		#endif

		#if defined(ENGINE_OS_MACOS)
		.flags                   = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
		#else
		.flags                   = 0U,
		#endif

		.pApplicationInfo        = &app_info,

		#if defined(ENGINE_VL_DEBUG)
		.enabledLayerCount       = layers.size(),
		.ppEnabledLayerNames     = layers.data(),
		#else
		.enabledLayerCount       = 0U,
		.ppEnabledLayerNames     = nullptr,
		#endif

		.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
	};

	return vk::make_shared(create);
}

// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::instance::instance(void)
: _instance{create_instance()}
#if defined(ENGINE_VL_DEBUG)
	, _messenger{_instance}
#endif
{

	//auto p = ___self::extension_properties();
}


// -- private static methods --------------------------------------------------

/* extension properties */
auto vulkan::instance::extension_properties(void) -> vk::vector<vk::extension_properties> {
	return vk::enumerate_instance_extension_properties();
}
