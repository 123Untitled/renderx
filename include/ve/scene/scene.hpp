#ifndef ___void_engine_scene___
#define ___void_engine_scene___

#include "ve/camera.hpp"
#include "ve/vulkan/command_buffer.hpp"
#include "ve/vulkan/swapchain_manager.hpp"
#include "ve/object.hpp"
#include "ve/geometry/mesh_library.hpp"
#include "ve/mouse_delta.hpp"
#include "ve/vulkan/descriptors/descriptor_sets.hpp"
#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"
#include "ve/vulkan/descriptors/descriptor_pool.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S C E N E -----------------------------------------------------------

	class scene final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::scene;


			// -- private members ---------------------------------------------

			/* camera */
			rx::camera _camera;

			/* pipeline */
			vulkan::pipeline _pipeline;

			/* objects */
			std::vector<rx::object> _objects;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			scene(const vulkan::swapchain_manager& _smanager)
			: _camera{},
			  _pipeline{
				  vulkan::pipeline_builder<ve::vert3x>::build(
						  _smanager.render_pass().underlying())}
			{
				// add cube object
				//_objects.emplace_back(rx::mesh_library::get<"fibonacci_sphere">());
				_objects.emplace_back(rx::mesh_library::get<"icosphere">());

				//_camera.ratio(rx::sdl::window::ratio());
				_camera.fov(70.0f);
				_camera.update_projection();

				_camera.transform().position().z = -6.0f;

				// create descriptor set layout
				//vulkan::descriptor_set_layout::builder builder{};
				//
				//// add binding
				//builder.add_binding(0U, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, 1U);
				//
				//// build layout
				//auto layout = builder.build();
				//
				//// create descriptor pool
				//vulkan::descriptor_pool::builder pool_builder{};
				//
				//// add pool size
				//pool_builder.add_pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1U);
				//
				//// build pool
				//auto pool = pool_builder.build();
				//
				//// create descriptor sets
				//vulkan::descriptor_sets sets{};
				//
				//// reserve
				//sets.reserve(1U);
				//
				//// push
				//sets.push(layout); // it misses the uniform buffer

			}



			// -- public methods ----------------------------------------------

			/* draw */
			auto draw(const vk::u32 image_index,
					  vulkan::command_buffer<vulkan::primary>& cmd,
					  const vulkan::swapchain_manager& _smanager) -> void {


				_camera.from_tap_event(ve::mouse_delta::dx(),
									   ve::mouse_delta::dy());
				_camera.update();

				_objects[0].rotation().y += 0.04f * rx::delta::time<float>();
				_objects[0].rotation().x += 0.02f * rx::delta::time<float>();
				_objects[0].rotation().z += 0.01f * rx::delta::time<float>();




				const auto& swapchain = _smanager.swapchain();
				const auto& render_pass = _smanager.render_pass();
				const auto& frames = _smanager.frames();

				// begin render pass
				cmd.begin_render_pass(swapchain,
						render_pass,
						frames[image_index]);

				// dynamic viewport
				cmd.set_viewport(swapchain.extent());

				// dynamic scissor
				cmd.set_scissor(swapchain);


				struct push_constants {
					glm::mat4 model;
					glm::mat4 view;
					glm::mat4 projection;
					glm::vec3 camera_position;
				};

				static push_constants pc;


				{ // -- for each mesh -----------------------------------------------------

					for (const auto& object : _objects) {

						// bind pipeline
						cmd.bind_pipeline(_pipeline);

						// bind vertex buffer
						cmd.bind_vertex_buffer(object.mesh().vertices());

						// bind index buffer
						cmd.bind_index_buffer(object.mesh().indices());


						pc.model = object.model();
						pc.view = _camera.view();
						pc.projection = _camera.projection();
						pc.camera_position = _camera.transform().position();


						// push constants
						cmd.push_constants(_pipeline, pc);

						// draw indexed
						cmd.draw_indexed(object.mesh().indices().count());
					}
				}

			}

	}; // class scene

} // namespace ve

#endif // ___void_engine_scene___
