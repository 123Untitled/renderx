#ifndef ENGINE_VULKAN_SHADER_MODULE_HPP
#define ENGINE_VULKAN_SHADER_MODULE_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* logical device */
	class logical_device;


	// -- S H A D E R  M O D U L E --------------------------------------------

	class shader_module final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shader_module;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			shader_module(void) = delete;

			/* logical device and path constructor */
			shader_module(const vulkan::logical_device&, const std::string&);

			/* deleted copy constructor */
			shader_module(const self&) = default;

			/* deleted move constructor */
			shader_module(self&&) noexcept = default;

			/* destructor */
			~shader_module(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = default;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* VkShaderModule conversion operator */
			operator ::VkShaderModule(void) noexcept;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


		private:

			// -- private static methods --------------------------------------

			/* create shader module */
			static auto create_shader_module(const vulkan::logical_device&,
											 const ::VkShaderModuleCreateInfo&,
											 ::VkShaderModule&) noexcept -> ::VkResult;

			/* create shader module info */
			static auto create_shader_module_info(const std::vector<char>&) noexcept -> ::VkShaderModuleCreateInfo;


			// -- private members ---------------------------------------------

			/* shader module */
			::VkShaderModule _module;

	}; // class shader_module





	/*
	template <::VkShaderStageFlagBits stage>
	auto create_pipeline_shader_stage_info(const vulkan::shader_module& module) noexcept -> ::VkPipelineShaderStageCreateInfo {
		return ::VkPipelineShaderStageCreateInfo{
			.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext  = nullptr,
			.flags  = 0,
			.stage  = stage,
			.module = module,
			.pName  = "main",
			.pSpecializationInfo = nullptr
		};
	}*/


} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
