#include "ve/vulkan/device.hpp"
#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/queue.hpp"
#include "ve/vulkan/instance.hpp"
#include "ve/vulkan/validation_layers.hpp"
#include "ve/vulkan/queue_family_library.hpp"

#include <stdexcept>

#include "ve/hint.hpp"

#include "ve/vk/array.hpp"

#include "ve/os.hpp"



// -- private static methods --------------------------------------------------

/* shared */
auto vulkan::device::_shared(void) -> ___self& {
	static ___self ___ins{};
	return ___ins;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::device::device(void)
: _ldevice{nullptr}, _family{0U}, _priority{1.0f} {

	// get surface
	auto& surface = vulkan::surface::shared();

	// get physical device
	auto& pdevice = ve::physical_device::shared();

	// get queue family index
	//_family = pdevice.find_queue_family(surface, VK_QUEUE_GRAPHICS_BIT);

	// create device queue info
	//const auto queue_info = vulkan::queue::info(_family, _priority);

	const auto queue_info = ve::queue_family_library::info();

	// get physical device features
	const auto features = pdevice.features();

	// setup extensions
	constexpr vk::array extensions {
		"VK_KHR_swapchain",
		//"VK_KHR_index_type_uint8",
		#if defined(ENGINE_OS_MACOS)
		"VK_KHR_portability_subset",
		#endif

		//"VK_KHR_shader_non_semantic_info"
		//"VK_EXT_mesh_shader",
	};

	// get validation layers
	#if defined(ENGINE_VL_DEBUG)
	constexpr auto layers = vulkan::validation_layers::layers();
	#endif

	// create info
	const vk::device_create_info info {
		// structure type
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		// next structure
		.pNext                   = nullptr,
		// flags
		.flags                   = 0U,
		// number of queue create infos
		.queueCreateInfoCount    = queue_info.size(),
		// queue create infos
		.pQueueCreateInfos       = queue_info.data(),
		// number of enabled layers

		#if defined(ENGINE_VL_DEBUG)
		.enabledLayerCount       = layers.size(),
		// enabled layers
		.ppEnabledLayerNames     = layers.data(),

		#else
		// number of enabled layers
		.enabledLayerCount       = 0U,
		// enabled layers
		.ppEnabledLayerNames     = nullptr,
		#endif

		// number of enabled extensions
		.enabledExtensionCount   = extensions.size(),
		// enabled extensions
		.ppEnabledExtensionNames = extensions.data(),
		// enabled features
		.pEnabledFeatures        = &features
	};

	// create logical device
	vk::try_execute<"failed to create device">(
			::vk_create_device, pdevice, &info, nullptr, &_ldevice);
}

/* destructor */
vulkan::device::~device(void) noexcept {

	// release logical device
	::vk_destroy_device(_ldevice, nullptr);
}


// -- public static accessors -------------------------------------------------

/* logical */
auto vulkan::device::logical(void) -> const vk::device& {
	return ___self::_shared()._ldevice;
}

/* physical */
auto vulkan::device::physical(void) -> const ve::physical_device& {
	return ve::physical_device::shared();
}

/* queue family */
auto vulkan::device::family(void) -> const vk::u32& {
	return ___self::_shared()._family;
}


// -- public static methods ---------------------------------------------------

/* wait idle */
auto vulkan::device::wait_idle(void) -> void {

	// wait idle
	vk::try_execute<"failed to wait idle">(
				::vk_device_wait_idle,
				___self::_shared()._ldevice);

	// warning:
	// this function must not be called from a destructor
}
