#ifndef ___ve_skybox___
#define ___ve_skybox___

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/image_view.hpp"
#include "ve/vulkan/descriptor/descriptor_set_layout_library.hpp"

#include "ve/vulkan/descriptor/pool.hpp"
#include "ve/vulkan/descriptor/set.hpp"
#include "ve/vulkan/descriptor/sets.hpp"
#include "ve/vulkan/descriptor/layout.hpp"


#include "ve/vulkan/pipeline/library.hpp"
#include "ve/vulkan/command_buffer.hpp"

#include "ve/vulkan/pipeline/pipeline_layout_library.hpp"

#include "ve/vulkan/barrier/memory_barrier.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S K Y B O X ---------------------------------------------------------

	class skybox final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::skybox;


			// -- private members ---------------------------------------------

			/* extent */
			vk::extent2D _extent;

			/* image */
			ve::image _image;

			/* view */
			ve::image_view _view;


			/* descriptor sets */
			vk::descriptor::sets _sets;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			skybox(const vk::extent2D& extent)
			: _extent{extent},
			  _image{extent.width, extent.height,
					 VK_FORMAT_R32_SFLOAT,
					 VK_SAMPLE_COUNT_1_BIT,
					 VK_IMAGE_TILING_OPTIMAL,
					 VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					 VK_IMAGE_LAYOUT_UNDEFINED,
					 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
			  _view{_image, VK_FORMAT_R32_SFLOAT, VK_IMAGE_ASPECT_COLOR_BIT},
			  _sets{} {


				// build descriptor sets (with pool)
				_sets = vk::descriptor::sets{
					vk::descriptor::pool::builder{}
					.max_sets(2U)
					.pool_size(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1U)
					.pool_size(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1U)
					.pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1U)};


				_sets.reserve(2U);

				// new layout builder
				vk::descriptor::set::layout::builder lbuilder;

				/*
				// construct compute layout
				lbuilder.binding(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
								 VK_SHADER_STAGE_COMPUTE_BIT);

				// new compute layout
				auto compute_layout = lbuilder.build();

				// reset layout builder
				lbuilder.reset();
				*/

				// construct render layout
				lbuilder.binding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
								 VK_SHADER_STAGE_FRAGMENT_BIT)
						.binding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
								 VK_SHADER_STAGE_VERTEX_BIT);

				// new render layout
				auto render_layout = lbuilder.build();


				_sets.push(ve::descriptor_set_layout_library::get<"skybox_compute">());
				_sets[0U].write(_view.descriptor_image_info(VK_IMAGE_LAYOUT_GENERAL),
								VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);

				//_sets.push(render_layout);
				//_sets[1U].write(_view.descriptor_image_info(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL),
				//				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
			}


			/* render */
			auto render(vulkan::command_buffer& cmd) -> void {

				// get compute pipeline
				const auto& cp = vk::pipeline::library::get<"skybox_compute">();
				const auto& cl = vk::pipeline_layout_library::get<"skybox_compute">();


				// image write barrier
				ve::memory_barrier::image imb {
					VK_ACCESS_NONE,
					VK_ACCESS_SHADER_WRITE_BIT,
					VK_IMAGE_LAYOUT_UNDEFINED,
					VK_IMAGE_LAYOUT_GENERAL,
					_image,
					VK_IMAGE_ASPECT_COLOR_BIT
				};

				// barrier
				imb.pipeline_barrier(cmd,
						VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);

				// bind compute pipeline
				cmd.bind_compute_pipeline(cp);

				// bind descriptor sets
				cmd.bind_compute_descriptor_sets(cl, 0U, 1U, _sets.data());

				// group x
				const vk::u32 gx = (_extent.width + 15U) / 16U;
				// group y
				const vk::u32 gy = (_extent.height + 15U) / 16U;

				// dispatch
				cmd.dispatch(gx, gy, 1U);

				// transition to read only
				imb.access_masks(VK_ACCESS_SHADER_WRITE_BIT,
								 VK_ACCESS_SHADER_READ_BIT)
				   .layouts(VK_IMAGE_LAYOUT_GENERAL,
						    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

				// barrier
				imb.pipeline_barrier(cmd,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
						VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
			}

	}; // class skybox

} // namespace ve

#endif // ___ve_skybox___
