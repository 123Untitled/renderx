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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderx/running.hpp"

#include "renderx/shapes/cuboid.hpp"

#include "renderx/sdl/events.hpp"


auto make_projection(void) noexcept -> glm::mat4 {

	float fov = 105.0f;
	float ratio = rx::sdl::window::width() / rx::sdl::window::height();

	const float near = 0.1f;
	const float far = 1000.0f;


	const float ys = 1 / std::tan(((fov / 180.0f) * M_PI) * 0.5f);
	const float xs = ys / ratio;
	const float zs = far / (near - far);
	const float zt = zs * near;

	glm::mat4 projection {
		{+xs,   0,   0,   0},
		{  0, +ys,   0,   0},
		{  0,   0, -zs,   1},
		{  0,   0,  zt,   0}
	};

	return projection;
}

struct type_matrix {
	glm::mat4 matrix;
};

static type_matrix model {
	.matrix = glm::mat4(1.0f)
};

static type_matrix proj {
	//.matrix = glm::perspective(glm::radians(45.0f),
	//		(float)rx::sdl::window::width() / (float)rx::sdl::window::height(),
	//		0.1f, 1000.0f)
	.matrix = make_projection()
};

static type_matrix const_matrix {
	.matrix = glm::mat4(1.0f)
};

// view matrix (backwards 10 units)
static type_matrix view {
	.matrix = glm::mat4(1.0f)
};


// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
:
	//_events{},
	_queue{},
	_swapchain{},
	_pool{VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT},
	_cmds{_pool.underlying(), _swapchain.size()},
	_shaders{},
	
	_pipeline{
		vulkan::pipeline_builder<vertex_type>::build(
				_shaders,
				_swapchain.render_pass().underlying())
	},

	_memory{},
	_sync{},
	_meshes{},
	_objects{},
	_allocator{}
{

		auto cuboid = rx::cube();

		_meshes.emplace_back(cuboid.first, cuboid.second);

		//_mesh = rx::mesh{cuboid.first, cuboid.second};


		auto alloc = _allocator.allocate_buffer(_meshes.back().vertices().underlying());
		alloc.memcpy(cuboid.first.data());


		auto alloc_index = _allocator.allocate_buffer(_meshes.back().indices().underlying());
		alloc_index.memcpy(cuboid.second.data());


	_objects.emplace_back(_meshes.back());
}



// -- public methods ----------------------------------------------------------

/* run */
auto engine::renderer::run(void) -> void {

	static vk::u32 i = 0U;


	ws::running::start();

	while (ws::running::state() == true) {

		if (rx::sdl::events::poll()) {
			;
		}



		for (auto& object : _objects) {


			//auto n = 4;
			//object.rotation().x += n * 0.001f;
			//object.rotation().y += n * 0.005f;
			//object.rotation().z += n * -0.003f;

			object.rotation().y = -rx::sdl::events::x();
			object.rotation().x = +rx::sdl::events::y();


		}

		// update model matrix
		//model.matrix = glm::scale(model.matrix, glm::vec3(z, z, z));
		//model.matrix = glm::mat4(1.0f);
		//model.matrix = glm::rotate(model.matrix, (float)glfwGetTime()*0.5f, glm::vec3(-0.0f, 1.0f, 0.3f));
		//model.matrix = glm::rotate(model.matrix, (float)glfwGetTime()*1.0f, glm::vec3(-0.3f, 0.1f, 0.9f));

		view.matrix = glm::mat4(1.0f);
		view.matrix = glm::translate(view.matrix, glm::vec3(0, 0, +3));


		// update constant matrix
		//const_matrix.matrix = model.matrix * view.matrix * proj.matrix;
		const_matrix.matrix = proj.matrix * view.matrix * model.matrix;


		___self::draw_frame();

		//std::cout << "--------------- draw frame [" << i++ << "] ---------------" << std::endl;
	}

	// wait for logical device to be idle
	vulkan::device::wait_idle();
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {


	// wait for current fence
	_sync.wait_current_fence();

	vk::u32 image_index = 0U;

	// here error not means program must stop
	if (_swapchain.acquire_next_image(_sync.image_available(),
										image_index) == false)
		return;


	auto& cmd = _cmds[image_index];

	// record command buffer (see flagbits)
	cmd.reset();


	// -- record command buffer -----------------------------------------------

	// start recording
	cmd.begin();

	// begin render pass
	cmd.begin_render_pass(_swapchain,
						  _swapchain.render_pass(),
						  _swapchain.frames()[image_index]);

	// dynamic viewport
	cmd.set_viewport(_swapchain);

	// dynamic scissor
	cmd.set_scissor(_swapchain);


	{ // -- for each mesh -----------------------------------------------------

		for (const auto& object : _objects) {

			// bind pipeline
			cmd.bind_pipeline(_pipeline);

			// bind vertex buffer
			cmd.bind_vertex_buffer(object.mesh().vertices());

			// bind index buffer
			cmd.bind_index_buffer(object.mesh().indices());

			// push constants
			cmd.push_constants(_pipeline, proj.matrix * view.matrix * object.model());

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
	if (_queue.present(_swapchain, image_index,
					   _sync.render_finished()
				) == false)
		return;

	// next frame
	++_sync;
}


// this for when swapchain image number is inferior to MAX_FRAMES_IN_FLIGHT
// Vérifier si une frame précédente est en train d'utiliser cette image (il y a une fence à attendre)
//if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
//	vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
//}
