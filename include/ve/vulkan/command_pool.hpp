/*****************************************************************************/
/*                                                                           */
/*      dMP dMP .aMMMb  dMP dMMMMb                                           */
/*     dMP dMP dMP"dMP amr dMP VMP                                           */
/*    dMP dMP dMP dMP dMP dMP dMP                                            */
/*    YMvAP  dMP aMP dMP dMP.aMP                                             */
/*     VP    VMMMP  dMP dMMMMP                                               */
/*                                                                           */
/*       dMMMMMP dMMMMb   aMMMMP dMP dMMMMb  dMMMMMP                         */
/*      dMP     dMP dMP dMP     amr dMP dMP dMP                              */
/*     dMMMP   dMP dMP dMP MMP dMP dMP dMP dMMMP                             */
/*    dMP     dMP dMP dMP.dMP dMP dMP dMP dMP                                */
/*   dMMMMMP dMP dMP  VMMMP" dMP dMP dMP dMMMMMP                             */
/*                                                                           */
/*****************************************************************************/

#ifndef ___void_engine_vulkan_command_pool___
#define ___void_engine_vulkan_command_pool___

#include "ve/vk/unique.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- C O M M A N D  P O O L ----------------------------------------------

	class command_pool final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::command_pool;


			// -- private members ---------------------------------------------

			/* pool */
			vk::unique<vk::command_pool> _pool;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			command_pool(void) = delete;

			/* flags constructor */
			command_pool(const vk::command_pool_create_flags& = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

			/* deleted copy constructor */
			command_pool(const ___self&) = delete;

			/* move constructor */
			command_pool(___self&&) noexcept = default;

			/* destructor */
			~command_pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::command_pool&;


			// -- public methods ----------------------------------------------

			/* reset to system */
			auto reset_to_system(void) const -> void;

			/* reset to pool */
			auto reset_to_pool(void) const -> void;

			/* trim */
			auto trim(void) const noexcept -> void;

	}; // class command_pool

} // namespace vulkan

#endif // ___void_engine_vulkan_command_pool___
