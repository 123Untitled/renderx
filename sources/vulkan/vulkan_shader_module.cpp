#include "vulkan_shader_module.hpp"
#include "vulkan_logical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* path constructor */
vulkan::shader_module::shader_module(const vulkan::logical_device& device,
									 const std::string& path)
: _module{VK_NULL_HANDLE} {


	std::ifstream file{path, std::ios::ate | std::ios::binary};
	if (!file.is_open()) {
		std::cerr << "failed to open shader file: " << path << std::endl;
		return;
	}

	std::vector<char> buffer;
	std::size_t size = static_cast<std::size_t>(file.tellg());
	buffer.resize(size);
	file.seekg(0);
	file.read(buffer.data(), static_cast<std::streamsize>(size));
	file.close();


	// create shader module info
	auto info = self::create_shader_module_info(buffer);
	// create shader module
	auto result = self::create_shader_module(device, info, _module);

	if (result != VK_SUCCESS) {
		std::cerr << "failed to create shader module: " << result << std::endl;
		return;
	}

}


// -- public conversion operators ---------------------------------------------

/* VkShaderModule conversion operator */
vulkan::shader_module::operator ::VkShaderModule(void) noexcept {
	return _module;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::shader_module::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_module == VK_NULL_HANDLE)
		return;
	::vkDestroyShaderModule(device, _module, nullptr);
	_module = VK_NULL_HANDLE;
}


// -- private static methods --------------------------------------------------

/* create shader module */
auto vulkan::shader_module::create_shader_module(const vulkan::logical_device& device,
												 const ::VkShaderModuleCreateInfo& info,
												 ::VkShaderModule& module) noexcept -> ::VkResult {
	return ::vkCreateShaderModule(device, &info, nullptr, &module);
}

/* create shader module info */
auto vulkan::shader_module::create_shader_module_info(const std::vector<char>& code) noexcept -> ::VkShaderModuleCreateInfo {
	return ::VkShaderModuleCreateInfo{
		.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext    = nullptr,
		.flags    = 0,
		.codeSize = code.size(),
		.pCode    = reinterpret_cast<const std::uint32_t*>(code.data())
	};
}


