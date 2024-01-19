#ifndef ENGINE_VULKAN_COMMANDBUFFER_HPP
#define ENGINE_VULKAN_COMMANDBUFFER_HPP


// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- C O M M A N D  B U F F E R -------------------------------------------

	class command_buffer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_buffer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_buffer(void);


		private:

			// -- private members ---------------------------------------------

			/* buffer */
			::VkCommandBuffer _buffer;

			/* logical device */
			::VkDevice _device;

	};

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMANDBUFFER_HPP
