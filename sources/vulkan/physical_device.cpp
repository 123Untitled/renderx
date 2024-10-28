#include "ve/vulkan/physical_device.hpp"

#include "ve/vulkan/device.hpp"
#include "ve/vulkan/surface.hpp"
#include "ve/vk/functions.hpp"
#include "ve/exceptions.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::physical_device::physical_device(void) noexcept
: _pdevice{nullptr} {
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
auto vulkan::physical_device::find_queue_family(const vk::surface& surface,
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
auto vulkan::physical_device::have_surface_formats(void) const -> bool {

	vk::u32 count = 0U;

	// get physical device surface formats count
	vk::try_execute<"failed to get physical device surface formats count">(
			::vk_get_physical_device_surface_formats_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	return count > 0U;
}

/* have present modes */
auto vulkan::physical_device::have_present_modes(void) const -> bool {

	vk::u32 count = 0U;

	vk::try_execute<"failed to get physical device surface present modes">(
			::vk_get_physical_device_surface_present_modes_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	return count > 0U;
}

/* is support surface and queue family */
auto vulkan::physical_device::is_support_surface_and_queue_family(const vk::surface& surface,
																  const vk::u32 family) const -> bool {
	return vk::get_physical_device_surface_support(_pdevice, surface, family);
}

/* extension properties */
auto vulkan::physical_device::extension_properties(void) const -> std::vector<vk::extension_properties> {
	return vk::enumerate_device_extension_properties(_pdevice);
}

/* surface capabilities */
auto vulkan::physical_device::surface_capabilities(void) const -> vk::surface_capabilities {

	vk::surface_capabilities capabilities;

	vk::try_execute<"failed to get physical device surface capabilities">(
			::vk_get_physical_device_surface_capabilities_khr,
			_pdevice, vulkan::surface::shared(), &capabilities);

	return capabilities;
}


/* surface formats */
auto vulkan::physical_device::surface_formats() const -> std::vector<vk::surface_format> {

	vk::u32 count = 0U;

	// get physical device surface formats count
	vk::try_execute<"failed to get physical device surface formats count">(
			::vk_get_physical_device_surface_formats_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	std::vector<vk::surface_format> formats;
	formats.resize(count);

	// get physical device surface formats
	vk::try_execute<"failed to get physical device surface formats">(
			::vk_get_physical_device_surface_formats_khr,
			_pdevice, vulkan::surface::shared(), &count, formats.data());

	return formats;
}

/* surface present modes */
auto vulkan::physical_device::surface_present_modes(void) const -> std::vector<vk::present_mode> {

	vk::u32 count = 0U;

	vk::try_execute<"failed to get physical device surface present modes">(
			::vk_get_physical_device_surface_present_modes_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	std::vector<vk::present_mode> pmodes;
	pmodes.resize(count);

	vk::try_execute<"failed to get physical device surface present modes">(
			::vk_get_physical_device_surface_present_modes_khr,
			_pdevice, vulkan::surface::shared(), &count, pmodes.data());

	return pmodes;
}

/* properties */
auto vulkan::physical_device::properties(void) const -> vk::physical_device_properties {
	return vk::get_physical_device_properties(_pdevice);
}

/* features */
auto vulkan::physical_device::features(void) const -> vk::physical_device_features {
	return vk::get_physical_device_features(_pdevice);
}
