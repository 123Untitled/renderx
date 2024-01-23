#include "renderer.hpp"

static vk::vector<engine::basic_vertex> vertices{};

static vk::pipeline pipeline{};

// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
:	_instance{},
	_window{800, 600},
	_events{},
	_surface{_instance, _window},
	_pdevice{_instance.pick_physical_device(_surface)},
	_ldevice{_pdevice, _surface},
	_swapchain{},
	_command_pool{},
	_image_available{},
	_render_finished{},
	//_command_pool{*_ldevice, 0}, /* queue family index */
	//_image_available{*_ldevice},
	//_render_finished{*_ldevice},
	_shaders{} {

		/*
	_pdevice{vulkan::instance::pick_physical_device(_surface)},
	_ldevice{xns::make_shared<vulkan::logical_device>(_pdevice, _surface)},
	_swapchain{_pdevice, _ldevice, _surface},
	_command_pool{},
	_image_available{},
	_render_finished{},
	//_command_pool{*_ldevice, 0},
	//_image_available{*_ldevice},
	//_render_finished{*_ldevice},
	_shaders{} {
		*/




	// create triangle
	vertices.emplace_back(-1.0f, -1.0f, 0.0f,
						   1.0f,  0.0f, 0.0f, 1.0f);
	vertices.emplace_back( 0.0f,  1.0f, 0.0f,
						   0.0f,  1.0f, 0.0f, 1.0f);
	vertices.emplace_back( 1.0f, -1.0f, 0.0f,
						   0.0f,  0.0f, 1.0f, 1.0f);



}

/* initialize */
auto engine::renderer::initialize(void) -> void {

	// create logical device
	//_ldevice = xns::make_shared<vulkan::logical_device>(_pdevice, _surface);
	// create swapchain
	//_swapchain = vulkan::swapchain{_pdevice, _ldevice, _surface};
	// create command pool
	//_command_pool = vulkan::command_pool{*_ldevice, 0}; /* queue family index */

	// create semaphores
	//_image_available = vulkan::semaphore{*_ldevice};
	//_render_finished = vulkan::semaphore{*_ldevice};


	// load shaders
	//_shaders.load_vertex<"basic">(*_ldevice);


}

/* destructor */
engine::renderer::~renderer(void) noexcept {
	//this->destroy(*_ldevice);
}


// -- public methods ----------------------------------------------------------

/* launch */
auto engine::renderer::launch(void) -> void {

	//this->initialize();

	return;
	while (_window.should_close() == false) {

		_events.wait();
		//_events.poll();
		//draw_frame();
	}
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {

	xns::u32 image_index = 0;

	auto cb = _command_pool.new_command_buffer(_ldevice);

	cb.bind_graphics_pipeline(pipeline);

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
	// wait for logical device to be idle
	//_ldevice->wait_idle();
	//_shaders.destroy(*_ldevice);
	//_render_finished.destroy(*_ldevice);
	//_image_available.destroy(*_ldevice);
	//_command_pool.destroy(*_ldevice);
}


