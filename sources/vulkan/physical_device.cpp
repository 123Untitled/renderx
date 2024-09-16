/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "engine/vulkan/physical_device.hpp"

#include "engine/vulkan/surface.hpp"
#include "engine/vk/functions.hpp"
#include "engine/exceptions.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::physical_device::physical_device(void) noexcept
: _pdevice{VK_NULL_HANDLE} {
}

/* vk::physical_device constructor */
vulkan::physical_device::physical_device(const vk::physical_device& pdevice) noexcept
: _pdevice{pdevice} {
}


// -- public conversion operators ---------------------------------------------

/* vk::physical_device conversion operator */
vulkan::physical_device::operator const vk::physical_device&(void) const noexcept {
	return _pdevice;
}


// -- public accessors --------------------------------------------------------

/* find queue family */
auto vulkan::physical_device::find_queue_family(const vulkan::surface& surface,
												const vk::queue_flags_bits flags) const -> vk::u32 {
	// get queue families properties
	static const auto properties = vk::get_physical_device_queue_family_properties(_pdevice);

	for (vk::u32 i = 0U; i < properties.size(); ++i) {
		// check queue flags
		if (properties[i].queueFlags & flags
		&& is_support_surface_and_queue_family(surface, i)) {
			return i;
		}
	}
	throw engine::exception{"failed to find suitable queue family"};
}

/* supports swapchain */
auto vulkan::physical_device::supports_swapchain(void) const noexcept -> bool {
	auto extensions = vk::enumerate_device_extension_properties(_pdevice);

	for (const auto& extension : extensions) {
		if (vk::supports_swapchain(extension))
			return true;
	}
	return false;
}

/* have surface formats */
auto vulkan::physical_device::have_surface_formats(const vulkan::surface& surface) const -> bool {
	return bool{vk::get_physical_device_surface_formats_count(_pdevice, surface) > 0};
}

/* have present modes */
auto vulkan::physical_device::have_present_modes(const vulkan::surface& surface) const -> bool {
	return bool{vk::get_physical_device_surface_present_modes_count(_pdevice, surface) > 0};
}

/* is support surface and queue family */
auto vulkan::physical_device::is_support_surface_and_queue_family(const vulkan::surface& surface,
																  const vk::u32 family) const -> bool {
	return vk::get_physical_device_surface_support(_pdevice, surface, family);
}

/* extension properties */
auto vulkan::physical_device::extension_properties(void) const -> vk::vector<vk::extension_properties> {
	return vk::enumerate_device_extension_properties(_pdevice);
}

/* surface capabilities */
auto vulkan::physical_device::surface_capabilities(const vulkan::surface& surface) const -> vk::surface_capabilities {
	return vk::get_physical_device_surface_capabilities(_pdevice, surface);
}

/* surface formats */
auto vulkan::physical_device::surface_formats(const vulkan::surface& surface) const -> vk::vector<vk::surface_format> {
	return vk::get_physical_device_surface_formats(_pdevice, surface);
}

/* surface present modes */
auto vulkan::physical_device::surface_present_modes(const vulkan::surface& surface) const -> vk::vector<vk::present_mode> {
	return vk::get_physical_device_surface_present_modes(_pdevice, surface);
}

/* properties */
auto vulkan::physical_device::properties(void) const -> vk::physical_device_properties {
	return vk::get_physical_device_properties(_pdevice);
}

/* features */
auto vulkan::physical_device::features(void) const -> vk::physical_device_features {
	return vk::get_physical_device_features(_pdevice);
}
