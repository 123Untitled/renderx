#ifndef ___void_engine_scene___
#define ___void_engine_scene___

#include "ve/camera.hpp"
#include "ve/vulkan/command_buffer.hpp"
#include "ve/vulkan/swapchain_manager.hpp"
#include "ve/object.hpp"
#include "ve/geometry/mesh_library.hpp"
#include "ve/mouse_delta.hpp"

#include "ve/vulkan/descriptor/sets.hpp"
#include "ve/vulkan/descriptor/layout.hpp"
#include "ve/vulkan/descriptor/pool.hpp"
#include "ve/vulkan/descriptor/allocator.hpp"

#include "ve/vulkan/descriptor/descriptor_set_layout_library.hpp"

#include "ve/vulkan/pipeline/library.hpp"

#include "ve/vulkan/pipeline/pipeline_layout_library.hpp"
#include "ve/vulkan/barrier/memory_barrier.hpp"

#include "ve/types.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	class bindable {


		private:


			// -- private members ---------------------------------------------

			/* descriptor sets */
			vk::descriptor::set _set;


	};


	// -- S C E N E -----------------------------------------------------------

	class scene final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::scene;


			// -- private members ---------------------------------------------

			/* **** skybox **** */

			/* extent */
			vk::extent2D _extent;

			/* image */
			ve::image _image;

			/* view */
			ve::image_view _view;



			/* camera */
			ve::camera _camera;

			/* planet */
			ve::object _planet;

			/* uniform buffer */
			ve::uniform_buffer_long<glm::mat4> _ubo;

			std::vector<vk::descriptor::set> _sets;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			scene(const vulkan::swapchain_manager& smanager)
			: _extent{smanager.swapchain().extent()},
			  _image{_extent.width, _extent.height,
					 VK_FORMAT_R32_SFLOAT,
					 VK_SAMPLE_COUNT_1_BIT,
					 VK_IMAGE_TILING_OPTIMAL,
					 VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					 VK_IMAGE_LAYOUT_UNDEFINED,
					 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
			  _view{_image, VK_FORMAT_R32_SFLOAT, VK_IMAGE_ASPECT_COLOR_BIT},

			_camera{},
			  _sets{}

			{
				_planet = ve::object{rx::mesh_library::get<"icosphere">()};

				//_camera.ratio(rx::sdl::window::ratio());
				_camera.update_projection();

				_camera.position().z = -4.0f;
				//_objects[0].scale() = glm::vec3{50.0f, 50.0f, 50.0f};


				//_ubo = ve::uniform_buffer_long<glm::mat4>{1U};
				//_ubo.update(0U, _planet.model());


				// -- set layouts ---------------------------------------------

				_sets.push_back(ve::descriptor_set_layout_library::get<"skybox_compute">());
				//_sets.push_back(ve::descriptor_set_layout_library::get<"planet">());

				// skybox compute
				_sets[0U].write(_view.descriptor_image_info(VK_IMAGE_LAYOUT_GENERAL),
								VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);


				// planet
				//_sets[1U].write(_ubo.descriptor_buffer_info(),
				//				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
			}



			// -- public methods ----------------------------------------------

			/* draw */
			auto draw(const vk::u32 image_index,
					  vulkan::command_buffer& cmd,
					  const vulkan::swapchain_manager& _smanager) -> void {


				// compute skybox
				compute_skybox(cmd);



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

	}; // class scene

} // namespace ve

#endif // ___void_engine_scene___
