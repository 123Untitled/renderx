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
			shader_module(void) noexcept;

			/* path constructor */
			shader_module(const vulkan::logical_device&, const std::string&);

			/* deleted copy constructor */
			shader_module(const self&) = delete;

			/* move constructor */
			shader_module(self&&) noexcept;

			/* destructor */
			~shader_module(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkShaderModule&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkShaderModule&;


		private:

			// -- private static methods --------------------------------------

			/* create shader module */
			static auto create_shader_module(const vulkan::logical_device&,
											 const ::VkShaderModuleCreateInfo&,
											 ::VkShaderModule&) noexcept -> ::VkResult;

			/* create shader module info */
			static auto create_shader_module_info(const std::vector<char>&) noexcept -> ::VkShaderModuleCreateInfo;


			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


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


	template <::VkShaderStageFlagBits stage>
	auto create_pipeline_shader_stage_info(const vulkan::shader_module& module) noexcept -> ::VkPipelineShaderStageCreateInfo {
		return ::VkPipelineShaderStageCreateInfo{
			.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext  = nullptr,
			.flags  = 0,
			.stage  = stage,
			.module = module.underlying(),
			.pName  = "main",
			.pSpecializationInfo = nullptr
		};
	}


} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
