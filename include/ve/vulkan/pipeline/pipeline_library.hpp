#ifndef ___ve_vvulken_pipeline_library___
#define ___ve_vvulken_pipeline_library___

#include "ve/containers/static_map.hpp"
#include "ve/vulkan/pipeline/builder.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- P I P E L I N E  L I B R A R Y ---------------------------------------

	class pipeline_library final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ve::pipeline_library;


			// -- private members ---------------------------------------------

			ve::static_map<vk::pipeline,
				"planet",
				"skybox_heightmap_compute"
				> _pipelines;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			pipeline_library(void)
			: _pipelines{
				self::_planet(),
				self::_skybox_heightmap_compute()} {
			}

			/* deleted copy constructor */
			pipeline_library(const self&) = delete;

			/* deleted move constructor */
			pipeline_library(self&&) = delete;

			/* destructor */
			~pipeline_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- private static methods --------------------------------------

			/* planet */
			static auto _planet(void) -> vk::pipeline {

				return {};
				//return vk::pipeline::builder::planet();
			}


			/* skybox heightmap compute */
			static auto _skybox_heightmap_compute(void) -> vk::pipeline {

				return {};
				//const vk::comp_module m{"shaders/spir-v/skybox_heightmap.comp.spv"};
				//
				//return vk::pipeline{
				//	m.stage_info(),
				//	ve::pipeline_layout_library::get<"skybox_heightmap">()
				//};
			}


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const ::vk_pipeline& {
				return (ve::get<key>(self::_shared()._pipelines));
			}

	}; // class pipeline_library

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_LIBRARY_HPP
