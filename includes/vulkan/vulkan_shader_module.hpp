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
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "vk_typedefs.hpp"
#include "vk_shared.hpp"
#include "vk_functions.hpp"

#include <cstddef>

#include <xns/string_literal.hpp>

// for specialization
#include <xns/integer_sequence.hpp>
#include <xns/type_at.hpp>
#include <xns/is_trivially_copyable.hpp>
#include <xns/is_nothrow_default_constructible.hpp>
#include <xns/is_empty.hpp>
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
			shader_module(void) noexcept = default;

			/* logical device and path constructor */
			shader_module(const vk::shared<vk::device>& device,
						  const xns::string& path)
			: _module{},
			  _stage{
				.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.pNext  = nullptr,
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





	template <typename... __types>
	class specialization final {


		// -- assertions ------------------------------------------------------

		/* check if all types are trivially copyable */
		static_assert(xns::are_trivially_copyable<__types...>,
				"specialization: all types must be trivially copyable");

		/* check if all types are nothrow constructible */
		static_assert(xns::are_nothrow_default_constructible<__types...>,
				"specialization: all types must be nothrow constructible");

		/* check if all types are not empty classes */
		static_assert((not xns::is_empty<__types> and ...),
				"specialization: all types must not be empty classes");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::specialization<__types...>;

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* sequence type */
			template <size_type... __idx>
			using __sequence = xns::integer_sequence<vk::u32, __idx...>;

			/* make sequence type */
			using __make_sequence = xns::make_integer_sequence<vk::u32, sizeof...(__types)>;

			/* type at */
			template <size_type __idx>
			using __type_at = xns::type_at<__idx, __types...>;


			// -- private structs ---------------------------------------------

			/* wrapper */
			template <size_type __idx, typename __type>
			struct alignas(sizeof(void*)) __wrapper {

				/* info:
				 * alignment: size of arch pointer
				 */

				// -- members -------------------------------------------------

				/* value */
				__type value;

			}; // struct __wrapper


			/* implementation */
			template <typename>
			struct __impl;

			/* implementation */
			template <size_type... __idx>
			struct __impl<__sequence<__idx...>> final : public __wrapper<__idx, __types>... {


				// -- types ---------------------------------------------------

				/* self type */
				using __self = self::__impl<__sequence<__idx...>>;


				// -- lifecycle -----------------------------------------------

				/* constructor */
				constexpr __impl(void) noexcept = default;

				/* variadic constructor */
				template <typename... __params>
				constexpr __impl(__params&&... params) noexcept
				: __wrapper<__idx, __types>{xns::forward<__params>(params)}... {
				}

				/* copy constructor */
				constexpr __impl(const __impl&) noexcept = default;

				/* move constructor */
				constexpr __impl(__impl&&) noexcept = default;

				/* destructor */
				~__impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const __impl&) noexcept -> __impl& = default;

				/* move assignment operator */
				constexpr auto operator=(__impl&&) noexcept -> __impl& = default;

			}; // struct __impl


			/* impl type */
			using __impl_type = __impl<__make_sequence>;

			/* wrapper at */
			template <size_type __idx>
			using __wrapper_at = typename __impl_type::template __wrapper<__idx, __type_at<__idx>>;


			/* offset_of */
			template <size_type __type_idx>
			class __offset_of final {


				private:

					// -- private types ---------------------------------------

					/* self type */
					using __self = self::__offset_of<__type_idx>;


					// -- private static methods ------------------------------

					/* compute */
					template <size_type __idx, size_type __offset>
					static consteval auto __compute(void) noexcept -> size_type {
						// end of recursion
						if constexpr (__idx == __type_idx)
							return __offset;
						// recursive call
						else return __self::__compute<__idx + 1, __offset + sizeof(__wrapper_at<__idx>)>();
					}

				public:

					// -- public constants ------------------------------------

					/* value */
					static constexpr auto value = __compute<0, 0>();

			}; // class offset_of

			/* offset at */
			template <size_type __idx>
			static constexpr auto __offset_at = __offset_of<__idx>::value;


			/* entries */
			struct __entries final {


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				__entries(void) noexcept = default;

				/* sequence constructor */
				template <size_type... __idx>
				constexpr __entries(__sequence<__idx...>) noexcept
				: entries{{
					// constant id
					.constantID = __idx,
					// offset
					.offset     = __offset_at<__idx>,
					// size
					.size       = sizeof(__type_at<__idx>)
					}...} {
				}

				/* copy constructor */
				constexpr __entries(const __entries&) noexcept = default;

				/* move constructor */
				constexpr __entries(__entries&&) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const __entries&) noexcept -> __entries& = default;

				/* move assignment operator */
				constexpr auto operator=(__entries&&) noexcept -> __entries& = default;


				// -- conversion operators ------------------------------------

				/* vk::specialization_map_entry conversion operator */
				constexpr operator const vk::specialization_map_entry*(void) const noexcept {
					return entries;
				}


				// -- members -------------------------------------------------

				/* entries */
				vk::specialization_map_entry entries[sizeof...(__types)];

			}; // struct __entries


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			specialization(void) = delete;

			/* variadic constructor */
			template <typename... __params>
			constexpr specialization(__params&&... params) noexcept
			: _entries{__make_sequence{}},
			  _info{
				// map entry count
				.mapEntryCount = sizeof...(__types),
				// map entries
				.pMapEntries   = _entries,
				// data size
				.dataSize      = sizeof(_impl),
				// data
				.pData         = &_impl
			  },
			  _impl{xns::forward<__params>(params)...} {
			}

			/* copy constructor */
			constexpr specialization(const self&) noexcept = default;

			/* move constructor */
			constexpr specialization(self&&) noexcept = default;

			/* destructor */
			~specialization(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* info */
			constexpr auto info(void) const noexcept -> const vk::specialization_info& {
				return _info;
			}

			/* entries */
			constexpr auto operator[](const size_type& idx) const noexcept -> const vk::specialization_map_entry& {
				return _entries.entries[idx];
			}


			// -- public conversion operators ---------------------------------

			/* vk::specialization_info conversion operator */
			constexpr operator const vk::specialization_info&(void) const noexcept {
				return _info;
			}



			// -- public methods ----------------------------------------------

			/* print */
			void print(void) const noexcept {
				std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "///[SPECIALIZATION INFO]///" << std::endl;
				std::cout << "map entry count: " << _info.mapEntryCount << std::endl;
				std::cout << "data size: " << _info.dataSize << std::endl;
				std::cout << "map entries: " << std::endl;
				__print<0>();
			}


		private:

			// -- private methods ---------------------------------------------

			/* print */
			template <size_type __idx>
			void __print(void) const noexcept {
				if constexpr (__idx == sizeof...(__types)) {
					return;
				}
				else {
					const auto& id     = _entries.entries[__idx].constantID;
					const auto& offset = _entries.entries[__idx].offset;
					const auto& size   = _entries.entries[__idx].size;

					std::cout << "------[" << __idx << "]------" << std::endl;
					std::cout << "      constant id: " << id     << std::endl;
					std::cout << "           offset: " << offset << std::endl;
					std::cout << "             size: " << size   << std::endl;

					const char* data = reinterpret_cast<const char*>(_info.pData);

					data += offset;

					auto* ptr = reinterpret_cast<const __type_at<__idx>*>(data);

					std::cout << "            value: " << *ptr << std::endl;
					__print<__idx + 1>();
				}
			}


			// -- private members ---------------------------------------------

			/* entries */
			__entries _entries;

			/* info */
			vk::specialization_info _info;

			/* impl */
			__impl<__make_sequence> _impl;

	}; // class specialization

	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... __types>
	specialization(__types...) -> specialization<__types...>;


} // namespace vulkan

#endif // ENGINE_VULKAN_SHADER_MODULE_HPP
