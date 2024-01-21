#include "vulkan_physical_device.hpp"
#include "vulkan_extension_properties.hpp"


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
	auto extensions = vulkan::extension_properties::extensions(*this);

	for (const auto& extension : extensions)
		if (extension.supports_swapchain())
			return true;
	return false;
}

/* have formats */
auto vulkan::physical_device::have_formats(const vulkan::surface& surface) const -> bool {
	::uint32_t count = 0;

	if (::vkGetPhysicalDeviceSurfaceFormatsKHR(_device, surface, &count, nullptr) != VK_SUCCESS)
		throw engine::exception{"failed to query number of surface formats"};

	return bool{count > 0};
}

/* have present modes */
auto vulkan::physical_device::have_present_modes(const vulkan::surface& surface) const -> bool {
	::uint32_t count = 0;

	if (::vkGetPhysicalDeviceSurfacePresentModesKHR(_device, surface, &count, nullptr) != VK_SUCCESS)
		throw engine::exception{"failed to query number of present modes"};

	return bool{count > 0};
}


/* is support surface and queue family */
auto vulkan::physical_device::is_support(const vulkan::surface& surface,
											 ::uint32_t family) const -> bool {

	::VkBool32 present = false;
	if (::vkGetPhysicalDeviceSurfaceSupportKHR(_device, family,
												surface,
												&present) != VK_SUCCESS)
		throw engine::exception{"failed to get physical device surface support"};
	return present == VK_TRUE;
}



/* extensions */
auto vulkan::physical_device::extensions(void) const -> xns::vector<vulkan::extension_properties> {
	return vulkan::extension_properties::extensions(*this);
}

/* capabilities */
auto vulkan::physical_device::capabilities(const vulkan::surface& surface) const -> vulkan::surface_capabilities {
	return vulkan::surface_capabilities{*this, surface};
}

/* formats */
auto vulkan::physical_device::formats(const vulkan::surface& surface) const -> xns::vector<::VkSurfaceFormatKHR> {

	::uint32_t count = 0;

	if (::vkGetPhysicalDeviceSurfaceFormatsKHR(_device, surface, &count, nullptr) != VK_SUCCESS)
		throw engine::exception{"failed to query number of surface formats"};

	if (count == 0)
		throw engine::exception{"no surface formats available"};

	xns::vector<::VkSurfaceFormatKHR> formats;
	formats.resize(count);

	if (::vkGetPhysicalDeviceSurfaceFormatsKHR(_device, surface, &count, formats.data()) != VK_SUCCESS)
		throw engine::exception{"failed to query surface formats"};

	return formats;
}

/* present modes */
auto vulkan::physical_device::present_modes(const vulkan::surface& surface) const -> xns::vector<::VkPresentModeKHR> {

	::uint32_t count = 0;

	if (::vkGetPhysicalDeviceSurfacePresentModesKHR(_device, surface, &count, nullptr) != VK_SUCCESS)
		throw engine::exception{"failed to query number of present modes"};

	if (count == 0)
		throw engine::exception{"no present modes available"};

	xns::vector<::VkPresentModeKHR> modes;
	modes.resize(count);

	if (::vkGetPhysicalDeviceSurfacePresentModesKHR(_device, surface, &count, modes.data()) != VK_SUCCESS)
		throw engine::exception{"failed to query present modes"};

	return modes;
}

/* properties */
auto vulkan::physical_device::properties(void) const -> ::VkPhysicalDeviceProperties {
	::VkPhysicalDeviceProperties properties{};
	::vkGetPhysicalDeviceProperties(_device, &properties);
	return properties;
}

/* features */
auto vulkan::physical_device::features(void) const -> ::VkPhysicalDeviceFeatures {
	::VkPhysicalDeviceFeatures features{};
	::vkGetPhysicalDeviceFeatures(_device, &features);
	return features;
}



// -- private lifecycle -------------------------------------------------------

/* VkPhysicalDevice constructor */
vulkan::physical_device::physical_device(const ::VkPhysicalDevice& device) noexcept
: _device{device} {}



// -- private static methods --------------------------------------------------


/* device type */
auto vulkan::physical_device::type(const ::VkPhysicalDeviceProperties& properties) noexcept -> void {
	// switch over device type
	switch (properties.deviceType) {
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			std::cout << "device type: discrete gpu" << std::endl;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			std::cout << "device type: integrated gpu" << std::endl;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			std::cout << "device type: virtual gpu" << std::endl;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			std::cout << "device type: cpu" << std::endl;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			std::cout << "device type: other" << std::endl;
			break;
		default:
			std::cout << "device type: unknown" << std::endl;
			break;
	}
}

