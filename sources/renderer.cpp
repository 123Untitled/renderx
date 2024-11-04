#include "ve/renderer.hpp"
#include "ve/time/delta.hpp"
#include "ve/running.hpp"
#include "ve/glfw/monitor.hpp"
#include "ve/glfw/events.hpp"
#include "ve/vulkan/pipeline/pipeline_library.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::renderer::renderer(void)
: _queue{},
  _smanager{},
  _pool{},
  _cmds{_pool, _smanager.size(), VK_COMMAND_BUFFER_LEVEL_PRIMARY},
  _sync{1U/*_smanager.size()*/},
  _scene{_smanager} {
}



// -- public methods ----------------------------------------------------------

/* run */
auto ve::renderer::run(void) -> void {

	vk::u32 i{0U};

	// game loop
	while (ve::running::state() == true &&
			glfw::window::should_close() == false) {

		// update delta time
		ve::delta::update();

		// poll events
		glfw::events::poll();


		ve::mouse_delta::update();
		//glfw::compute_to_mouse_delta(_camera);


		___self::_draw_frame();

		//std::cout << "--------------- draw frame [" << i++ << "] ---------------" << std::endl;
	}

	// wait for logical device to be idle
	vulkan::device::wait_idle();
}


/* draw frame */
auto ve::renderer::_draw_frame(void) -> void {

	/* wait for current fence;
	 *    - wait for the current frame to be finished rendering
	 */

	// wait for current fence
	_sync.wait_current_fence();

	vk::u32 image_index = 0U;

	const auto& swapchain = _smanager.swapchain();

	// here error not means program must stop
	const vk::result status = swapchain.acquire_next_image(
									_sync.current_image_available(),
									image_index);

	/* acquire next image:
	 *    - acquire next image from swapchain
	 *    - check for status
	 *    - recreate swapchain if needed
	 */

	if (status == VK_ERROR_OUT_OF_DATE_KHR) {
		_smanager.recreate();
		return;
	}
	else if (status != VK_SUCCESS && status != VK_SUBOPTIMAL_KHR) {
		throw vk::exception{"failed to acquire next image", status};
	}


	auto cmd = _cmds[image_index];

	// record command buffer (see flagbits)
	cmd.reset();


	// -- record command buffer -----------------------------------------------

	// start recording
	cmd.begin();


	// here call scene draw !!!
	_scene.draw(image_index, cmd, _smanager);


	/* here compute post processing




	*/

	// end recording
	cmd.end();

	// -- submit command buffer -----------------------------------------------

	/* reset current fence;
	 *    - reset current fence to be used again
	 */

	// reset fence
	_sync.reset_current_fence();


	/* submit command buffer;
	 *    - submit command buffer to queue
	 *    - wait for current frame to be finished rendering
	 */

	// submit command buffers
	_queue.submit(_sync.current_image_available(),
				  _sync.current_render_finished(),
				  _sync.current_fence(),
				  cmd);

	// here error not means program must stop
	const vk::result state = _queue.present(swapchain, image_index,
											_sync.current_render_finished());

	if (status == VK_ERROR_OUT_OF_DATE_KHR
	  || status == VK_SUBOPTIMAL_KHR
	  || glfw::window::resized() == true) {
		// recreate swapchain
		_smanager.recreate();
	}
	else if (state != VK_SUCCESS) {
		throw vk::exception{"failed to queue present", state};
	}

	// next frame
	++_sync;
}


// this for when swapchain image number is inferior to MAX_FRAMES_IN_FLIGHT
// Vérifier si une frame précédente est en train d'utiliser cette image (il y a une fence à attendre)
//if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
//	vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
//}
