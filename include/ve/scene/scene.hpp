#ifndef ___void_engine_scene___
#define ___void_engine_scene___

#include "ve/camera.hpp"
#include "ve/skybox.hpp"

#include "ve/vulkan/command_buffer.hpp"
#include "ve/vulkan/swapchain_manager.hpp"
#include "ve/object.hpp"

#include "ve/geometry/mesh_library.hpp"

#include "ve/mouse_delta.hpp"

#include "ve/vulkan/pipeline/library.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S C E N E -----------------------------------------------------------

	class scene final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::scene;


			// -- private members ---------------------------------------------

			/* skybox */
			ve::skybox _skybox;

			/* camera */
			ve::camera _camera;

			/* planet */
			ve::object _planet;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			scene(const vk::extent2D& extent)
			: _skybox{extent},
			  _camera{},
			  _planet{} {


				_planet = ve::object{rx::mesh_library::get<"icosphere">()};

				_camera.update_projection();
				_camera.position().z = -2.0f;
			}



			// -- public methods ----------------------------------------------

			/* draw */
			auto draw(const vk::u32 image_index,
					  vulkan::command_buffer& cmd,
					  const vulkan::swapchain_manager& _smanager) -> void {


				// compute skybox
				_skybox.compute(cmd);



				update();



				// -- begin render pass ---------------------------------------

				const auto& swapchain   = _smanager.swapchain();
				const auto& render_pass = _smanager.render_pass();
				const auto& frames      = _smanager.frames();

				// begin render pass
				cmd.begin_render_pass(swapchain.extent(),
									  render_pass,
									  frames[image_index]);

				// dynamic viewport
				cmd.set_viewport_and_scissor(swapchain.extent());

				// bind pipeline
				cmd.bind_graphics_pipeline(
						vk::pipeline::library::get<"planet">());


				// -- render --------------------------------------------------

				// bind camera descriptor
				_camera.render(cmd, vk::pipeline_layout_library::get<"main">());
				_planet.render(cmd, vk::pipeline_layout_library::get<"main">());


				// end render pass
				cmd.end_render_pass();
			}

			/* update */
			auto update(void) -> void {

				_camera.update_rotation(ve::mouse_delta::dx(), ve::mouse_delta::dy());
				_camera.update();

				_planet.rotation().x += 0.08f * ve::delta::time();
				_planet.update();
			}


			/* compute skybox */
			/*
			auto compute_skybox(vulkan::command_buffer& cmd) -> void {

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
				cmd.bind_compute_pipeline(
						vk::pipeline::library::get<"skybox_compute">());

				::vk_descriptor_set set = *_sets.data();

				// bind descriptor sets
				cmd.bind_compute_descriptor_sets(
						vk::pipeline_layout_library::get<"skybox_compute">(),
						0U, 1U, &set);

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
			*/

	}; // class scene

} // namespace ve

#endif // ___void_engine_scene___
