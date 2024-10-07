#ifndef ___RENDERX_VULKAN_DESCRIPTOR_SETS___
#define ___RENDERX_VULKAN_DESCRIPTOR_SETS___

#include "engine/vk/typedefs.hpp"
#include "engine/vk/shared.hpp"
#include "engine/memory/malloc.hpp"

#include "engine/vulkan/descriptor_pool.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  S E T S ----------------------------------------

	class descriptor_sets final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_sets;


			// -- private members ---------------------------------------------

			/* device */
			vk::shared<vk::device> _device;

			/* descriptor pool */
			vulkan::descriptor_pool _pool;

			/* descriptor sets */
			vk::descriptor_set* _sets;


		public:

			// -- public lifecycle --------------------------------------------

			/* device and size constructor */
			descriptor_sets(vk::shared<vk::device>& ___dev, vk::u32 ___size)
			: _device{___dev}, _pool{___dev, ___size}, _sets{nullptr} {


				vk::descriptor_set_layout dsl{
					// layout
				};

				vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = nullptr, // pool,
					.descriptorSetCount = ___size, // swapchain size
					.pSetLayouts = &dsl
				};

				// allocate descriptor sets
				_sets = rx::malloc<vk::descriptor_set>(___size);


				if (vkAllocateDescriptorSets(_device.underlying(), &info, _sets) != VK_SUCCESS) {
					throw std::runtime_error("failed to allocate descriptor sets!");
				}


				for (vk::u32 i = 0U; i < ___size; ++i) {

					vk::descriptor_buffer_info buffer_info{
						.buffer = nullptr, // buffer
						.offset = 0U,
						.range = sizeof(0/* must be size of uniform buffer object or struct */) // can be VK_WHOLE_SIZE
					};

					vk::write_descriptor_set wdset{
						.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
						.pNext = nullptr,
						.dstSet = _sets[i], // descriptor set
						.dstBinding = 0U,
						.dstArrayElement = 0U,
						.descriptorCount = 1U,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImageInfo = nullptr,
						.pBufferInfo = &buffer_info,
						.pTexelBufferView = nullptr
					};

					vkUpdateDescriptorSets(_device.underlying(), 1U, &wdset, 0U, nullptr);
				}
			}





	}; // class descriptor_sets

} // namespace vulkan

#endif // ___RENDERX_VULKAN_DESCRIPTOR_SETS___
