/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_RENDERER___
#define ___ENGINE_RENDERER___

#include <vulkan/vulkan.h>

//#include "engine/vertex/basic_vertex.hpp"

#include "engine/vulkan/swapchain.hpp"
#include "engine/vulkan/semaphore.hpp"
#include "engine/vulkan/fence.hpp"
#include "engine/vulkan/command_pool.hpp"
#include "engine/vulkan/pipeline.hpp"
#include "engine/vulkan/commands.hpp"
#include "engine/vulkan/queue.hpp"

#include "shader_library.hpp"

//#include "vulkan/global/instance.hpp"
#include "engine/vertex/vertex.hpp"
#include "engine/vertex/position.hpp"

#include "engine/vulkan/device_memory.hpp"
#include "engine/vulkan/memory_buffer.hpp"
#include "engine/vulkan/sync.hpp"

#include "renderx/vulkan/allocator.hpp"
#include "renderx/vulkan/index_buffer.hpp"
#include "renderx/vulkan/vertex_buffer.hpp"
#include "renderx/shapes/cuboid.hpp"
#include "renderx/mesh.hpp"
#include "renderx/object.hpp"
#include "renderx/camera.hpp"


// to be removed !
using vertex_type = engine::vertex<vx::float3,
								   vx::float3>;



// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = engine::renderer;


			// -- private members ---------------------------------------------

			/* queue */
			vulkan::queue _queue;

			/* swapchain */
			vulkan::swapchain _swapchain;

			/* command pool */
			vulkan::command_pool _pool;

			///* command buffers */
			vulkan::commands<vulkan::primary> _cmds;


			/* shader library */
			shader_library _shaders;


			/* pipeline */
			vulkan::pipeline _pipeline;

			/* device memory */
			vulkan::device_memory _memory;

			/* sync */
			vulkan::sync<3U> _sync;

			/* mesh */
			xns::vector<rx::mesh> _meshes;

			/* objects */
			vk::vector<rx::object> _objects;

			vulkan::allocator<vulkan::cpu_coherent> _allocator;

			/* camera */
			rx::camera _camera;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderer(void);

			/* deleted copy constructor */
			renderer(const ___self&) = delete;

			/* deleted move constructor */
			renderer(___self&&) noexcept = delete;

			/* destructor */
			~renderer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = delete;


			// -- public methods ----------------------------------------------

			/* draw frame */
			auto draw_frame(void) -> void;

			/* run */
			auto run(void) -> void;

	}; // class renderer

} // namespace engine

#endif // ___ENGINE_RENDERER___
