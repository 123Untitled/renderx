#include "renderx/vulkan/instance.hpp"
#include "renderx/system/write.hpp"

#include "renderx/glfw/system.hpp"

#include "renderx/vulkan/validation_layers.hpp"
#include "renderx/os.hpp"


// -- private static methods --------------------------------------------------

/* shared */
auto vulkan::instance::_shared(void) -> ___self& {
	static ___self ___ins{};
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::instance::instance(void)
/* uninitialized instance / messenger */ {

	// create application info
	constexpr vk::application_info app_info{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = nullptr,
		.pApplicationName   = "application",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName        = "renderx",
		.engineVersion      = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion         = VK_API_VERSION_1_0
	};

	// get required extensions (from GLFW)
	auto extensions = glfw::system::vulkan_required_extensions();

	#if defined(ENGINE_VL_DEBUG)

	// get debug info
	constexpr auto messenger_info = ___self::_messenger_info();

	// get validation layers
	constexpr auto layers = vulkan::validation_layers::layers();

	#endif // ENGINE_VL_DEBUG

	// create info
	const vk::instance_info info {

		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

		#if defined(ENGINE_VL_DEBUG)
		.pNext                   = &messenger_info,
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

	// create instance
	vk::try_execute<"failed to create instance">(
			::vk_create_instance, &info, nullptr, &_instance);


	// warning: need exception guard here !!

	// -- messenger -----------------------------------------------------------

	#if defined(ENGINE_VL_DEBUG)
	// get function
	const auto func = reinterpret_cast<vk::pfn_create_debug_utils_messenger>(
			::vk_get_instance_proc_addr(_instance, "vkCreateDebugUtilsMessengerEXT"));

	if (func == nullptr)
		throw vk::exception{"failed to get instance proc address", VK_ERROR_EXTENSION_NOT_PRESENT};

	// create messenger
	vk::try_execute<"failed to create debug utils messenger">(
			func,
			_instance, &messenger_info, nullptr, &_messenger);
	#endif

	//auto p = ___self::extension_properties();
}

/* destructor */
vulkan::instance::~instance(void) noexcept {


	// -- messenger -----------------------------------------------------------

	#if defined(ENGINE_VL_DEBUG)
	// get function
	const auto func = reinterpret_cast<vk::pfn_destroy_debug_utils_messenger>(
			::vk_get_instance_proc_addr(_instance, "vkDestroyDebugUtilsMessengerEXT"));

	// don't throw, we are in destructor
	if (func == nullptr)
		return;

	// release messenger
	func(_instance, _messenger, nullptr);
	#endif


	// -- instance ------------------------------------------------------------

	// release instance
	::vk_destroy_instance(_instance, nullptr);
}



// -- private static methods --------------------------------------------------

/* extension properties */
auto vulkan::instance::extension_properties(void) -> vk::vector<vk::extension_properties> {
	return vk::enumerate_instance_extension_properties();
}


// -- public static methods ---------------------------------------------------

/* shared */
auto vulkan::instance::shared(void) -> const vk::instance& {
	return ___self::_shared()._instance;
}

/* physical devices */
auto vulkan::instance::physical_devices(void) -> const vk::vector<vulkan::physical_device>& {
	static auto __pdevices = vk::enumerate_physical_devices<vulkan::physical_device>(___self::shared());
	return __pdevices;
}



/* callback */
#if defined(ENGINE_VL_DEBUG)
VKAPI_ATTR auto VKAPI_CALL
vulkan::instance::_callback(const vk::debug_utils_message_severity_flag_bit severity,
										 const vk::debug_utils_message_type_flags type,
										 const vk::debug_utils_messenger_callback_data* cdata,
										 void*) -> vk::bool32 {

	switch (severity) {

		// verbose
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			rx::write("\x1b[7;35m verbose: ");
			break;

		// info
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			rx::write("\x1b[7;36m info: ");
			break;

		// warning
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			rx::write("\x1b[7;32m warning: ");
			break;

		// error
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			rx::write("\x1b[7;31m error: ");
			break;

		default:
			break;
	}

	// general
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		rx::write("[general] \x1b[0m\r\n");

	// validation
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		rx::write("[validation] \x1b[0m\r\n");

	// performance
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		rx::write("[performance] \x1b[0m\r\n");


	std::cerr << cdata->pMessage << std::endl << std::endl;

	return VK_FALSE;
}
#endif
