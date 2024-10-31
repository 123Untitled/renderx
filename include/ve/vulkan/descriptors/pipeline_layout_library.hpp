#ifndef ___ve_vulkan_descriptor_pipeline_layout_library___
#define ___ve_vulkan_descriptor_pipeline_layout_library___

#include "ve/vulkan/descriptors/descriptor_set_layout_library.hpp"
#include "ve/containers/static_map.hpp"
#include "ve/vulkan/pipeline/pipeline_layout.hpp"


// -- V E ---------------------------------------------------------------------

namespace ve {


	// -- P I P E L I N E  L A Y O U T  L I B R A R Y -------------------------

	class pipeline_layout_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::pipeline_layout_library;


			// -- private members ---------------------------------------------

			ve::static_map<vulkan::pipeline_layout,
				"main"> _layouts;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			pipeline_layout_library(void)
			: _layouts{
				___self::_main_layout()} {
			}

			/* deleted copy constructor */
			pipeline_layout_library(const ___self&) = delete;

			/* deleted move constructor */
			pipeline_layout_library(___self&&) = delete;

			/* destructor */
			~pipeline_layout_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private static methods --------------------------------------

			/* main layout */
			static auto _main_layout(void) -> vulkan::pipeline_layout {


				// create push constant range
				const vk::push_constant_range range {
					// stage flags
					VK_SHADER_STAGE_FRAGMENT_BIT,
					// offset
					0U,
					// size
					sizeof(float)
				};

				const vk::descriptor_set_layout layouts[] {
					ve::descriptor_set_layout_library::get<"camera">(),
					ve::descriptor_set_layout_library::get<"object">(),
				};

				return vulkan::pipeline_layout{layouts, range};
			}



		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const vk::pipeline_layout& {
				return (ve::get<key>(___self::_shared()._layouts)).get();
			}

	}; // class descriptor_set_layout_library

} // namespace ve

#endif // ___ve_vulkan_descriptor_set_layout_library___
