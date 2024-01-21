#include "renderer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
	// create window
:	_window{800, 600},
	// create events
	_events{},
	// create surface
	_surface{_window},
	// pick physical device
	_pdevice{vulkan::instance::pick_physical_device(_surface)},
	// create logical device
	_ldevice{_pdevice, _surface},
	// create swapchain
	_swapchain{_pdevice, _ldevice, _surface},
	// create semaphores
	_image_available{_ldevice},
	// create semaphores
	_render_finished{_ldevice} {

}

/* destructor */
engine::renderer::~renderer(void) noexcept {
	_render_finished.destroy(_ldevice);
	_image_available.destroy(_ldevice);
	_swapchain.destroy(_ldevice);
}


// -- public methods ----------------------------------------------------------

/* launch */
auto engine::renderer::launch(void) -> void {

	while (_window.should_close() == false) {

		_events.wait();
		//_events.poll();
		draw_frame();
	}

	// wait for logical device to be idle
	_ldevice.wait_idle();
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {

	xns::u32 image_index = 0;

	vulkan::queue queue{};

	// here error not means program must stop
	if (_swapchain.acquire_next_image(_ldevice, _image_available, image_index) == false)
		return;


	// maybe send img_index to queue.submit
	/* command_buffers[image_index] */
	queue.submit(&_image_available, 1,
				 &_render_finished, 1,
				 nullptr, /* command_buffers */ 0);


	// here error not means program must stop
	if (queue.present(_swapchain, image_index, &_render_finished, 1) == false)
		return;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto engine::renderer::destroy(const vulkan::logical_device& device) noexcept -> void {
	_image_available.destroy(device);
	_render_finished.destroy(device);
}

