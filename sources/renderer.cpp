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
#include "ve/mouse_delta.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::renderer::renderer(void)
:
	_queue{},
	_smanager{},
	_pool{VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT},
	_cmds{_pool.get(), _smanager.size()},
	_memory{},
	_sync{},
	_scene{_smanager} {
}



// -- public methods ----------------------------------------------------------

/* run */
auto ve::renderer::run(void) -> void {

	rx::umax last = rx::now();

	static vk::u32 i = 0U;

	// game loop
	while (rx::running::state() == true &&
			glfw::window::should_close() == false) {

		rx::delta::update();

		// poll events
		glfw::events::poll();

		ve::mouse_delta::update();

		// get current time (nanoseconds)
		//rx::umax now = rx::now();

		//glfw::compute_to_mouse_delta(_camera);




		// compute fps
		//float fps = 1.0f / rx::delta::time<float>();

		//usleep(1'000'000 / 60);


		//std::cout << "delta: " << rx::delta::time<float>() << " fps: " << fps << std::endl;

		//last = now;

		___self::_draw_frame();

		// limit to 120 fps
		//usleep(1'000'000 / 120);

		//std::cout << "--------------- draw frame [" << i++ << "] ---------------" << std::endl;
	}

	// wait for logical device to be idle
	vulkan::device::wait_idle();
}


/* draw frame */
auto ve::renderer::_draw_frame(void) -> void {

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
		//_camera.ratio((float)extent.width / (float)extent.height);
		//_camera.update_projection();
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

	// here call scene draw !!!
	_scene.draw(image_index, cmd, _smanager);

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
		//_camera.ratio((float)extent.width / (float)extent.height);
		//_camera.update_projection();

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
