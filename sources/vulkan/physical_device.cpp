#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/instance.hpp"

#include "ve/vulkan/device.hpp"
#include "ve/vulkan/surface.hpp"
#include "ve/vk/functions.hpp"

#include <iostream>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::physical_device::physical_device(void)
: _pdevice{_self::_pick_physical_device()} {
}

/* physical device constructor */
ve::physical_device::physical_device(const vk::physical_device& pdevice) noexcept
: _pdevice{pdevice} {
}


// -- public conversion operators ---------------------------------------------

/* vk::physical_device conversion operator */
ve::physical_device::operator const vk::physical_device&(void) const noexcept {
	return _pdevice;
}


// -- public accessors --------------------------------------------------------


/* supports swapchain */
auto ve::physical_device::supports_swapchain(void) const noexcept -> bool {
	auto extensions = vk::enumerate_device_extension_properties(_pdevice);

	for (const auto& extension : extensions) {
		if (vk::supports_swapchain(extension))
			return true;
	}
	return false;
}

/* have surface formats */
auto ve::physical_device::have_surface_formats(void) const -> bool {

	vk::u32 count = 0U;

	// get physical device surface formats count
	vk::try_execute<"failed to get physical device surface formats count">(
			::vk_get_physical_device_surface_formats_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	return count > 0U;
}

/* have present modes */
auto ve::physical_device::have_present_modes(void) const -> bool {

	vk::u32 count = 0U;

	vk::try_execute<"failed to get physical device surface present modes">(
			::vk_get_physical_device_surface_present_modes_khr,
			_pdevice, vulkan::surface::shared(), &count, nullptr);

	return count > 0U;
}

/* extension properties */
auto ve::physical_device::extension_properties(void) const -> std::vector<vk::extension_properties> {
	return vk::enumerate_device_extension_properties(_pdevice);
}

/* surface capabilities */
auto ve::physical_device::surface_capabilities(void) const -> vk::surface_capabilities {

	vk::surface_capabilities capabilities;

	vk::try_execute<"failed to get physical device surface capabilities">(
			::vk_get_physical_device_surface_capabilities_khr,
			_pdevice, vulkan::surface::shared(), &capabilities);

	return capabilities;
}


/* surface formats */
auto ve::physical_device::surface_formats() const -> std::vector<vk::surface_format> {

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
auto ve::physical_device::surface_present_modes(void) const -> std::vector<vk::present_mode> {

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
auto ve::physical_device::properties(void) const noexcept -> vk::physical_device_properties {
	vk::physical_device_properties properties;
	::vkGetPhysicalDeviceProperties(_pdevice, &properties);
	return properties;
}

/* features */
auto ve::physical_device::features(void) const -> vk::physical_device_features {
	return vk::get_physical_device_features(_pdevice);
}


/* queue family properties */
auto ve::physical_device::queue_family_properties(void) const -> std::vector<vk::queue_family_properties> {

	vk::u32 count{0U};

	// get queue family properties count
	::vk_get_physical_device_queue_family_properties(
			_pdevice, &count, nullptr);

	// reserve space
	std::vector<vk::queue_family_properties> properties;
	properties.resize(count);

	// get queue family properties
	::vk_get_physical_device_queue_family_properties(
			_pdevice, &count, properties.data());

	// done
	return properties;
}


// -- private static methods --------------------------------------------------

/* pick physical device */
auto ve::physical_device::_pick_physical_device(void) -> vk::physical_device {

	// get surface
	const vk::surface& surface = vulkan::surface::shared();

	// get physical devices
	const auto pdevices = vulkan::instance::physical_devices();

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
	for (const auto& device : pdevices) {

		_self pdevice{device};

		auto capabilities = pdevice.surface_capabilities();
		auto properties   = pdevice.properties();
		auto features     = pdevice.features();

		// check if physical device supports tesselation shaders
		if (features.tessellationShader == true)
			;

		// check if physical device supports swapchain
		ppd |= (static_cast<unsigned>(pdevice.supports_swapchain()) << _ppd_swapchain_shift);

		// check if physical device has surface formats
		ppd |= (static_cast<unsigned>(pdevice.have_surface_formats()) << _ppd_surface_shift);

		// check if physical device has present modes
		ppd |= (static_cast<unsigned>(pdevice.have_present_modes()) << _ppd_present_shift);

		// check if physical device is a gpu
		//if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		// || properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
			ppd |= (1U << _ppd_gpu_shift);

		if (pdevice.supports_swapchain())
			std::cout << "swapchain support" << std::endl;

		if (pdevice.have_surface_formats())
			std::cout << "surface formats" << std::endl;

		if (pdevice.have_present_modes())
			std::cout << "present mode" << std::endl;

		std::cout << "gpu: " << properties.deviceType << std::endl;



		// check if physical device is suitable
		if (ppd == 0b1111)
			return pdevice;
	}

	// no suitable physical device found
	throw std::runtime_error{"failed to find suitable physical device"};
}
// &&  features.geometryShader == true) {
