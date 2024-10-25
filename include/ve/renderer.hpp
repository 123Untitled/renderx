#ifndef ___RENDERX_RENDERER___
#define ___RENDERX_RENDERER___

//#include "ve/vertex/basic_vertex.hpp"

#include "ve/vulkan/swapchain.hpp"
#include "ve/vulkan/swapchain_manager.hpp"

#include "ve/vulkan/semaphore.hpp"
#include "ve/vulkan/fence.hpp"
#include "ve/vulkan/command_pool.hpp"
#include "ve/vulkan/pipeline.hpp"
#include "ve/vulkan/commands.hpp"
#include "ve/vulkan/queue.hpp"

//#include "vulkan/global/instance.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vertex/position.hpp"

#include "ve/vulkan/device_memory.hpp"
#include "ve/vulkan/memory_buffer.hpp"
#include "ve/vulkan/sync.hpp"

#include "ve/vulkan/allocator.hpp"
#include "ve/vulkan/index_buffer.hpp"
#include "ve/vulkan/vertex_buffer.hpp"
#include "ve/shapes/cuboid.hpp"
#include "ve/mesh.hpp"
#include "ve/object.hpp"
#include "ve/camera.hpp"

#include "ve/glfw/events.hpp"

// to be removed !
using vertex_type = ve::vert3x;
//using vertex_type = ve::vertex<vx::float3, vx::float3>;



// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::renderer;


			// -- private members ---------------------------------------------

			/* queue */
			vulkan::queue _queue;

			/* swapchain */
			vulkan::swapchain_manager _smanager;

			/* command pool */
			vulkan::command_pool _pool;

			///* command buffers */
			vulkan::commands<vulkan::primary> _cmds;

			/* pipeline */
			vulkan::pipeline _pipeline;

			/* device memory */
			vulkan::device_memory _memory;

			/* sync */
			vulkan::sync<3U> _sync;

			/* objects */
			vk::vector<rx::object> _objects;

			/* camera */
			rx::camera _camera;


			// -- private methods ---------------------------------------------

			/* draw frame */
			auto _draw_frame(void) -> void;


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

			/* run */
			auto run(void) -> void;


			auto test(void) -> void;
			static auto entrypoint(void*) -> void*;

	}; // class renderer

} // namespace rx

#endif // ___RENDERX_RENDERER___
