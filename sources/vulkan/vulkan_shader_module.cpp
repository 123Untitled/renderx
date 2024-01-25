#include "vulkan_shader_module.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::shader_module::shader_module(void) noexcept
: _module{}, _entry{} {
}

/* path constructor */
vulkan::shader_module::shader_module(const vk::shared<vk::device>& device,
									 const xns::string& path,
										   xns::string&& entry)
: _module{}, _entry{xns::move(entry)} {


	std::ifstream file{path.data(), std::ios::ate | std::ios::binary};
	if (!file.is_open()) {
		throw vulkan::exception{"failed to open shader file"};
	}

	std::vector<char> code;
	std::size_t size = static_cast<std::size_t>(file.tellg());
	code.resize(size);
	file.seekg(0);
	file.read(code.data(), static_cast<std::streamsize>(size));
	file.close();


	_module = vk::make_managed(vk::create(device, vk::shader_module_info{
		.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext    = VK_NULL_HANDLE,
		.flags    = 0,
		.codeSize = code.size(),
		.pCode    = reinterpret_cast<const vk::u32*>(code.data())
	}), device);
}

/* copy constructor */
vulkan::shader_module::shader_module(const self& other) noexcept
: _module{other._module}, _entry{other._entry} {
}

/* move constructor */
vulkan::shader_module::shader_module(self&& other) noexcept
: _module{xns::move(other._module)}, _entry{xns::move(other._entry)} {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::shader_module::operator=(const self& other) noexcept -> self& {
	_module = other._module;
	_entry  = other._entry;
	return *this;
}

/* move assignment operator */
auto vulkan::shader_module::operator=(self&& other) noexcept -> self& {
	_module = xns::move(other._module);
	_entry  = xns::move(other._entry);
	return *this;
}


// -- public conversion operators ---------------------------------------------

/* vk::shader_module conversion operator */
vulkan::shader_module::operator const vk::shader_module&(void) const noexcept {
	return _module;
}


// -- public accessors --------------------------------------------------------

/* stage info */
auto vulkan::shader_module::stage_info(const vk::shader_stage_flag_bits stage) const noexcept -> vk::pipeline_shader_stage_info {
	return vk::pipeline_shader_stage_info{
		.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext  = VK_NULL_HANDLE,
		.flags  = 0,
		.stage  = stage,
		.module = _module,
		.pName  = _entry.data(),
		.pSpecializationInfo = nullptr
	};
}



