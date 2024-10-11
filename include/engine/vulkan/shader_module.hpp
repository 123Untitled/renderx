/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_SHADER_MODULE___
#define ___RENDERX_VULKAN_SHADER_MODULE___

#include <vulkan/vulkan.h>

#include "engine/vulkan/device.hpp"

#include "engine/vk/typedefs.hpp"
#include "engine/vulkan/specialization.hpp"
#include "engine/vk/exception.hpp"
#include "engine/vk/utils.hpp"


#include <cstddef>
#include "renderx/meta/string_literal.hpp"

#include <sys/stat.h>
#include <vector>
#include <fcntl.h>
#include <unistd.h>



inline auto get_file_content(const std::string_view& path) -> std::vector<char> {

	// open file
	const int file = ::open(path.data(), O_RDONLY);
	if (file == -1)
		throw vk::exception{"failed to open shader file"};

	// get file size
	struct stat stat;
	if (::fstat(file, &stat) == -1)
		throw vk::exception{"failed to open shader file"};

	// get file size
	const vk::u32 size = static_cast<vk::u32>(stat.st_size);

	// create buffer
	std::vector<char> buffer;
	buffer.resize(size);

	// read file
	const auto readed = ::read(file, buffer.data(), size);

	// check readed size
	if (readed != size)
		throw vk::exception{"failed to read shader file"};

	// close file
	::close(file);

	// return buffer
	return buffer;
}



// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- S H A D E R  M O D U L E --------------------------------------------

	template <vk::shader_stage_flag_bits ___stage>
	class shader_module final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::shader_module<___stage>;


			// -- private members ---------------------------------------------

			/* shader module */
			vk::shader_module _module;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_module(void) noexcept
			: _module{nullptr} {
			}

			/* path constructor */
			shader_module(const std::string& ___path)
			/* uninitialized module */ {

				// get shader data
				const auto data = get_file_content(___path);

				// create info
				vk::shader_module_info info {
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
				};

				// create shader module
				vk::try_execute<"failed to create shader module">(
						::vk_create_shader_module,
						vulkan::device::logical(), &info, nullptr, &_module);
			}

			/* deleted copy constructor */
			shader_module(const ___self&) = delete;

			/* move constructor */
			shader_module(___self&& ___ot) noexcept
			: _module{___ot._module} {

				// invalidate other
				___ot._module = nullptr;
			}

			/* destructor */
			~shader_module(void) noexcept {

				if (_module == nullptr)
					return;

				// release shader module
				::vk_destroy_shader_module(vulkan::device::logical(), _module, nullptr);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check for self-assignment
				if (this == &___ot)
					return *this;

				// release shader module
				if (_module != nullptr)
					::vk_destroy_shader_module(vulkan::device::logical(),
							_module, nullptr);

				// move assignment
				_module = ___ot._module;
				___ot._module = nullptr;

				// done
				return *this;
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
					.pSpecializationInfo = &(___spec.info())
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

#endif // ___RENDERX_VULKAN_SHADER_MODULE___
