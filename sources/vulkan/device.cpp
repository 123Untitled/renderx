#include "ve/vulkan/device.hpp"
#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/queue.hpp"
#include "ve/vulkan/instance.hpp"
#include "ve/vulkan/validation_layers.hpp"

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
: _ldevice{nullptr},
  _pdevice{nullptr},
  _family{0U}, _priority{1.0f} {

	// get surface
	auto& surface = vulkan::surface::shared();

	// pick physical device
	_pdevice = ___self::_pick_physical_device(surface);

	// get queue family index
	_family  = _pdevice.find_queue_family(surface, VK_QUEUE_GRAPHICS_BIT);

	// create device queue info
	const auto queue_info = vulkan::queue::info(_family, _priority);

	// get physical device features
	const auto features = _pdevice.features();

	// setup extensions
	constexpr vk::array extensions {
		"VK_KHR_swapchain",
		//"VK_KHR_index_type_uint8",
		#if defined(ENGINE_OS_MACOS)
		"VK_KHR_portability_subset",
		#endif

		//"VK_EXT_mesh_shader",
	};

	// get validation layers
	#if defined(ENGINE_VL_DEBUG)
	constexpr auto layers = vulkan::validation_layers::layers();
	#endif


	//VkPhysicalDeviceIndexTypeUint8FeaturesEXT index_type_uint8_features {
	//	.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT,
	//	.pNext = nullptr,
	//	.indexTypeUint8 = VK_TRUE
	//};

	// device info
	const vk::device_info info {
		// structure type
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		// next structure
		.pNext                   = nullptr,
		// flags
		.flags                   = 0U,
		// number of queue create infos
		.queueCreateInfoCount    = 1U,
		// queue create infos
		.pQueueCreateInfos       = &queue_info,
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
			::vk_create_device, _pdevice, &info, nullptr, &_ldevice);
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
auto vulkan::device::physical(void) -> const vulkan::physical_device& {
	return ___self::_shared()._pdevice;
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


// -- private static methods --------------------------------------------------

#include <iostream>

/* pick physical device */
auto vulkan::device::_pick_physical_device(const vk::surface& surface) -> vulkan::physical_device {

	// get physical devices
	const auto& pdevices = vulkan::instance::physical_devices();

	enum : unsigned {
		_ppd_swapchain = 0b0001,
		_ppd_surface   = 0b0010,
		_ppd_present   = 0b0100,
		_ppd_gpu       = 0b1000
	};
	enum : unsigned {
		_ppd_swapchain_shift = 0,
		_ppd_surface_shift   = 1,
		_ppd_present_shift   = 2,
		_ppd_gpu_shift       = 3
	};

	unsigned ppd = 0U;

	// loop over devices
	for (const auto& pdevice : pdevices) {

		auto capabilities = pdevice.surface_capabilities();
		auto properties   = pdevice.properties();
		auto features     = pdevice.features();

		// check if physical device supports tesselation shaders
		if (features.tessellationShader == true)
			ve::hint::success("tesselation shader supported");

		// check if physical device supports swapchain
		ppd |= (static_cast<unsigned>(pdevice.supports_swapchain()) << _ppd_swapchain_shift);

		// check if physical device has surface formats
		ppd |= (static_cast<unsigned>(pdevice.have_surface_formats()) << _ppd_surface_shift);

		// check if physical device has present modes
		ppd |= (static_cast<unsigned>(pdevice.have_present_modes()) << _ppd_present_shift);

		// check if physical device is a gpu
		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		 || properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
			ppd |= (1U << _ppd_gpu_shift);

		// check if physical device is suitable
		if (ppd == 0b1111)
			return pdevice;
	}

	// no suitable physical device found
	throw std::runtime_error{"failed to find suitable physical device"};
}
// &&  features.geometryShader == true) {
