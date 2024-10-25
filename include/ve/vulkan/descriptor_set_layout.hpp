#ifndef ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___
#define ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___

#include "ve/vk/utils.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  S E T  L A Y O U T -----------------------------

	class descriptor_set_layout final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_set_layout;


			// -- private members ---------------------------------------------

			/* descriptor set layout */
			vk::descriptor_set_layout _layout;


		public:

			// -- public lifecycle --------------------------------------------

			/* device constructor */
			descriptor_set_layout(void)
			: _layout{___self::_create_descriptor_set_layout()} {
			}

			/* deleted copy constructor */


		private:

			// -- private static methods --------------------------------------

			/* create descriptor set layout */
			static auto _create_descriptor_set_layout(void) -> vk::descriptor_set_layout {

				const vk::descriptor_set_layout_binding binding{
					// binding in shader
					.binding = 0U,
					// type of descriptor
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					// may be an array in shader, so descriptorCount define how many
					.descriptorCount = 1U,
					// stage where the descriptor is going to be used
					.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
					// used for texture sampling
					.pImmutableSamplers = nullptr
				};

				const vk::descriptor_set_layout_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0U,
					.bindingCount = 1U,
					.pBindings = &binding
				};

				vk::descriptor_set_layout layout;

				// create layout
				vk::try_execute<"failed to create descriptor set layout">(
						::vkCreateDescriptorSetLayout,
						vulkan::device::logical(),
						&info, nullptr, &layout);

				return layout;
			}

	}; // class descriptor_set_layout

} // namespace vulkan

#endif // ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___
