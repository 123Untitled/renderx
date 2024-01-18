#include "vulkan_shader_module.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::shader_module::shader_module(void) noexcept
: _module{nullptr}, _device{nullptr} {}

/* path constructor */
vulkan::shader_module::shader_module(const vulkan::logical_device& device,
									 const std::string& path)
: _module{nullptr}, _device{device.underlying()} {

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

/* move constructor */
vulkan::shader_module::shader_module(self&& other) noexcept
: _module{other._module}, _device{other._device} {
	other.init();
}

/* destructor */
vulkan::shader_module::~shader_module(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::shader_module::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	_module = other._module;
	_device = other._device;
	other.init();
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::shader_module::underlying(void) noexcept -> ::VkShaderModule& {
	return _module;
}

/* const underlying */
auto vulkan::shader_module::underlying(void) const noexcept -> const ::VkShaderModule& {
	return _module;
}


// -- private static methods --------------------------------------------------

/* create shader module */
auto vulkan::shader_module::create_shader_module(const vulkan::logical_device& device,
												 const ::VkShaderModuleCreateInfo& info,
												 ::VkShaderModule& module) noexcept -> ::VkResult {
	return ::vkCreateShaderModule(device.underlying(), &info, nullptr, &module);
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


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::shader_module::free(void) noexcept -> void {
	if (_module == VK_NULL_HANDLE)
		return;
	::vkDestroyShaderModule(_device, _module, nullptr);
}

/* init */
auto vulkan::shader_module::init(void) noexcept -> void {
	_module = VK_NULL_HANDLE;
	_device = VK_NULL_HANDLE;
}
