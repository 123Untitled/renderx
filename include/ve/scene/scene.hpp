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
#include "ve/vulkan/descriptors/descriptor_set_layout_library.hpp"

#include "ve/types.hpp"


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
			ve::camera _camera;

			/* pipeline */
			vulkan::pipeline _pipeline;

			/* objects */
			std::vector<rx::object> _objects;

			/* descriptor sets */
			vulkan::descriptor_sets _sets[3U];

			/* uniform buffer */
			ve::uniform_buffer_long<glm::mat4> _ubo[3U];

			/* uniform buffer */
			ve::uniform_buffer _ubo_cam[3U];


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			scene(const vulkan::swapchain_manager& _smanager)
			: _camera{},
			  _pipeline{
				  vulkan::pipeline_builder<ve::vert3x>::build(
						  _smanager.render_pass())}
			{
				// add cube object
				//_objects.emplace_back(rx::mesh_library::get<"fibonacci_sphere">());
				_objects.emplace_back(rx::mesh_library::get<"icosphere">());

				//_camera.ratio(rx::sdl::window::ratio());
				_camera.projection().fov(70.0f);
				_camera.update_projection();

				_camera.position().z = -6.0f;


				for (vk::u32 i = 0U; i < 3U; ++i) {
					_ubo[i] = ve::uniform_buffer_long<glm::mat4>{(vk::u32)_objects.size()};
					_ubo_cam[i] = ve::uniform_buffer{_camera.uniform()};
				}


				for (vk::u32 x = 0U; x < 3U; ++x) {
					for (vk::u32 i = 0U; i < (vk::u32)_objects.size(); ++i) {
						_ubo[x].update(i, _objects[i].model());
					}
					_ubo_cam[x].update(_camera.uniform());
				}
					//for (vk::u32 i = 0U; i < (vk::u32)_objects.size(); ++i) {
					//	_ubo.update(i, _objects[i].model());
					//}


				// -- descriptor sets -----------------------------------------

				for (vk::u32 x = 0U; x < 3U; ++x) {
					// create descriptor pool
					vulkan::descriptor_pool::builder pbuilder{};

					pbuilder.max_sets(2U);

					// add pool size (camera)
					pbuilder.pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1U);
					// add pool size (objects)
					pbuilder.pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1U);

					// create descriptor sets
					_sets[x] = vulkan::descriptor_sets{pbuilder};

					_sets[x].reserve(2U);

					_sets[x].push(ve::descriptor_set_layout_library::get<"camera">());
					_sets[x].push(ve::descriptor_set_layout_library::get<"object">());

					_sets[x].write(0U, _ubo_cam[x].descriptor_buffer_info(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
					_sets[x].write(1U, _ubo[x].descriptor_buffer_info(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
				}

				std::cout << "\x1b[32mSCENE INITIALIZED\x1b[0m" << std::endl;
				//throw std::runtime_error{"scene init"};

			}



			// -- public methods ----------------------------------------------

			/* draw */
			auto draw(const vk::u32 image_index,
					  vulkan::command_buffer<vulkan::primary>& cmd,
					  const vulkan::swapchain_manager& _smanager) -> void {


				_camera.update_rotation(ve::mouse_delta::dx(), ve::mouse_delta::dy());
				_camera.update();
				_ubo_cam[image_index].update(_camera.uniform());


				_objects[0].rotation().y += 0.26f * ve::delta::time();
				_objects[0].rotation().x += 0.04f * ve::delta::time();
				_objects[0].rotation().z += 0.02f * ve::delta::time();


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
				cmd.set_scissor(swapchain.extent());

				// bind pipeline
				cmd.bind_pipeline(_pipeline);

				// bind camera descriptor
				cmd.bind_descriptor_sets(
						_pipeline.layout(),
						_sets[image_index][0U]);



				{ // -- for each mesh -----------------------------------------------------

					for (ve::u32 i = 0U; i < (ve::u32)_objects.size(); ++i) {

						// update object
						_objects[i].update();

						// update uniform buffer
						_ubo[image_index].update(i, _objects[i].model());


						auto offset = _ubo[image_index].alignment(i);

						cmd.bind_descriptor_sets(
								_pipeline.layout(),
								// first set
								1U, // set in layout shader
								// descriptor set count
								1U,
								// descriptor sets
								&_sets[image_index][1U],
								// dynamic offset count
								1U,
								// dynamic offsets
								&offset);




						// bind vertex buffer
						cmd.bind_vertex_buffer(_objects[i].mesh().vertices());

						// bind index buffer
						cmd.bind_index_buffer(_objects[i].mesh().indices());



						// draw indexed
						cmd.draw_indexed(_objects[i].mesh().indices().count());
					}
				}

				//throw std::runtime_error{"scene draw"};

			}

	}; // class scene

} // namespace ve

#endif // ___void_engine_scene___
