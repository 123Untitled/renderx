#include "vulkan_vertex_buffer.hpp"


static auto find_memory_type(::uint32_t filter, ::VkMemoryPropertyFlags flags) -> ::uint32_t {

	::VkPhysicalDeviceMemoryProperties properties{};
	::VkPhysicalDevice device = VK_NULL_HANDLE; // temporary

	::vkGetPhysicalDeviceMemoryProperties(device, &properties);

	for (::uint32_t i = 0; i < properties.memoryTypeCount; ++i) {
		if ((filter & (1 << i))
		&& (properties.memoryTypes[i].propertyFlags & flags) == flags) {
			return i;
		}
	}

	throw engine::exception{"failed to find suitable memory type"};
}


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::vertex_buffer::vertex_buffer(const vulkan::logical_device& device)
:	_buffer{VK_NULL_HANDLE},
	_memory{VK_NULL_HANDLE} {

	vk::vector<engine::basic_vertex> vertices; // temporary

	::VkBufferCreateInfo info{};

	info.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.pNext       = nullptr;
	info.flags       = 0;
	info.size        = sizeof(engine::basic_vertex) * vertices.size();
	info.usage       = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.queueFamilyIndexCount = 0; // not implemented yet !
	info.pQueueFamilyIndices   = nullptr; // not implemented yet !

	// create buffer
	if (::vkCreateBuffer(device, &info, nullptr, &_buffer) != VK_SUCCESS) {
		throw engine::exception{"failed to create vertex buffer"};
	}

	::VkMemoryRequirements requirements{};
	::vkGetBufferMemoryRequirements(device, _buffer, &requirements);

	::VkMemoryAllocateInfo alloc_info{};
	alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.pNext           = nullptr;
	alloc_info.allocationSize  = requirements.size;
	alloc_info.memoryTypeIndex = find_memory_type(requirements.memoryTypeBits,
									VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
									| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (::vkAllocateMemory(device, &alloc_info, nullptr, &_memory) != VK_SUCCESS) {
		throw engine::exception{"failed to allocate vertex buffer memory"};
	}

	if (::vkBindBufferMemory(device, _buffer, _memory, 0) != VK_SUCCESS) {
		throw engine::exception{"failed to bind vertex buffer memory"};
	}
	// 4th parameter is offset in memory, but we want to bind from the beginning
	// its used for memory allocation of multiple buffers in one memory block
	// very useful for optimization !


	// copy vertices to buffer
	void* data;
	if (::vkMapMemory(device, _memory, 0, VK_WHOLE_SIZE, 0, &data) != VK_SUCCESS) {
		throw engine::exception{"failed to map vertex buffer memory"};
	}
	std::memcpy(data, vertices.data(), info.size);
	::vkUnmapMemory(device, _memory);

	// to see later :
	//::vkFlushMappedMemoryRanges(device, 1, &(::VkMappedMemoryRange{
	//	.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
	//	.pNext  = nullptr,
	//	.memory = _memory,
	//	.offset = 0,
	//	.size   = VK_WHOLE_SIZE
	//}));
	// ::vkInvalidateMappedMemory
}

/* move constructor */
vulkan::vertex_buffer::vertex_buffer(self&& other) noexcept
: _buffer{other._buffer}, _memory{other._memory} {
	other.init();
}




/* destructor */
vulkan::vertex_buffer::~vertex_buffer(void) noexcept {
	free();
}


// -- public methods ----------------------------------------------------------

/* render */
auto vulkan::vertex_buffer::render(const ::VkCommandBuffer& command) const noexcept -> void {
	// bind vertex buffer
	const ::VkDeviceSize offset = 0;
	::vkCmdBindVertexBuffers(
			// command buffer
			command,
			// first binding
			0,
			// binding count
			1,
			// buffers
			&_buffer,
			// offsets
			&offset);

	::vkCmdDraw(
			// command buffer
			command,
			// vertex count
			3,
			// instance count
			1,
			// first vertex
			0,
			// first instance
			0);
}



// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::vertex_buffer::free(void) noexcept -> void {
	// check if buffer is null
	if (_buffer == VK_NULL_HANDLE)
		return;
	// destroy buffer
	// !!!!!!!!!!!
	//::vkDestroyBuffer(_device.underlying(), _buffer, nullptr);
	//::vkFreeMemory(_device.underlying(), _memory, nullptr);
}

/* init */
auto vulkan::vertex_buffer::init(void) noexcept -> void {
	_buffer = VK_NULL_HANDLE;
	_memory = VK_NULL_HANDLE;
}

