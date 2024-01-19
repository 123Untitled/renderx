#include "vulkan_logical_device.hpp"
#include "vulkan_queue.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::logical_device::logical_device(void) noexcept
: _device{nullptr}, _priority{1.0f} {}

/* physical device and surface constructor */
vulkan::logical_device::logical_device(const vulkan::physical_device& pdevice,
									   const vulkan::surface& surface)
: _device{nullptr}, _priority{1.0f} {

	// get queue family index
	auto index = vulkan::queue_families::find(pdevice, surface);

	// create device queue info
	auto queue_info = vulkan::queue::create_queue_info(index, _priority);

	::VkPhysicalDeviceFeatures features{}; /* not implemented */
	std::memset(&features, 0, sizeof(features));

	// create device info
	auto device_info = self::create_device_info(queue_info, features);
	// create device
	_device = self::create_device(pdevice, device_info);
}

/* move constructor */
vulkan::logical_device::logical_device(self&& other) noexcept
: _device{other._device}, _priority{other._priority} {
	other.init();
}

/* destructor */
vulkan::logical_device::~logical_device(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::logical_device::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	  _device = other._device;
	_priority = other._priority;
	other.init();
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::logical_device::underlying(void) noexcept -> ::VkDevice& {
	return _device;
}

/* const underlying */
auto vulkan::logical_device::underlying(void) const noexcept -> const ::VkDevice& {
	return _device;
}


// -- private static methods --------------------------------------------------

/* create device */
auto vulkan::logical_device::create_device(const vulkan::physical_device& pdevice,
										   const ::VkDeviceCreateInfo& info) -> ::VkDevice {

	::VkDevice device{nullptr};

	if (auto result = ::vkCreateDevice(pdevice.underlying(), &info, nullptr, &device);
		result != VK_SUCCESS)
		throw engine::exception{"failed to create logical device"};

	return device;
}

/* create device info */
auto vulkan::logical_device::create_device_info(::VkDeviceQueueCreateInfo& queue_info,
												::VkPhysicalDeviceFeatures& features) noexcept -> ::VkDeviceCreateInfo {
	static constexpr const char* extensions[] = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	return ::VkDeviceCreateInfo{
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext                   = nullptr,
		.flags                   = 0,
		.queueCreateInfoCount    = 1,
		.pQueueCreateInfos       = &queue_info,
		.enabledLayerCount       = 0,
		.ppEnabledLayerNames     = nullptr,
		.enabledExtensionCount   = 1,
		.ppEnabledExtensionNames = extensions,
		.pEnabledFeatures        = &features
	};
}


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::logical_device::free(void) noexcept -> void {
	if (_device == nullptr)
		return;
	::vkDestroyDevice(_device, nullptr);
}

/* init */
auto vulkan::logical_device::init(void) noexcept -> void {
	  _device = nullptr;
	_priority = 1.0f;
}

