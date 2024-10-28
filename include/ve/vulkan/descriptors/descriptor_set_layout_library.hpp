#ifndef ___void_engine_vulkan_descriptor_set_layout_library___
#define ___void_engine_vulkan_descriptor_set_layout_library___

#include "ve/containers/static_map.hpp"
#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"


// -- V E ---------------------------------------------------------------------

namespace ve {


	// -- D E S C R I P T O R  S E T  L A Y O U T  L I B R A R Y --------------

	class descriptor_set_layout_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::descriptor_set_layout_library;


			// -- private members ---------------------------------------------

			ve::static_map<vulkan::descriptor_set_layout,
				"main"> _layouts;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			descriptor_set_layout_library(void)
			: _layouts{} {

				vulkan::descriptor_set_layout::builder builder;

				builder.add_binding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
									   VK_SHADER_STAGE_VERTEX_BIT
									| VK_SHADER_STAGE_FRAGMENT_BIT);

				ve::get<"main">(_layouts) = builder.build();
			}

			/* deleted copy constructor */
			descriptor_set_layout_library(const ___self&) = delete;

			/* deleted move constructor */
			descriptor_set_layout_library(___self&&) = delete;

			/* destructor */
			~descriptor_set_layout_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const vk::descriptor_set_layout& {
				return ve::get<key>(_shared()._layouts).get();
			}

	}; // class descriptor_set_layout_library

} // namespace ve

#endif // ___void_engine_vulkan_descriptor_set_layout_library___
