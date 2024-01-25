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
	_swapchain{_pdevice, _ldevice, _surface},
	_command_pool{_ldevice, 0}, /* queue family index */
	_image_available{_ldevice},
	_render_finished{_ldevice},
	_shaders{},
	_render_pass{_ldevice} {

	// load shaders
	_shaders.load_vertex<"basic">(_ldevice);

	vulkan::shader_module vertex_shader{_ldevice,
			xns::string{"shaders/spirv/basic.vert.spv"}, xns::string{"main"}};

	// create triangle
	vertices.emplace_back(-1.0f, -1.0f, 0.0f,
						   1.0f,  0.0f, 0.0f, 1.0f);
	vertices.emplace_back( 0.0f,  1.0f, 0.0f,
						   0.0f,  1.0f, 0.0f, 1.0f);
	vertices.emplace_back( 1.0f, -1.0f, 0.0f,
						   0.0f,  0.0f, 1.0f, 1.0f);
}



// -- public methods ----------------------------------------------------------

/* launch */
auto engine::renderer::launch(void) -> void {

	//this->initialize();
	std::cout << _ldevice.count() << std::endl;

	return;
	while (_window.should_close() == false) {

		_events.wait();
		//_events.poll();
		//draw_frame();
	}

	// wait for logical device to be idle
	_ldevice.wait_idle();
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {

	xns::u32 image_index = 0;

	//auto cb = _command_pool.new_command_buffer(_ldevice);

	//cb.bind_pipeline<"graphics">(pipeline);

	vulkan::queue queue{};

	// here error not means program must stop
	if (_swapchain.acquire_next_image(_image_available, image_index) == false)
		return;

	vk::semaphore wait[] = {_image_available};
	vk::semaphore signal[] = {_render_finished};

	// maybe send img_index to queue.submit
	/* command_buffers[image_index] */
	queue.submit(wait, signal, VK_NULL_HANDLE, /* command_buffers */ 0);

	// here error not means program must stop
	if (queue.present(_swapchain, image_index, signal) == false)
		return;
}


