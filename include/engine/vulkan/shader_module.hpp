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

#ifndef ENGINE_VULKAN_SHADER_MODULE_HEADER
#define ENGINE_VULKAN_SHADER_MODULE_HEADER

#include <vulkan/vulkan.h>

//#include <string>
//#include <fstream>
//#include <iostream>
//#include <vector>

#include "engine/vk/typedefs.hpp"
#include "engine/vulkan/specialization.hpp"
#include "engine/vk/shared.hpp"
//#include "engine/vk/functions.hpp"

#include <cstddef>

#include <xns/string_literal.hpp>

#include <xns/unique_descriptor.hpp>

#include <sys/stat.h>



inline auto get_file_content(const xns::string_view& path) -> xns::vector<char> {

	xns::unique_descriptor file{::open(path.data(), O_RDONLY)};

	if (not file)
		throw vk::exception{"failed to open shader file"};

	struct stat stat;
	if (::fstat(file, &stat) == -1)
		throw vk::exception{"failed to open shader file"};

	const vk::u32 size = static_cast<vk::u32>(stat.st_size);

	xns::vector<char> buffer;
	buffer.resize(size);


	const auto readed = ::read(file, buffer.data(), size);

	if (readed != size)
		throw vk::exception{"failed to read shader file"};

	return buffer;
}



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* device */
	class device;


	// -- S H A D E R  M O D U L E --------------------------------------------

	template <vk::shader_stage_flag_bits ___stage>
	class shader_module final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::shader_module<___stage>;


			// -- private members ---------------------------------------------

			/* shader module */
			vk::shared<vk::shader_module> _module;


			// -- private methods ---------------------------------------------

			/* create shader module */
			static auto _create_shader_module(const vk::shared<vk::device>& ___device,
											  const xns::string& ___path) -> vk::shared<vk::shader_module> {

				// get shader data
				const auto data = get_file_content(___path);

				// create shader module
				return vk::shared<vk::shader_module>{___device, vk::shader_module_info{
					// structure type
					.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
					// next structure
					.pNext    = nullptr,
					// flags
					.flags    = 0U,
					// data size
					.codeSize = data.size(),
					// data pointer
					.pCode    = reinterpret_cast<const vk::u32*>(data.data())
				}};
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_module(void) noexcept = default;

			/* logical device and path constructor */
			shader_module(const vk::shared<vk::device>&     ___device,
						  const xns::string&                ___path)
			: _module{___self::_create_shader_module(___device, ___path)} {
			}

			/* copy constructor */
			shader_module(const ___self&) noexcept = default;

			/* move constructor */
			shader_module(___self&&) noexcept = default;

			/* destructor */
			~shader_module(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::shader_module conversion operator */
			operator const vk::shader_module&(void) const noexcept {
				return _module;
			}


			// -- public static methods ---------------------------------------

			/* stage info */
			auto stage_info(void) const noexcept -> vk::pipeline_shader_stage_info {

				// create stage info
				return vk::pipeline_shader_stage_info {
					.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext  = nullptr,
					/* flags:
						VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT
						VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT
						VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT
						VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
					*/
					.flags  = 0U,
					.stage  = ___stage,
					.module = _module,
					.pName  = "main",
					.pSpecializationInfo = nullptr
				};
			}

			/* stage info */
			template <typename... ___types>
			auto stage_info(const vulkan::specialization<___types...>& ___spec) const noexcept -> vk::pipeline_shader_stage_info {

				// create stage info
				return vk::pipeline_shader_stage_info {
					.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext  = nullptr,
					.flags  = 0U,
					.stage  = ___stage,
					.module = _module,
					.pName  = "main",
					.pSpecializationInfo = &___spec.info(),
				};
			}


	}; // class shader_module


	// -- aliases -------------------------------------------------------------

	/* vertex module */
	using vertex_module = vulkan::shader_module<VK_SHADER_STAGE_VERTEX_BIT>;

	/* fragment module */
	using fragment_module = vulkan::shader_module<VK_SHADER_STAGE_FRAGMENT_BIT>;

	/* compute module */
	using compute_module = vulkan::shader_module<VK_SHADER_STAGE_COMPUTE_BIT>;

	/* tessellation control module */
	using tessellation_control_module = vulkan::shader_module<VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>;

	/* tessellation evaluation module */
	using tessellation_evaluation_module = vulkan::shader_module<VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>;

	/* geometry module */
	using geometry_module = vulkan::shader_module<VK_SHADER_STAGE_GEOMETRY_BIT>;

} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
