#ifndef ___void_engine_vulkan_descriptor_sets___
#define ___void_engine_vulkan_descriptor_sets___

#include "ve/vk/typedefs.hpp"
#include "ve/memory/malloc.hpp"

#include "ve/vulkan/descriptors/descriptor_pool.hpp"
#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"

#include <stdexcept>


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  S E T S ----------------------------------------

	class descriptor_sets final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_sets;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vulkan::descriptor_pool _pool;

			/* descriptor sets */
			vk::descriptor_set* _sets;


		public:

			// -- public lifecycle --------------------------------------------

			/* device and size constructor */
			descriptor_sets(const vulkan::descriptor_set_layout& layout,
							const vk::u32& size = 1U)
			: _pool{size}, _sets{nullptr} {


				vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool.get(), // descriptor pool
					.descriptorSetCount = size, // swapchain size
					.pSetLayouts = &layout.get() // descriptor set layout
				};

				// allocate descriptor sets
				_sets = rx::malloc<vk::descriptor_set>(size);


				// create descriptor sets
				vk::try_execute<"failed to allocate descriptor sets">(
						::vkAllocateDescriptorSets,
						vulkan::device::logical(),
						&info, _sets);



				for (vk::u32 i = 0U; i < size; ++i) {

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

					vkUpdateDescriptorSets(
							vulkan::device::logical(),
							1U, &wdset, 0U, nullptr);
				}
			}


	}; // class descriptor_sets

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_sets___
