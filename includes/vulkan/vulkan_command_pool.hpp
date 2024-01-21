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

			/* logical device constructor */
			command_pool(const vulkan::logical_device&);


			// -- public methods ----------------------------------------------

			/* new buffer */
			auto new_buffer(const vulkan::logical_device&) const -> vulkan::command_buffer;

			/* new buffers */
			auto new_buffers(const vulkan::logical_device&, const ::uint32_t) const -> xns::vector<vulkan::command_buffer>;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* VkCommandPool conversion operator */
			operator ::VkCommandPool(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* pool */
			::VkCommandPool _pool;

	}; // class command_pool

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMAND_POOL_HPP

