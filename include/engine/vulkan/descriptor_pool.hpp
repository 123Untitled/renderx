#ifndef ___RENDERX_VULKAN_DESCRIPTOR_POOL___
#define ___RENDERX_VULKAN_DESCRIPTOR_POOL___

#include "engine/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	//// -- D E S C R I P T O R  P O O L ----------------------------------------
	//
	//class descriptor_pool final {
	//
	//
	//	private:
	//
	//		// -- private types -----------------------------------------------
	//
	//		/* self type */
	//		using ___self = vulkan::descriptor_pool;
	//
	//
	//		// -- private members ---------------------------------------------
	//
	//		/* device */
	//		vk::shared<vk::device> _device;
	//
	//		/* descriptor pool */
	//		vk::descriptor_pool _pool;
	//
	//
	//	public:
	//
	//		// -- public lifecycle --------------------------------------------
	//
	//		/* device and size constructor */
	//		descriptor_pool(const vk::shared<vk::device>& ___dev, const vk::u32& ___size)
	//		: _device{___dev},
	//		  _pool{___self::_create_descriptor_pool(_device.underlying(), ___size)} {
	//
	//			// INFO:
	//			// recreate pool when swapchain is recreated
	//		}
	//
	//
	//	private:
	//
	//		// -- private static methods --------------------------------------
	//
	//		/* create descriptor pool */
	//		static auto _create_descriptor_pool(const vk::device& ___dev, const vk::u32& ___size) -> vk::descriptor_pool {
	//
	//			// pool size
	//			vk::descriptor_pool_size pool_size{
	//				.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	//				.descriptorCount = ___size
	//			};
	//
	//			// pool info
	//			vk::descriptor_pool_info pool_info{
	//				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
	//				.pNext = nullptr,
	//				.flags = 0U,
	//				.maxSets = ___size,
	//				.poolSizeCount = 1U,
	//				.pPoolSizes = &pool_size
	//			};
	//
	//			// create descriptor pool
	//			return vk::create(___dev, pool_info);
	//		}
	//
	//}; // class descriptor_pool

} // namespace vulkan

#endif // ___RENDERX_VULKAN_DESCRIPTOR_POOL___
