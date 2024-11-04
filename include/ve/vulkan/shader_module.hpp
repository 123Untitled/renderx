#ifndef ___ve_vulkan_shader_module___
#define ___ve_vulkan_shader_module___

#include "ve/vk/unique.hpp"

#include "ve/vulkan/specialization.hpp"
#include "ve/vk/exception.hpp"
#include "ve/vk/utils.hpp"


#include <cstddef>
#include "ve/meta/string_literal.hpp"

#include <sys/stat.h>
#include <vector>
#include <fcntl.h>
#include <unistd.h>



inline auto get_file_content(const char* path) -> std::vector<char> {

	// open file
	const int file = ::open(path, O_RDONLY);

	if (file == -1)
		throw std::runtime_error{std::string{"failed to open shader file: "} + path};

	// get file size
	struct stat stat;
	if (::fstat(file, &stat) == -1)
		throw "failed to open shader file";

	// get file size
	const vk::u32 size = static_cast<vk::u32>(stat.st_size);

	// create buffer
	std::vector<char> buffer;
	buffer.resize(size);

	// read file
	const auto readed = ::read(file, buffer.data(), size);

	// check readed size
	if (readed != size)
		throw "failed to read shader file";

	// close file
	::close(file);

	// return buffer
	return buffer;
}



// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- S H A D E R  M O D U L E --------------------------------------------

	template <::vk_shader_stage_flag_bits S>
	class shader_module final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::shader_module<S>;


			// -- private members ---------------------------------------------

			/* shader module */
			vk::unique<::vk_shader_module> _module;


			// -- private static methods --------------------------------------

			/* create shader module */
			template <unsigned N>
			static auto _create_shader_module(const char (&path)[N]) -> vk::unique<::vk_shader_module> {

				// get shader data
				const auto data = get_file_content(path);

				// create info
				::vk_shader_module_create_info info {
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
				return vk::make_unique<::vk_shader_module>(info);
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_module(void) noexcept = default;

			/* path constructor */
			template <unsigned N>
			shader_module(const char (&path)[N])
			: _module{self::_create_shader_module(path)} {
			}

			/* deleted copy constructor */
			shader_module(const self&) = delete;

			/* move constructor */
			shader_module(self&&) noexcept = default;

			/* destructor */
			~shader_module(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public static methods ---------------------------------------

			/* stage info */
			auto stage_info(void) const noexcept -> ::vk_pipeline_shader_stage_create_info {

				// create stage info
				return ::vk_pipeline_shader_stage_create_info {
					// structure type
					.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					// next structure
					.pNext  = nullptr,
					// flags
					.flags  = 0U,
					// stage
					.stage  = S,
					// module
					.module = _module.get(),
					// entry point
					.pName  = "main",
					// specialization info
					.pSpecializationInfo = nullptr
				};
			}

			/* stage info */
			template <typename... ___types>
			auto stage_info(const vulkan::specialization<___types...>& spec) const noexcept -> ::vk_pipeline_shader_stage_create_info {

				// create stage info
				return ::vk_pipeline_shader_stage_create_info {
					.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext  = nullptr,
					.flags  = 0U,
					.stage  = S,
					.module = _module.get(),
					.pName  = "main",
					.pSpecializationInfo = &(spec.info())
				};
			}


	}; // class shader_module


	// -- aliases -------------------------------------------------------------

	/* vertex module */
	using vert_module = vk::shader_module<VK_SHADER_STAGE_VERTEX_BIT>;

	/* fragment module */
	using frag_module = vk::shader_module<VK_SHADER_STAGE_FRAGMENT_BIT>;

	/* compute module */
	using comp_module = vk::shader_module<VK_SHADER_STAGE_COMPUTE_BIT>;

	/* tessellation control module */
	using tesc_module = vk::shader_module<VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>;

	/* tessellation evaluation module */
	using tese_module = vk::shader_module<VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>;

	/* geometry module */
	using geom_module = vk::shader_module<VK_SHADER_STAGE_GEOMETRY_BIT>;






	// -- S H A D E R  M O D U L E --------------------------------------------

	//class shader_module2 final {
	//
	//
	//	private:
	//
	//		// -- private types -----------------------------------------------
	//
	//		/* self type */
	//		using ___self = vulkan::shader_module2;
	//
	//
	//		// -- private members ---------------------------------------------
	//
	//		/* shader module */
	//		vk::shader_module _module;
	//
	//		/* stage */
	//		vk::shader_stage_flag_bits _stage;
	//
	//
	//	public:
	//
	//		// -- public lifecycle --------------------------------------------
	//
	//		/* default constructor */
	//		shader_module2(void) noexcept
	//		: _module{nullptr} /* uninitialized stage */ {
	//		}
	//
	//		/* default constructor */
	//		shader_module2(const std::string_view& path, const vk::shader_stage_flag_bits stage)
	//		: /* uninitialized module */ _stage{stage} {
	//
	//			// get shader data
	//			const auto data = get_file_content(path);
	//
	//			// create info
	//			vk::shader_module_info info {
	//				// structure type
	//				.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
	//				// next structure
	//				.pNext    = nullptr,
	//				// flags
	//				.flags    = 0U,
	//				// data size
	//				.codeSize = data.size(),
	//				// data pointer
	//				.pCode    = reinterpret_cast<const vk::u32*>(data.data())
	//			};
	//
	//			// create shader module
	//			vk::try_execute<"failed to create shader module">(
	//					::vk_create_shader_module,
	//					vulkan::device::logical(), &info, nullptr, &_module);
	//		}
	//
	//		/* deleted copy constructor */
	//		shader_module2(const ___self&) = delete;
	//
	//		/* move constructor */
	//		shader_module2(___self&& ___ot) noexcept
	//		: _module{___ot._module}, _stage{___ot._stage} {
	//
	//			// invalidate other
	//			___ot._module = nullptr;
	//		}
	//
	//		/* destructor */
	//		~shader_module2(void) noexcept {
	//
	//			if (_module == nullptr)
	//				return;
	//
	//			// release shader module
	//			::vk_destroy_shader_module(
	//					vulkan::device::logical(), _module, nullptr);
	//		}
	//
	//
	//		// -- public assignment operators ---------------------------------
	//
	//		/* deleted copy assignment operator */
	//		auto operator=(const ___self&) -> ___self& = delete;
	//
	//		/* move assignment operator */
	//		auto operator=(___self&& ___ot) noexcept -> ___self& {
	//
	//			// check for self-assignment
	//			if (this == &___ot)
	//				return *this;
	//
	//			// release shader module
	//			if (_module != nullptr)
	//				::vk_destroy_shader_module(vulkan::device::logical(),
	//						_module, nullptr);
	//
	//			// move assignment
	//			_module = ___ot._module;
	//			_stage  = ___ot._stage;
	//			___ot._module = nullptr;
	//
	//			// done
	//			return *this;
	//		}
	//
	//
	//
	//		// -- public static methods ---------------------------------------
	//
	//		/* stage info */
	//		auto stage_info(void) const noexcept -> vk::pipeline_shader_stage_info {
	//
	//			// create stage info
	//			return vk::pipeline_shader_stage_info {
	//				.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
	//				.pNext  = nullptr,
	//				/* flags:
	//					VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT
	//					VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT
	//					VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT
	//					VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
	//				*/
	//				.flags  = 0U,
	//				.stage  = _stage,
	//				.module = _module,
	//				.pName  = "main",
	//				.pSpecializationInfo = nullptr
	//			};
	//		}
	//
	//		/* stage info */
	//		template <typename... ___types>
	//		auto stage_info(const vulkan::specialization<___types...>& ___spec) const noexcept -> vk::pipeline_shader_stage_info {
	//
	//			// create stage info
	//			return vk::pipeline_shader_stage_info {
	//				.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
	//				.pNext  = nullptr,
	//				.flags  = 0U,
	//				.stage  = _stage,
	//				.module = _module,
	//				.pName  = "main",
	//				.pSpecializationInfo = &(___spec.info())
	//			};
	//		}
	//
	//
	//}; // class shader_module

} // namespace vk

#endif // ___ve_vulkan_shader_module___
