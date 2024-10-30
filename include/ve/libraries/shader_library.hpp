#ifndef ___ve_libraries_shader_library___
#define ___ve_libraries_shader_library___

#include "ve/containers/static_map.hpp"
#include "ve/vulkan/shader_module.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S H A D E R  L I B R A R Y ------------------------------------------

	class shader_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::shader_library;


			// -- private members ---------------------------------------------

			/* vertex modules */
			ve::static_map<vulkan::shader_module2, "planet">
				_vertex_modules;

			/* fragment modules */
			ve::static_map<vulkan::shader_module2, "planet">
				_fragment_modules;

			/* tesscontrol modules */
			ve::static_map<vulkan::shader_module2, "planet">
				_tesscontrol_modules;

			/* tesseval modules */
			ve::static_map<vulkan::shader_module2, "planet">
				_tesseval_modules;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self instance;
				return instance;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			shader_library(void)
			: _vertex_modules{}, _fragment_modules{} {

				ve::get<"planet">(_vertex_modules)
					= vulkan::shader_module2{"shaders/spir-v/planet.vert.spv", VK_SHADER_STAGE_VERTEX_BIT};

				ve::get<"planet">(_fragment_modules)
					= vulkan::shader_module2{"shaders/spir-v/planet.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT};

				ve::get<"planet">(_tesscontrol_modules)
					= vulkan::shader_module2{"shaders/spir-v/planet.tesc.spv", VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT};

				ve::get<"planet">(_tesseval_modules)
					= vulkan::shader_module2{"shaders/spir-v/planet.tese.spv", VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT};
			}

			/* deleted copy constructor */
			shader_library(const ___self&) = delete;

			/* deleted move constructor */
			shader_library(___self&&) = delete;

			/* destructor */
			~shader_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;



		public:

			// -- public static methods ---------------------------------------

			/* vertex module */
			template <ve::literal ___key>
			static auto vertex_stage_info(void) -> vk::pipeline_shader_stage_info {
				return ve::get<___key>(___self::_shared()._vertex_modules).stage_info();
			}

			/* fragment module */
			template <ve::literal ___key>
			static auto fragment_stage_info(void) -> vk::pipeline_shader_stage_info {
				return ve::get<___key>(___self::_shared()._fragment_modules).stage_info();
			}

			/* hull module */
			template <ve::literal ___key>
			static auto hull_stage_info(void) -> vk::pipeline_shader_stage_info {
				return ve::get<___key>(___self::_shared()._tesscontrol_modules).stage_info();
			}

			/* domain module */
			template <ve::literal ___key>
			static auto domain_stage_info(void) -> vk::pipeline_shader_stage_info {
				return ve::get<___key>(___self::_shared()._tesseval_modules).stage_info();
			}

	}; // class shader_library


} // namespace ve

#endif // ___void_libraries_shader_library___
