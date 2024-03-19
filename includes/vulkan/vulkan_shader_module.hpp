/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_SHADER_MODULE_HPP
#define ENGINE_VULKAN_SHADER_MODULE_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "vk_typedefs.hpp"
#include "vk_shared.hpp"
#include "vk_functions.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* device */
	class device;


	// -- S H A D E R  M O D U L E --------------------------------------------

	class shader_module final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shader_module;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_module(void) noexcept = default;

			/* logical device and path constructor */
			shader_module(const vk::shared<vk::device>&,
						  const xns::string&,
								xns::string&&);

			/* copy constructor */
			shader_module(const self&) noexcept = default;

			/* move constructor */
			shader_module(self&&) noexcept = default;

			/* destructor */
			~shader_module(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::shader_module conversion operator */
			operator const vk::shader_module&(void) const noexcept;


			// -- public accessors --------------------------------------------

			/* stage info */
			auto stage_info(const vk::shader_stage_flag_bits) const noexcept -> vk::pipeline_shader_stage_info;


		private:

			// -- private members ---------------------------------------------

			/* shader module */
			vk::shared<vk::shader_module> _module;

			/* entry point */
			xns::string _entry;

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
