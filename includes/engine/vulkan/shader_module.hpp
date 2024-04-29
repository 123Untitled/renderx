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

	template <xns::basic_string_literal __type>
	class shader_module final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::shader_module<__type>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr shader_module(void) noexcept
			: _module{}, _stage{} {
			}

			/* logical device and path constructor */
			shader_module(const vk::shared<vk::device>& device,
						  const xns::string& path)
			: _module{},
			  _stage{
				.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.pNext  = VK_NULL_HANDLE,
				/* flags:
				 * VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT
				 * VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT
				 * VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT
				 * VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
				 */
				.flags  = 0U,
				.stage  = self::__stage_flag(),
				.module = nullptr,
				.pName  = "main",
				.pSpecializationInfo = nullptr
			} {

				auto data = get_file_content(path);

				_module = {device, vk::shader_module_info{
					.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
					.pNext    = nullptr,
					.flags    = 0,
					.codeSize = data.size(),
					.pCode    = reinterpret_cast<const vk::u32*>(data.data())
				}};

				_stage.module = _module;

			}


			static consteval auto __stage_flag(void) -> vk::shader_stage_flag_bits {

				// VK_SHADER_STAGE_VERTEX_BIT
				if constexpr (__type == "vertex")
					return VK_SHADER_STAGE_VERTEX_BIT;

				// VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT
				if constexpr (__type == "tess_control")
					return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;

				// VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT
				if constexpr (__type == "tess_eval")
					return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;

				// VK_SHADER_STAGE_GEOMETRY_BIT
				if constexpr (__type == "geometry")
					return VK_SHADER_STAGE_GEOMETRY_BIT;

				// VK_SHADER_STAGE_FRAGMENT_BIT
				if constexpr (__type == "fragment")
					return VK_SHADER_STAGE_FRAGMENT_BIT;

				// VK_SHADER_STAGE_COMPUTE_BIT
				if constexpr (__type == "compute")
					return VK_SHADER_STAGE_COMPUTE_BIT;

				// VK_SHADER_STAGE_ALL_GRAPHICS
				if constexpr (__type == "all_graphics")
					return VK_SHADER_STAGE_ALL_GRAPHICS;

				// VK_SHADER_STAGE_ALL
				if constexpr (__type == "all")
					return VK_SHADER_STAGE_ALL;

				// VK_SHADER_STAGE_RAYGEN_BIT_KHR
				if constexpr (__type == "raygen")
					return VK_SHADER_STAGE_RAYGEN_BIT_KHR;

				// VK_SHADER_STAGE_ANY_HIT_BIT_KHR
				if constexpr (__type == "any_hit")
					return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;

				// VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR
				if constexpr (__type == "closest_hit")
					return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;

				// VK_SHADER_STAGE_MISS_BIT_KHR
				if constexpr (__type == "miss")
					return VK_SHADER_STAGE_MISS_BIT_KHR;

				// VK_SHADER_STAGE_INTERSECTION_BIT_KHR
				if constexpr (__type == "intersection")
					return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;

				// VK_SHADER_STAGE_CALLABLE_BIT_KHR
				if constexpr (__type == "callable")
					return VK_SHADER_STAGE_CALLABLE_BIT_KHR;

				// VK_SHADER_STAGE_TASK_BIT_EXT
				if constexpr (__type == "task")
					return VK_SHADER_STAGE_TASK_BIT_EXT;

				// VK_SHADER_STAGE_MESH_BIT_EXT
				if constexpr (__type == "mesh")
					return VK_SHADER_STAGE_MESH_BIT_EXT;

				// VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI
				if constexpr (__type == "subpass_shading")
					return VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI;

				// VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
				if constexpr (__type == "cluster_culling")
					return VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI;

				// VK_SHADER_STAGE_RAYGEN_BIT_NV
				if constexpr (__type == "raygen nv")
					return VK_SHADER_STAGE_RAYGEN_BIT_NV;

				// VK_SHADER_STAGE_ANY_HIT_BIT_NV
				if constexpr (__type == "any_hit nv")
					return VK_SHADER_STAGE_ANY_HIT_BIT_NV;

				// VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV
				if constexpr (__type == "closest_hit nv")
					return VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

				// VK_SHADER_STAGE_MISS_BIT_NV
				if constexpr (__type == "miss nv")
					return VK_SHADER_STAGE_MISS_BIT_NV;

				// VK_SHADER_STAGE_INTERSECTION_BIT_NV
				if constexpr (__type == "intersection nv")
					return VK_SHADER_STAGE_INTERSECTION_BIT_NV;

				// VK_SHADER_STAGE_CALLABLE_BIT_NV
				if constexpr (__type == "callable nv")
					return VK_SHADER_STAGE_CALLABLE_BIT_NV;

				// VK_SHADER_STAGE_TASK_BIT_NV
				if constexpr (__type == "task nv")
					return VK_SHADER_STAGE_TASK_BIT_NV;

				// VK_SHADER_STAGE_MESH_BIT_NV
				if constexpr (__type == "mesh nv")
					return VK_SHADER_STAGE_MESH_BIT_NV;

				else
					return static_cast<vk::shader_stage_flag_bits>(0U);

			}

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
			operator const vk::shader_module&(void) const noexcept {
				return _module;
			}


			// -- public accessors --------------------------------------------

			/* stage info */
			auto stage_info(const vk::shader_stage_flag_bits& stage) const noexcept -> vk::pipeline_shader_stage_info {
				return {};
			}


		private:

			// -- private members ---------------------------------------------

			/* shader module */
			vk::shared<vk::shader_module> _module;

			/* shader stage */
			vk::pipeline_shader_stage_info _stage;


		// -- assertions ------------------------------------------------------

		/* check if type is valid */
		static_assert(__stage_flag() != 0U,
				"shader_module: invalid shader type");

	}; // class shader_module

} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
