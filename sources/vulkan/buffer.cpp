#include "ve/vulkan/buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* parameters constructor */
vulkan::buffer::buffer(const vk::device_size& size,
					   const vk::buffer_usage_flags& usage)
: _buffer{vk::make_unique<vk::buffer>(
		// create buffer info
		vk::buffer_info{
			// structure type
			VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			// next structure
			nullptr,
			// flags
			0U,
			// size of buffer
			size,
			// usage flags
			usage,
			// sharing mode (exclusive or concurrent)
			VK_SHARING_MODE_EXCLUSIVE,
			// queue family index count (only for concurrent)
			0U,
			// queue family indices (only for concurrent)
			nullptr
		})} {
}

// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::buffer::underlying(void) const noexcept -> const vk::buffer& {
	return _buffer;
}
