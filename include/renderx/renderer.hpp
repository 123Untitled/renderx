#ifndef ___RENDERX_RENDERER___
#define ___RENDERX_RENDERER___

//#include "renderx/vertex/basic_vertex.hpp"

#include "renderx/vulkan/swapchain.hpp"
#include "renderx/vulkan/swapchain_manager.hpp"

#include "renderx/vulkan/semaphore.hpp"
#include "renderx/vulkan/fence.hpp"
#include "renderx/vulkan/command_pool.hpp"
#include "renderx/vulkan/pipeline.hpp"
#include "renderx/vulkan/commands.hpp"
#include "renderx/vulkan/queue.hpp"

#include "shader_library.hpp"

//#include "vulkan/global/instance.hpp"
#include "renderx/vertex/vertex.hpp"
#include "renderx/vertex/position.hpp"

#include "renderx/vulkan/device_memory.hpp"
#include "renderx/vulkan/memory_buffer.hpp"
#include "renderx/vulkan/sync.hpp"

#include "renderx/vulkan/allocator.hpp"
#include "renderx/vulkan/index_buffer.hpp"
#include "renderx/vulkan/vertex_buffer.hpp"
#include "renderx/shapes/cuboid.hpp"
#include "renderx/mesh.hpp"
#include "renderx/object.hpp"
#include "renderx/camera.hpp"

#include "renderx/glfw/events.hpp"

// to be removed !
using vertex_type = engine::vertex<vx::float3,
								   vx::float3>;



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


			/* shader library */
			engine::shader_library _shaders;


			/* pipeline */
			vulkan::pipeline _pipeline;

			/* device memory */
			vulkan::device_memory _memory;

			/* sync */
			vulkan::sync<3U> _sync;

			/* mesh */
			std::vector<rx::mesh> _meshes;

			/* objects */
			vk::vector<rx::object> _objects;

			vulkan::allocator<vulkan::cpu_coherent> _allocator;

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
