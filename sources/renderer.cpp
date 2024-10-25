/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "ve/renderer.hpp"
#include "ve/time/delta.hpp"
#include "ve/running.hpp"
#include "ve/glfw/monitor.hpp"
#include "ve/geometry/mesh_library.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
rx::renderer::renderer(void)
:
	_queue{},
	_smanager{},

	_pool{VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT},
	_cmds{_pool.underlying(), _smanager.size()},
	
	_pipeline{
		vulkan::pipeline_builder<vertex_type>::build(
				_smanager.render_pass().underlying())
	},

	_memory{},
	_sync{},
	_objects{},
	_camera{}
{

	// add cube object
	//_objects.emplace_back(rx::mesh_library::get<"fibonacci_sphere">());
	_objects.emplace_back(rx::mesh_library::get<"icosphere">());

	//_camera.ratio(rx::sdl::window::ratio());
	_camera.fov(70.0f);
	_camera.update_projection();

	_camera.transform().position().z = -6.0f;

	//glfw::monitor m;
}

namespace rx {


	class mouse_delta final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::mouse_delta;


			/* mouse position */
			double _lx, _ly;

			/* mouse delta */
			double _dx, _dy;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self ___ins;
				return ___ins;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			mouse_delta(void) noexcept
			: _lx{0.0}, _ly{0.0},
			  _dx{0.0}, _dy{0.0} {
			}

		public:

			/* update */
			static auto update(void) noexcept -> void {

				___self& ins = ___self::_shared();

				double cx, cy;

				// retrieve position
				::glfw_get_cursor_pos(&glfw::window::shared(),
						&cx, &cy);

				ins._dx = cx - ins._lx;
				ins._dy = cy - ins._ly;

				// update last known position
				ins._lx = cx;
				ins._ly = cy;

				//if (ins._dx != 0.0 || ins._dy != 0.0)
				//	std::cout << "dx: " << ins._dx << " dy: " << ins._dy << std::endl;
			}

			/* dx */
			static auto dx(void) noexcept -> double {
				return ___self::_shared()._dx;
			}

			/* dy */
			static auto dy(void) noexcept -> double {
				return ___self::_shared()._dy;
			}

	}; // class mouse_delta

} // namespace rx


// -- public methods ----------------------------------------------------------

/* run */
auto rx::renderer::run(void) -> void {

	rx::umax last = rx::now();

	static vk::u32 i = 0U;

	while (rx::running::state() == true &&
		 glfw::window::should_close() == false) {

		rx::delta::update();
		// poll events
		glfw::events::poll();

		// get current time (nanoseconds)
		//rx::umax now = rx::now();

		//glfw::compute_to_mouse_delta(_camera);

		rx::mouse_delta::update();
		_camera.from_tap_event(rx::mouse_delta::dx(),
							   rx::mouse_delta::dy());


		// compute fps
		//float fps = 1.0f / rx::delta::time<float>();

		//usleep(1'000'000 / 60);

		_objects[0].rotation().y += 0.04f * rx::delta::time<float>();
		_objects[0].rotation().x += 0.02f * rx::delta::time<float>();
		_objects[0].rotation().z += 0.01f * rx::delta::time<float>();

		//std::cout << "delta: " << rx::delta::time<float>() << " fps: " << fps << std::endl;

		//last = now;

		___self::_draw_frame();
		_camera.update();

		// limit to 120 fps
		//usleep(1'000'000 / 120);

		//std::cout << "--------------- draw frame [" << i++ << "] ---------------" << std::endl;
	}

	// wait for logical device to be idle
	vulkan::device::wait_idle();
}

auto rx::renderer::test(void) -> void {

	while (rx::running::state() == true) {


		_camera.update();

		// draw frame
		_draw_frame();
	}
}

/* draw frame */
auto rx::renderer::_draw_frame(void) -> void {

	// wait for current fence
	_sync.wait_current_fence();

	vk::u32 image_index = 0U;

	const auto& swapchain = _smanager.swapchain();

	// here error not means program must stop
	const vk::result status = swapchain.acquire_next_image(_sync.image_available(),
															image_index);

	if (status == VK_ERROR_OUT_OF_DATE_KHR) {

		std::cout << "recreating swapchain (after acquire)" << std::endl;

		auto extent = glfw::window::framebuffer_size();
		_camera.ratio((float)extent.width / (float)extent.height);
		_camera.update_projection();
		_smanager.recreate();
		return; // maybe goto start of the function ?
	}
	else if (status != VK_SUCCESS && status != VK_SUBOPTIMAL_KHR) {
		throw vk::exception{"failed to acquire next image", status};
	}


	auto& cmd = _cmds[image_index];

	// record command buffer (see flagbits)
	cmd.reset();


	// -- record command buffer -----------------------------------------------

	// start recording
	cmd.begin();

	const auto& render_pass = _smanager.render_pass();
	const auto& frames = _smanager.frames();

	// begin render pass
	cmd.begin_render_pass(swapchain,
						  render_pass,
						  frames[image_index]);

	// dynamic viewport
	cmd.set_viewport(swapchain);

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
			cmd.push_constants(_pipeline,
					pc);
					//_camera.projection() *
					//_camera.view() *
					//object.model());

			// draw indexed
			cmd.draw_indexed(object.mesh().indices().count());
		}
	}

	// end render pass
	cmd.end_render_pass();

	// end recording
	cmd.end();

	// -- submit command buffer -----------------------------------------------

	// reset fence
	_sync.reset_current_fence();

	// submit command buffers
	_queue.submit(_sync.image_available(),
				  _sync.render_finished(),
				  _sync.fence(),
				  cmd);

	// here error not means program must stop
	const vk::result state = _queue.present(swapchain, image_index,
											_sync.render_finished());

	if (status == VK_ERROR_OUT_OF_DATE_KHR
	  || status == VK_SUBOPTIMAL_KHR
	  || glfw::window::resized() == true) {

		std::cout << "recreating swapchain (after present)" << std::endl;

		auto extent = glfw::window::framebuffer_size();
		_camera.ratio((float)extent.width / (float)extent.height);
		_camera.update_projection();

		// recreate swapchain
		_smanager.recreate();
	}
	else if (state != VK_SUCCESS) {
		throw vk::exception{"failed to queue present", state};
	}

	//std::cout << "draw frame" << std::endl;

	// next frame
	++_sync;
}


// this for when swapchain image number is inferior to MAX_FRAMES_IN_FLIGHT
// Vérifier si une frame précédente est en train d'utiliser cette image (il y a une fence à attendre)
//if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
//	vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
//}
