#ifndef ___ve_skybox___
#define ___ve_skybox___

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/image_view.hpp"
#include "ve/vulkan/sampler.hpp"

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

			/* sampler */
			vk::sampler _sampler;

			/* compute descriptor set */
			vk::descriptor::set _compute_set;

			/* render descriptor set */
			vk::descriptor::set _render_set;



		public:

			// -- public lifecycle --------------------------------------------

			/* extent constructor */
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

			  // create descriptor layout
			  _compute_set{ve::descriptor_set_layout_library::get<"skybox_compute">()},
			  _render_set{ve::descriptor_set_layout_library::get<"skybox_render">()} {


				_compute_set.write(_view.descriptor_image_info(VK_IMAGE_LAYOUT_GENERAL),
								VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);

				_render_set.write(_view.descriptor_image_info(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, _sampler),
								VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
			}


			/* compute */
			auto compute(vulkan::command_buffer& cmd) -> void {

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
				_compute_set.bind(cmd, cl, 0U, VK_PIPELINE_BIND_POINT_COMPUTE);

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
