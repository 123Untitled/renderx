#include "vulkan_logical_device.hpp"
#include "vulkan_queue.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::logical_device::logical_device(void) noexcept
: _device{}, _priority{1.0f} {}

/* physical device and surface constructor */
vulkan::logical_device::logical_device(const vulkan::physical_device& pdevice,
									   const vulkan::surface& surface)
: _device{}, _priority{1.0f} {

	// get queue family index
	const auto index = vulkan::queue_families::find(pdevice, surface);

	// create device queue info
	const auto queue_info = vulkan::queue::create_queue_info(index, _priority);

	// get physical device features
	const auto features = pdevice.features();

	// setup extensions
	constexpr xns::array extensions = {
		// swapchain extension
		(const char*)VK_KHR_SWAPCHAIN_EXTENSION_NAME
		#if defined(ENGINE_OS_MACOS)
		// portability subset extension
		,(const char*)"VK_KHR_portability_subset" // VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME not defined ???
		#endif
	};

	// create device
	_device = vk::make_shared(pdevice, vk::device_info{
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext                   = nullptr,
		.flags                   = 0,
		.queueCreateInfoCount    = 1,
		.pQueueCreateInfos       = &queue_info,
		.enabledLayerCount       = 0,
		.ppEnabledLayerNames     = nullptr,
		.enabledExtensionCount   = static_cast<vk::u32>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
		.pEnabledFeatures        = &features
	});

}

/* copy constructor */
vulkan::logical_device::logical_device(const self& other) noexcept
: _device{other._device}, _priority{other._priority} {}

/* move constructor */
vulkan::logical_device::logical_device(self&& other) noexcept
: _device{xns::move(other._device)}, _priority{other._priority} {
	other._priority = 1.0f;
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::logical_device::operator=(const self& other) noexcept -> self& {
	_device = other._device;
	_priority = other._priority;
	return *this;
}

/* move assignment operator */
auto vulkan::logical_device::operator=(self&& other) noexcept -> self& {
	_device = xns::move(other._device);
	_priority = other._priority;
	other._priority = 1.0f;
	return *this;
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


