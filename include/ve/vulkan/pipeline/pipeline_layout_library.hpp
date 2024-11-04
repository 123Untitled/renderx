#ifndef ___ve_vulkan_pipeline_layout_library___
#define ___ve_vulkan_pipeline_layout_library___

#include "ve/containers/static_map.hpp"

#include "ve/vulkan/descriptor/descriptor_set_layout_library.hpp"
#include "ve/vulkan/pipeline/layout.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- P I P E L I N E  L A Y O U T  L I B R A R Y -------------------------

	class pipeline_layout_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline_layout_library;


			// -- private members ---------------------------------------------

			ve::static_map<vk::pipeline::layout,
				"main",
				"skybox_compute"
				> _layouts;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			pipeline_layout_library(void)
			: _layouts{
				self::_main_layout(),
				self::_skybox_compute()} {
			}

			/* deleted copy constructor */
			pipeline_layout_library(const self&) = delete;

			/* deleted move constructor */
			pipeline_layout_library(self&&) = delete;

			/* destructor */
			~pipeline_layout_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- private static methods --------------------------------------

			/* main layout */
			static auto _main_layout(void) -> vk::pipeline::layout {

				// create push constant range
				const vk::push_constant_range range {
					// stage flags
					VK_SHADER_STAGE_FRAGMENT_BIT,
					// offset
					0U,
					// size
					sizeof(float)
				};

				const ::vk_descriptor_set_layout layouts[] {
					ve::descriptor_set_layout_library::get<"camera">(),
					ve::descriptor_set_layout_library::get<"planet">(),
				};

				return vk::pipeline::layout{layouts, range};
			}


			/* skybox compute */
			static auto _skybox_compute(void) -> vk::pipeline::layout {

				const ::vk_descriptor_set_layout layouts[] {
					ve::descriptor_set_layout_library::get<"skybox_compute">()
				};

				return vk::pipeline::layout{layouts};
			}


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const ::vk_pipeline_layout& {
				return ve::get<key>(self::_shared()._layouts);
			}

	}; // class pipeline_layout_library

} // namespace vk

#endif // ___ve_vulkan_pipeline_layout_library___
