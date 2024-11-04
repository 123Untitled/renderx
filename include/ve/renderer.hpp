#ifndef ___ve_renderer___
#define ___ve_renderer___

#include "ve/vulkan/swapchain_manager.hpp"
#include "ve/vulkan/sync.hpp"

#include "ve/vulkan/command_pool.hpp"
#include "ve/vulkan/commands.hpp"

#include "ve/vulkan/queue.hpp"

#include "ve/scene/scene.hpp"
#include "ve/skybox.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::renderer;


			// -- private members ---------------------------------------------

			/* queue */
			vulkan::queue _queue;

			/* swapchain */
			vulkan::swapchain_manager _smanager;

			/* command pool */
			ve::command_pool _pool;

			/* command buffers */
			vulkan::commands _cmds;

			/* sync */
			ve::sync _sync;

			/* scene */
			ve::scene _scene;


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

	}; // class renderer

} // namespace ve

#endif // ___ve_renderer___
