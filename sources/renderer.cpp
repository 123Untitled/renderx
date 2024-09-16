/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "engine/renderer.hpp"
#include "engine/vertex/vertex.hpp"


//static vk::vector<engine::basic_vertex> vertices{};


class rotation final {

	public:

		static consteval auto format(void) noexcept -> vk::format {
			return VK_FORMAT_R32G32B32_SFLOAT;
		}

		xns::f32 _x;
		xns::f32 _y;
		xns::f32 _z;
};


using _vertex = engine::vertex<rotation>;

// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
:
	_window{800, 600},
	_events{},
	_surface{_window},
	_device{_surface},
	_queue{_device},
	_swapchain{_device, _surface},
	_pool{_device, _device.family()},
	_cmds{_pool, _swapchain.size()},
	_image_available{_device},
	_render_finished{_device},
	_shaders{_device},
	_pipeline{
		vulkan::pipeline_builder<_vertex>::build(
				_device.shared(),
				_shaders,
				_swapchain.render_pass().shared())
	} {
	//_shaders{} {

	// load shaders
	//_shaders.load_vertex<"basic">(_device);
	//
	//vulkan::shader_module vertex_shader{_device,
	//		xns::string{"shaders/spirv/basic.vert.spv"}, xns::string{"main"}};
	//
	//// create triangle
	//vertices.emplace_back(-1.0f, -1.0f, 0.0f,
	//					   1.0f,  0.0f, 0.0f, 1.0f);
	//vertices.emplace_back( 0.0f,  1.0f, 0.0f,
	//					   0.0f,  1.0f, 0.0f, 1.0f);
	//vertices.emplace_back( 1.0f, -1.0f, 0.0f,
	//					   0.0f,  0.0f, 1.0f, 1.0f);
}



// -- public methods ----------------------------------------------------------

/* launch */
auto engine::renderer::launch(void) -> void {


	while (_window.should_close() == false) {

		_events.wait();

		//_events.poll();
		//draw_frame();

		//sleep(1);
	}

	// wait for logical device to be idle
	_device.wait_idle();
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {

	xns::u32 image_index = 0U;

	// here error not means program must stop
	if (_swapchain.acquire_next_image(_image_available, image_index) == false)
		return;

	auto& cmd = _cmds[image_index];

	cmd.begin();

	cmd.renderpass_begin(_swapchain,
						 _swapchain.render_pass(),
						 _swapchain.frames()[image_index]);

	cmd.bind_graphics_pipeline(_pipeline);
	cmd.cmd_set_viewport(_swapchain);
	// set scissor...
	cmd.cmd_draw(3, 1, 0, 0);
	cmd.renderpass_end();
	cmd.end();


	// maybe send img_index to queue.submit
	/* command_buffers[image_index] */
	_queue.submit({_image_available}, {_render_finished}, _cmds);
	//_queue.submit(wait, signal, _cmds);

	// here error not means program must stop
	if (_queue.present(_swapchain, image_index, {_render_finished}) == false)
		return;
}
