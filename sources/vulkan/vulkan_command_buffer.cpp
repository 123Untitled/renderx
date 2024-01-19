#include "vulkan_commandbuffer.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::command_buffer::command_buffer(void)
: _buffer{VK_NULL_HANDLE}, _device{VK_NULL_HANDLE} {


	::VkCommandBufferAllocateInfo info{};
	// type of structure
	info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	// pointer to next structure
	info.pNext              = nullptr;
	// command pool from which buffers are allocated
	info.commandPool        = VK_NULL_HANDLE;
	// level of command buffer
	info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	// number of command buffers to allocate
	info.commandBufferCount = 1;


	if (::vkAllocateCommandBuffers(nullptr /* logical device */,
				&info, &_buffer) != VK_SUCCESS)
		throw engine::exception{"failed to allocate command buffer"};



}
