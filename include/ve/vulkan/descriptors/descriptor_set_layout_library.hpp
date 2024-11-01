#ifndef ___ve_vulkan_descriptor_set_layout_library___
#define ___ve_vulkan_descriptor_set_layout_library___

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
				"camera", "object", "skybox_heightmap"> _layouts;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			descriptor_set_layout_library(void)
			: _layouts{
				___self::_camera_layout(),
				___self::_object_layout(),
				___self::_skybox_heightmap()} {
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


			// -- private static methods --------------------------------------

			/* camera layout */
			static auto _camera_layout(void) -> vulkan::descriptor_set_layout {

				const vk::descriptor_set_layout_binding binding[1U]{
					{
						// binding
						.binding = 0U,
						// type
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						// count
						.descriptorCount = 1U,
						// stage
						//.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
						.stageFlags =  VK_SHADER_STAGE_VERTEX_BIT
							//| VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT
							| VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
						// immutable samplers
						.pImmutableSamplers = nullptr
					}
				};


				return vulkan::descriptor_set_layout{binding};
			}

			/* object layout */
			static auto _object_layout(void) -> vulkan::descriptor_set_layout {

				const vk::descriptor_set_layout_binding binding[1U]{
					{
						// binding
						.binding = 0U,
						// type
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
						// count
						.descriptorCount = 1U,
						// stage
						//.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
						.stageFlags =  VK_SHADER_STAGE_VERTEX_BIT
									//| VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT
									| VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
						// immutable samplers
						.pImmutableSamplers = nullptr
					}
				};

				return vulkan::descriptor_set_layout{binding};
			}

			/* skybox heightmap layout */
			static auto _skybox_heightmap(void) -> vulkan::descriptor_set_layout {

				const vk::descriptor_set_layout_binding binding[1U]{
					{
						// binding
						.binding = 0U,
						// type
						.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, // use for writing to image (heightmap)
						// count
						.descriptorCount = 1U,
						// stage
						.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
						// immutable samplers
						.pImmutableSamplers = nullptr
					}
				};

				return vulkan::descriptor_set_layout{binding};
			}


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const vk::descriptor_set_layout& {
				return (ve::get<key>(___self::_shared()._layouts)).get();
			}

	}; // class descriptor_set_layout_library

} // namespace ve

#endif // ___ve_vulkan_descriptor_set_layout_library___
