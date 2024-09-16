#include "engine/vulkan/device.hpp"
#include "engine/vulkan/physical_device.hpp"
#include "engine/vulkan/queue.hpp"
#include "engine/vulkan/instance.hpp"
#include "engine/vulkan/validation_layers.hpp"


#include "engine/vk/array.hpp"

#include "engine/os.hpp"

// -- public lifecycle --------------------------------------------------------

/* physical device and surface constructor */
vulkan::device::device(const vulkan::surface& surface)
: _ldevice{}, _pdevice{}, _family{0}, _priority{1.0f} {

	// pick physical device
	_pdevice = self::pick_physical_device(surface);

	// get queue family index
	_family  = _pdevice.find_queue_family(surface, VK_QUEUE_GRAPHICS_BIT);

	float prio = 1.0f;

	// create device queue info
	const auto queue_info = vulkan::queue::info(_family, prio);

	// get physical device features
	const auto features = _pdevice.features();

	// setup extensions
	constexpr vk::array extensions {
		"VK_KHR_swapchain",
		#if defined(ENGINE_OS_MACOS)
		"VK_KHR_portability_subset"
		#endif
	};

	// get validation layers
	#if defined(ENGINE_VL_DEBUG)
	constexpr auto layers = vulkan::validation_layers::layers();
	#endif

	// create device
	_ldevice = vk::make_shared(_pdevice, vk::device_info{
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
	});

}


// -- public conversion operators ---------------------------------------------

/* vk::device conversion operator */
vulkan::device::operator const vk::device&(void) const noexcept {
	return _ldevice;
}

/* vk::shared<vk::device> conversion operator */
vulkan::device::operator const vk::shared<vk::device>&(void) const noexcept {
	return _ldevice;
}


// -- public accessors --------------------------------------------------------

/* physical device */
auto vulkan::device::physical_device(void) const noexcept -> const vulkan::physical_device& {
	return _pdevice;
}

/* queue family */
auto vulkan::device::family(void) const noexcept -> const vk::u32& {
	return _family;
}

/* shared */
auto vulkan::device::shared(void) const noexcept -> const vk::shared<vk::device>& {
	return _ldevice;
}

/* handle */
auto vulkan::device::handle(void) const noexcept -> const vk::device& {
	return _ldevice;
}


// -- public methods ----------------------------------------------------------

/* wait idle */
auto vulkan::device::wait_idle(void) const -> void {
	vk::device_wait_idle(_ldevice);
}


// -- private static methods --------------------------------------------------

/* pick physical device */
auto vulkan::device::pick_physical_device(const vulkan::surface& surface) -> vulkan::physical_device {

	// get physical devices
	const auto& pdevices = vulkan::instance::physical_devices();

	// loop over devices
	for (const auto& pdevice : pdevices) {

		auto capabilities = pdevice.surface_capabilities(surface);
		auto properties   = pdevice.properties();
		auto features     = pdevice.features();

		if (pdevice.supports_swapchain()          == true
		&&  pdevice.have_surface_formats(surface) == true
		&&  pdevice.have_present_modes(surface)   == true
		&& (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		 || properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)) {
		// &&  features.geometryShader == true) {
			return pdevice;
		}
	}
	// no suitable physical device found
	throw vk::exception{"failed to find suitable physical device"};
}
