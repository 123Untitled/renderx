#ifndef ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___
#define ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___

#include "engine/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	//// -- D E S C R I P T O R  S E T  L A Y O U T -----------------------------
	//
	//class descriptor_set_layout final {
	//
	//
	//	private:
	//
	//		// -- private types -----------------------------------------------
	//
	//		/* self type */
	//		using ___self = vulkan::descriptor_set_layout;
	//
	//
	//		// -- private members ---------------------------------------------
	//
	//		/* device */
	//		vk::shared<vk::device> _device;
	//
	//		/* descriptor set layout */
	//		vk::descriptor_set_layout _layout;
	//
	//
	//	public:
	//
	//		// -- public lifecycle --------------------------------------------
	//
	//		/* device constructor */
	//		descriptor_set_layout(const vk::shared<vk::device>& ___dev)
	//		: _device{___dev},
	//		  _layout{___self::_create_descriptor_set_layout(_device.underlying())} {
	//		}
	//
	//
	//	private:
	//
	//		// -- private static methods --------------------------------------
	//
	//		/* create descriptor set layout */
	//		static auto _create_descriptor_set_layout(const vk::device& ___dev) -> vk::descriptor_set_layout {
	//
	//			vk::descriptor_set_layout_binding binding{
	//				// binding in shader
	//				.binding = 0U,
	//				// type of descriptor
	//				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	//				// may be an array in shader, so descriptorCount define how many
	//				.descriptorCount = 1U,
	//				// stage where the descriptor is going to be used
	//				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	//				// used for texture sampling
	//				.pImmutableSamplers = nullptr
	//			};
	//
	//			const vk::descriptor_set_layout_info info{
	//				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	//				.pNext = nullptr,
	//				.flags = 0U,
	//				.bindingCount = 1U,
	//				.pBindings = &binding
	//			};
	//
	//			// create layout
	//			return vk::create(___dev, info);
	//		}
	//
	//}; // class descriptor_set_layout

} // namespace vulkan

#endif // ___RENDERX_VULKAN_DESCRIPTOR_SET_LAYOUT___
