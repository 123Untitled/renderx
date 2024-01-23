#include "vulkan_shader_module.hpp"
#include "vulkan_logical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::shader_module::shader_module(void) noexcept
: _module{VK_NULL_HANDLE} {
}

/* path constructor */
vulkan::shader_module::shader_module(const vulkan::logical_device& device,
									 const std::string& path)
: _module{VK_NULL_HANDLE} {


	std::ifstream file{path, std::ios::ate | std::ios::binary};
	if (!file.is_open()) {
		throw vulkan::exception{"failed to open shader file", (VkResult)0};
	}

	std::cout << "shader file opened: " << path << std::endl;

	std::vector<char> code;
	std::size_t size = static_cast<std::size_t>(file.tellg());
	code.resize(size);
	file.seekg(0);
	file.read(code.data(), static_cast<std::streamsize>(size));
	file.close();

	// create shader module
	_module = vk::create(device, vk::shader_module_info{
		.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext    = VK_NULL_HANDLE,
		.flags    = 0,
		.codeSize = code.size(),
		.pCode    = reinterpret_cast<const vk::u32*>(code.data())
	});

}

/* copy constructor */
vulkan::shader_module::shader_module(const self& other) noexcept
: _module{other._module} {
}

/* move constructor */
vulkan::shader_module::shader_module(self&& other) noexcept
: self{other} /* copy */ {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::shader_module::operator=(const self& other) noexcept -> self& {
	_module = other._module;
	return *this;
}

/* move assignment operator */
auto vulkan::shader_module::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public conversion operators ---------------------------------------------

/* vk::shader_module conversion operator */
vulkan::shader_module::operator const vk::shader_module&(void) const noexcept {
	return _module;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::shader_module::destroy(const vulkan::logical_device& device) noexcept -> void {
	vk::destroy(device, _module);
}


