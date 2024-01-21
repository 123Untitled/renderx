#include "vulkan_physical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::physical_device::physical_device(void) noexcept
: _device{VK_NULL_HANDLE} {}

/* copy constructor */
vulkan::physical_device::physical_device(const self& other) noexcept
: _device{other._device} {}

/* move constructor */
vulkan::physical_device::physical_device(self&& other) noexcept
: self{other._device} /* copy */ {}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::physical_device::operator=(const self& other) noexcept -> self& {
	_device = other._device;
	return *this;
}

/* move assignment operator */
auto vulkan::physical_device::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}



// -- public conversion operators ---------------------------------------------

/* VkPhysicalDevice conversion operator */
vulkan::physical_device::operator const ::VkPhysicalDevice&() const noexcept {
	return _device;
}


// -- public accessors --------------------------------------------------------

/* supports swapchain */
auto vulkan::physical_device::supports_swapchain(void) const noexcept -> bool {
	auto extensions = vk::enumerate_device_extension_properties(_device);

	for (const auto& extension : extensions) {
		if (vk::supports_swapchain(extension))
			return true;
	}
	return false;
}

/* have surface formats */
auto vulkan::physical_device::have_surface_formats(const vulkan::surface& surface) const -> bool {
	return bool{vk::get_physical_device_surface_formats_count(_device, surface) > 0};
}

/* have present modes */
auto vulkan::physical_device::have_present_modes(const vulkan::surface& surface) const -> bool {
	return bool{vk::get_physical_device_surface_present_modes_count(_device, surface) > 0};
}

/* is support surface and queue family */
auto vulkan::physical_device::is_support_surface_and_queue_family(const vulkan::surface& surface,
																  const vk::u32 family) const -> bool {
	return vk::get_physical_device_surface_support(*this, surface, family);
}

/* extension properties */
auto vulkan::physical_device::extension_properties(void) const -> vk::vector<vk::extension_properties> {
	return vk::enumerate_device_extension_properties(_device);
}

/* surface capabilities */
auto vulkan::physical_device::surface_capabilities(const vulkan::surface& surface) const -> vk::surface_capabilities {
	return vk::get_physical_device_surface_capabilities(_device, surface);
}

/* surface formats */
auto vulkan::physical_device::surface_formats(const vulkan::surface& surface) const -> vk::vector<vk::surface_format> {
	return vk::get_physical_device_surface_formats(_device, surface);
}

/* surface present modes */
auto vulkan::physical_device::surface_present_modes(const vulkan::surface& surface) const -> vk::vector<vk::present_mode> {
	return vk::get_physical_device_surface_present_modes(_device, surface);
}

/* properties */
auto vulkan::physical_device::properties(void) const -> vk::physical_device_properties {
	return vk::get_physical_device_properties(_device);
}

/* features */
auto vulkan::physical_device::features(void) const -> vk::physical_device_features {
	return vk::get_physical_device_features(_device);
}



// -- private lifecycle -------------------------------------------------------

/* VkPhysicalDevice constructor */
vulkan::physical_device::physical_device(const vk::physical_device& device) noexcept
: _device{device} {}


