#ifndef ENGINE_VULKAN_SHADER_MODULE_HPP
#define ENGINE_VULKAN_SHADER_MODULE_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- S H A D E R  M O D U L E --------------------------------------------

	class shader_module final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shader_module;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_module(void) noexcept
			: _module{nullptr}, _device{nullptr} {
			}

			/* path constructor */
			shader_module(vulkan::logical_device& device, const std::string& path)
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

				::VkShaderModuleCreateInfo info{};
				info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				info.codeSize = size;
				info.pCode = reinterpret_cast<const std::uint32_t*>(buffer.data());

				::VkResult result = ::vkCreateShaderModule(_device, &info, nullptr, &_module);

				if (result != VK_SUCCESS) {
					std::cerr << "failed to create shader module: " << result << std::endl;
					return;
				}

			}

			/* deleted copy constructor */
			shader_module(const self&) = delete;

			/* move constructor */
			shader_module(self&& other) noexcept
			: _module{other._module}, _device{other._device} {
				other.init();
			}

			/* destructor */
			~shader_module(void) noexcept {
				free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				free();
				_module = other._module;
				_device = other._device;
				other.init();
				return *this;
			}


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				if (_module == nullptr)
					return;
				::vkDestroyShaderModule(_device, _module, nullptr);
			}

			/* init */
			auto init(void) noexcept -> void {
				_module = nullptr;
				_device = nullptr;
			}


			// -- private members ---------------------------------------------

			/* shader module */
			::VkShaderModule _module;

			/* vulkan device */
			::VkDevice _device;


	}; // class shader_module



	class shader_library final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shader_library;




	};


} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
