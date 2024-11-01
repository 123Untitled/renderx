#ifndef ___ve_heightmap_compute___
#define ___ve_heightmap_compute___

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/image_view.hpp"
#include "ve/vulkan/descriptors/descriptor_pool.hpp"
#include "ve/vulkan/descriptors/descriptor_sets.hpp"
#include "ve/vulkan/descriptors/descriptor_set_layout_library.hpp"
#include "ve/vulkan/pipeline/pipeline_library.hpp"
#include "ve/vulkan/command_buffer.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- H E I G H T M A P  C O M P U T E ------------------------------------

	class heightmap_compute final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::heightmap_compute;


			// -- private members ---------------------------------------------

			/* extent */
			vk::extent2D _extent;

			/* image */
			ve::image _image;

			/* view */
			ve::image_view _view;


			/* descriptor sets */
			vulkan::descriptor_sets _sets;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			heightmap_compute(const vk::u32& width, const vk::u32& height)
			: _extent{width, height},
			  _image{width, height,
					 VK_FORMAT_R32_SFLOAT,
					 VK_SAMPLE_COUNT_1_BIT,
					 VK_IMAGE_TILING_OPTIMAL,
					 VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					 VK_IMAGE_LAYOUT_UNDEFINED,
					 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
			  _view{_image, VK_FORMAT_R32_SFLOAT, VK_IMAGE_ASPECT_COLOR_BIT},
			  _sets{} {

				vulkan::descriptor_pool::builder pbuilder{};

				pbuilder.max_sets(1U);

				// add pool size (heightmap)
				pbuilder.pool_size(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1U);

				_sets = vulkan::descriptor_sets{pbuilder};

				_sets.reserve(1U);

				_sets.push(ve::descriptor_set_layout_library::get<"skybox_heightmap">());

				_sets.write(0U, _view.descriptor_image_info(VK_IMAGE_LAYOUT_GENERAL), VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
			}


			/* render */
			auto render(vulkan::command_buffer& cmd) -> void {

				// get compute pipeline
				const auto& cp = ve::pipeline_library::get<"skybox_heightmap_compute">();
				const auto& cl = ve::pipeline_layout_library::get<"skybox_heightmap">();


				// image general barrier
				const vk::image_memory_barrier imb{
					// structure type
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					// next structure
					.pNext = nullptr,
					// source access mask
					.srcAccessMask = VK_ACCESS_NONE,
					// destination access mask
					.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT,
					// old layout
					.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					// new layout
					.newLayout = VK_IMAGE_LAYOUT_GENERAL,
					// source queue family index
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					// destination queue family index
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					// image
					.image = _image,
					// subresource range
					.subresourceRange = {
						// aspect mask
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						// base mip level
						.baseMipLevel = 0U,
						// level count
						.levelCount = 1U,
						// base array layer
						.baseArrayLayer = 0U,
						// layer count
						.layerCount = 1U
					}
				};

				// barrier
				cmd.pipeline_barrier(VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, 0U, 0U, nullptr, 0U, nullptr, 1U, &imb);

				// bind compute pipeline
				cmd.bind_compute_pipeline(cp);

				// bind descriptor sets
				cmd.bind_compute_descriptor_sets(cl, 0U, 1U, &_sets[0]);

				// group x
				const vk::u32 gx = (_extent.width + 15U) / 16U;
				// group y
				const vk::u32 gy = (_extent.height + 15U) / 16U;

				// dispatch
				cmd.dispatch(gx, gy, 1U);


				// image read barrier
				const vk::image_memory_barrier imb2{
					// structure type
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					// next structure
					.pNext = nullptr,
					// source access mask
					.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT,
					// destination access mask
					.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
					// old layout
					.oldLayout = VK_IMAGE_LAYOUT_GENERAL,
					// new layout
					.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					// source queue family index
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					// destination queue family index
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					// image
					.image = _image,
					// subresource range
					.subresourceRange = {
						// aspect mask
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						// base mip level
						.baseMipLevel = 0U,
						// level count
						.levelCount = 1U,
						// base array layer
						.baseArrayLayer = 0U,
						// layer count
						.layerCount = 1U
					}
				};


				// barrier
				cmd.pipeline_barrier(VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0U, 0U, nullptr, 0U, nullptr, 1U, &imb2);

			}


	}; // class heightmap_compute

} // namespace ve

#endif // ___ve_heightmap_compute___
