#ifndef ENGINE_VULKAN_COMMAND_POOL_HPP
#define ENGINE_VULKAN_COMMAND_POOL_HPP


// vulkan headers
#include <vulkan/vulkan.h>
#include "exceptions.hpp"

#include "vulkan_logical_device.hpp"


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
			command_pool(void) noexcept;

			/* logical device and queue family index constructor */
			command_pool(const vulkan::logical_device&, const vk::u32);

			/* copy constructor */
			command_pool(const self&) noexcept;

			/* move constructor */
			command_pool(self&&) noexcept;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* new command buffer */
			auto new_command_buffer(const vulkan::logical_device&) const -> vulkan::command_buffer;

			/* new buffers */
			auto new_buffers(const vulkan::logical_device&, const vk::u32) const -> xns::vector<vulkan::command_buffer>;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* vk::command_pool conversion operator */
			operator const vk::command_pool&(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* pool */
			vk::command_pool _pool;

	}; // class command_pool

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMAND_POOL_HPP