/* device features */
auto vulkan::physical_device::features(const ::VkPhysicalDeviceFeatures& features) noexcept -> void {
	// switch over device features

	std::cout << "                     robustBufferAccess: " << features.robustBufferAccess << std::endl;
	std::cout << "                    fullDrawIndexUint32: " << features.fullDrawIndexUint32 << std::endl;
	std::cout << "                         imageCubeArray: " << features.imageCubeArray << std::endl;
	std::cout << "                       independentBlend: " << features.independentBlend << std::endl;
	std::cout << "                         geometryShader: " << features.geometryShader << std::endl;
	std::cout << "                     tessellationShader: " << features.tessellationShader << std::endl;
	std::cout << "                      sampleRateShading: " << features.sampleRateShading << std::endl;
	std::cout << "                           dualSrcBlend: " << features.dualSrcBlend << std::endl;
	std::cout << "                                logicOp: " << features.logicOp << std::endl;
	std::cout << "                      multiDrawIndirect: " << features.multiDrawIndirect << std::endl;
	std::cout << "              drawIndirectFirstInstance: " << features.drawIndirectFirstInstance << std::endl;
	std::cout << "                             depthClamp: " << features.depthClamp << std::endl;
	std::cout << "                         depthBiasClamp: " << features.depthBiasClamp << std::endl;
	std::cout << "                       fillModeNonSolid: " << features.fillModeNonSolid << std::endl;
	std::cout << "                            depthBounds: " << features.depthBounds << std::endl;
	std::cout << "                              wideLines: " << features.wideLines << std::endl;
	std::cout << "                            largePoints: " << features.largePoints << std::endl;
	std::cout << "                             alphaToOne: " << features.alphaToOne << std::endl;
	std::cout << "                          multiViewport: " << features.multiViewport << std::endl;
	std::cout << "                      samplerAnisotropy: " << features.samplerAnisotropy << std::endl;
	std::cout << "                 textureCompressionETC2: " << features.textureCompressionETC2 << std::endl;
	std::cout << "             textureCompressionASTC_LDR: " << features.textureCompressionASTC_LDR << std::endl;
	std::cout << "                   textureCompressionBC: " << features.textureCompressionBC << std::endl;
	std::cout << "                  occlusionQueryPrecise: " << features.occlusionQueryPrecise << std::endl;
	std::cout << "                pipelineStatisticsQuery: " << features.pipelineStatisticsQuery << std::endl;
	std::cout << "         vertexPipelineStoresAndAtomics: " << features.vertexPipelineStoresAndAtomics << std::endl;
	std::cout << "               fragmentStoresAndAtomics: " << features.fragmentStoresAndAtomics << std::endl;
	std::cout << " shaderTessellationAndGeometryPointSize: " << features.shaderTessellationAndGeometryPointSize << std::endl;
	std::cout << "              shaderImageGatherExtended: " << features.shaderImageGatherExtended << std::endl;
	std::cout << "      shaderStorageImageExtendedFormats: " << features.shaderStorageImageExtendedFormats << std::endl;
	std::cout << "          shaderStorageImageMultisample: " << features.shaderStorageImageMultisample << std::endl;
	std::cout << "    shaderStorageImageReadWithoutFormat: " << features.shaderStorageImageReadWithoutFormat << std::endl;
	std::cout << "   shaderStorageImageWriteWithoutFormat: " << features.shaderStorageImageWriteWithoutFormat << std::endl;
	std::cout << "shaderUniformBufferArrayDynamicIndexing: " << features.shaderUniformBufferArrayDynamicIndexing << std::endl;
	std::cout << " shaderSampledImageArrayDynamicIndexing: " << features.shaderSampledImageArrayDynamicIndexing << std::endl;
	std::cout << "shaderStorageBufferArrayDynamicIndexing: " << features.shaderStorageBufferArrayDynamicIndexing << std::endl;
	std::cout << " shaderStorageImageArrayDynamicIndexing: " << features.shaderStorageImageArrayDynamicIndexing << std::endl;
	std::cout << "                     shaderClipDistance: " << features.shaderClipDistance << std::endl;
	std::cout << "                     shaderCullDistance: " << features.shaderCullDistance << std::endl;
	std::cout << "                          shaderFloat64: " << features.shaderFloat64 << std::endl;
	std::cout << "                            shaderInt64: " << features.shaderInt64 << std::endl;
	std::cout << "                            shaderInt16: " << features.shaderInt16 << std::endl;
	std::cout << "                shaderResourceResidency: " << features.shaderResourceResidency << std::endl;
	std::cout << "                   shaderResourceMinLod: " << features.shaderResourceMinLod << std::endl;
	std::cout << "                          sparseBinding: " << features.sparseBinding << std::endl;
	std::cout << "                  sparseResidencyBuffer: " << features.sparseResidencyBuffer << std::endl;
	std::cout << "                 sparseResidencyImage2D: " << features.sparseResidencyImage2D << std::endl;
	std::cout << "                 sparseResidencyImage3D: " << features.sparseResidencyImage3D << std::endl;
	std::cout << "                sparseResidency2Samples: " << features.sparseResidency2Samples << std::endl;
	std::cout << "                sparseResidency4Samples: " << features.sparseResidency4Samples << std::endl;
	std::cout << "                sparseResidency8Samples: " << features.sparseResidency8Samples << std::endl;
	std::cout << "               sparseResidency16Samples: " << features.sparseResidency16Samples << std::endl;
	std::cout << "                 sparseResidencyAliased: " << features.sparseResidencyAliased << std::endl;
	std::cout << "                variableMultisampleRate: " << features.variableMultisampleRate << std::endl;
	std::cout << "                       inheritedQueries: " << features.inheritedQueries << std::endl;

}
