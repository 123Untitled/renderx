/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_COMMAND_POOL___
#define ___ENGINE_VULKAN_COMMAND_POOL___

#include "ve/vulkan/command_buffer.hpp"


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
			vk::command_pool _pool;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			command_pool(void) = delete;

			/* flags constructor */
			command_pool(const vk::command_pool_create_flags& = 0U);

			/* deleted copy constructor */
			command_pool(const ___self&) = delete;

			/* move constructor */
			command_pool(___self&&) noexcept;

			/* destructor */
			~command_pool(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::command_pool&;


			// -- public methods ----------------------------------------------

			/* reset to system */
			auto reset_to_system(void) const -> void;

			/* reset to pool */
			auto reset_to_pool(void) const -> void;

			/* trim */
			auto trim(void) const noexcept -> void;

	}; // class command_pool

} // namespace vulkan

#endif // ___ENGINE_VULKAN_COMMAND_POOL___
