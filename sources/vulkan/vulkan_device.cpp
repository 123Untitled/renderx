#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_queue.hpp"
#include "vulkan/global/instance.hpp"

#include "os.hpp"

// -- public lifecycle --------------------------------------------------------

/* physical device and surface constructor */
vulkan::device::device(const vulkan::surface& surface)
: _ldevice{}, _pdevice{}, _family{0}, _priority{1.0f} {

	// pick physical device
	_pdevice = vulkan::instance::pick_physical_device(surface);

	// get queue family index
	_family = _pdevice.find_queue_family(surface, VK_QUEUE_GRAPHICS_BIT);

	// create device queue info
	const auto queue_info = vulkan::queue::create_queue_info(_family, _priority);

	// get physical device features
	const auto features = _pdevice.features();

	// setup extensions
	constexpr const char* extensions[] = {
		// swapchain extension
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
		#if defined(ENGINE_OS_MACOS)
		// portability subset extension
		,"VK_KHR_portability_subset"
		#endif
	};
	// VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME (not defined)

	// create device
	_ldevice = vk::make_shared(_pdevice, vk::device_info{
		// structure type
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		// next structure
		.pNext                   = nullptr,
		// flags
		.flags                   = 0,
		// number of queue create infos
		.queueCreateInfoCount    = 1,
		// queue create infos
		.pQueueCreateInfos       = &queue_info,
		// number of enabled layers
		.enabledLayerCount       = 0,
		// enabled layers
		.ppEnabledLayerNames     = nullptr,
		// number of enabled extensions
		.enabledExtensionCount   = static_cast<vk::u32>(sizeof(extensions) / sizeof(extensions[0])),
		//
		.ppEnabledExtensionNames = extensions,
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


// -- public methods ----------------------------------------------------------

/* wait idle */
auto vulkan::device::wait_idle(void) const -> void {
	vk::device_wait_idle(_ldevice);
}
