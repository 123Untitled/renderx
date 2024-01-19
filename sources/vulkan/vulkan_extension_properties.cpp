#include "vulkan_extension_properties.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::extension_properties::extension_properties(void) noexcept
: _name{}, _version{0} {}

/* move constructor */
vulkan::extension_properties::extension_properties(self&& other) noexcept
: _name{xns::move(other._name)}, _version{other._version} {}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::extension_properties::operator=(self&& other) noexcept -> self& {
	_name = xns::move(other._name);
	_version = other._version;
	return *this;
}


// -- public accessors --------------------------------------------------------

/* name */
auto vulkan::extension_properties::name(void) const noexcept -> const xns::string& {
	return _name;
}

/* version */
auto vulkan::extension_properties::version(void) const noexcept -> xns::u32 {
	return _version;
}


// -- public static methods ---------------------------------------------------

/* get all extension properties */
auto vulkan::extension_properties::get(const vulkan::physical_device& device)
		-> xns::vector<self> {

	::uint32_t count = 0;

	if (::vkEnumerateDeviceExtensionProperties(device.underlying(),
												nullptr,
												&count,
												nullptr) != VK_SUCCESS)
		throw engine::exception{"failed to get physical device extension count"};

	if (count == 0) return {};

	xns::vector<::VkExtensionProperties> extensions;
	extensions.resize(count);

	if (::vkEnumerateDeviceExtensionProperties(device.underlying(), nullptr, &count, extensions.data()) != VK_SUCCESS)
		throw engine::exception{"failed to enumerate physical device extensions"};

	xns::vector<self> result;
	result.reserve(count);

	for (const auto& ext : extensions) {
		result.emplace_back();
		result.back()._name    = xns::string{ext.extensionName};
		result.back()._version = ext.specVersion;
	}

	return result;
}
