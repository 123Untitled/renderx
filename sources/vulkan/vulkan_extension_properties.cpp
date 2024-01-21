#include "vulkan_extension_properties.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::extension_properties::extension_properties(void) noexcept
: _properties{} {}

/* copy constructor */
vulkan::extension_properties::extension_properties(const self& other) noexcept
: _properties{other._properties} {}

/* move constructor */
vulkan::extension_properties::extension_properties(self&& other) noexcept
: self{other} /* copy */ {}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::extension_properties::operator=(const self& other) noexcept -> self& {
	_properties = other._properties;
	return *this;
}

/* move assignment operator */
auto vulkan::extension_properties::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public accessors --------------------------------------------------------

/* name */
auto vulkan::extension_properties::name(void) const noexcept -> xns::string_view {
	return xns::string_view{_properties.extensionName};
}

/* version */
auto vulkan::extension_properties::version(void) const noexcept -> xns::u32 {
	return _properties.specVersion;
}

/* support swapchain */
auto vulkan::extension_properties::supports_swapchain(void) const noexcept -> bool {
	return xns::string_view{_properties.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME;
}


// -- public static methods ---------------------------------------------------

/* get all extension properties */
auto vulkan::extension_properties::extensions(const vulkan::physical_device& device)
		-> xns::vector<self> {

	::uint32_t count = 0;

	if (::vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr)
		!= VK_SUCCESS)
		throw engine::exception{"failed to get physical device extension count"};

	if (count == 0) return {};

	xns::vector<self> extensions;
	extensions.resize(count);

	auto data = reinterpret_cast<::VkExtensionProperties*>(extensions.data());

	if (::vkEnumerateDeviceExtensionProperties(device, nullptr, &count, data) != VK_SUCCESS)
		throw engine::exception{"failed to enumerate physical device extensions"};

	return extensions;
}
