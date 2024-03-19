/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "renderer.hpp"
#include "vulkan/global/instance.hpp"

static vk::vector<engine::basic_vertex> vertices{};

static vk::pipeline pipeline{};


// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
:
	_window{800, 600},
	_events{},
	_surface{_window},
	_device{_surface},
	_swapchain{_device, _surface},
	_command_pool{_device, 0}, /* queue family index */
	_command_buffer{_command_pool}, /* swapChainFramebuffers.size() */
	_image_available{_device},
	_render_finished{_device},
	_shaders{},
	_render_pass{_device} {

	// load shaders
	_shaders.load_vertex<"basic">(_device);

	vulkan::shader_module vertex_shader{_device,
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


	while (_window.should_close() == false) {

		_events.wait();
		//_events.poll();
		//draw_frame();
	}

	// wait for logical device to be idle
	_device.wait_idle();
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

	vk::semaphore   wait[] = { _image_available };
	vk::semaphore signal[] = { _render_finished };

	// maybe send img_index to queue.submit
	/* command_buffers[image_index] */
	queue.submit(wait, signal, VK_NULL_HANDLE, /* command_buffers */ 0);

	// here error not means program must stop
	if (queue.present(_swapchain, image_index, signal) == false)
		return;
}


