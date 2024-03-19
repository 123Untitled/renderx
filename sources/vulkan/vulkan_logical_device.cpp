#include "vulkan_logical_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_queue.hpp"
#include "vulkan/global/instance.hpp"

#include "os.hpp"

// -- public lifecycle --------------------------------------------------------

/* physical device and surface constructor */
vulkan::logical_device::logical_device(const vulkan::surface& surface)
: _device{}, _priority{1.0f} {


	auto pdevice = vulkan::instance::pick_physical_device(surface);

	// get queue family index
	const auto index = vulkan::queue_families::find(pdevice, surface);

	// create device queue info
	const auto queue_info = vulkan::queue::create_queue_info(index, _priority);

	// get physical device features
	const auto features = pdevice.features();

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
	_device = vk::make_shared(pdevice, vk::device_info{
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
vulkan::logical_device::operator const vk::device&(void) const noexcept {
	return _device;
}

/* vk::shared<vk::device> conversion operator */
vulkan::logical_device::operator const vk::shared<vk::device>&(void) const noexcept {
	return _device;
}


// -- public methods ----------------------------------------------------------

/* wait idle */
auto vulkan::logical_device::wait_idle(void) const -> void {
	vk::device_wait_idle(_device);
}
