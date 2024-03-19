/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_COMMAND_POOL_HEADER
#define ENGINE_VULKAN_COMMAND_POOL_HEADER

// interal headers
#include "vk_shared.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- forward declarations ------------------------------------------------

	/* command buffer */
	class command_buffer;


	// -- C O M M A N D  P O O L ----------------------------------------------

	class command_pool final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_pool;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_pool(void) noexcept = default;

			/* logical device and queue family index constructor */
			command_pool(const vk::shared<vk::device>&,
						 const vk::u32);

			/* copy constructor */
			command_pool(const self&) noexcept = default;

			/* move constructor */
			command_pool(self&&) noexcept = default;

			/* destructor */
			~command_pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* new primary command buffer */
			auto new_primary_command_buffer(const vk::u32) -> vulkan::command_buffer;

			/* new secondary command buffer */
			auto new_secondary_command_buffer(const vk::u32) -> vulkan::command_buffer;


			// -- public conversion operators ---------------------------------

			/* vk::shared<vk::command_pool> conversion operator */
			operator const vk::shared<vk::command_pool>&(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* pool */
			vk::shared<vk::command_pool> _pool;

			/* command buffers */
			vk::command_buffer _buffers;

			/* size */
			vk::u32 _size;

	}; // class command_pool

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMAND_POOL_HEADER
