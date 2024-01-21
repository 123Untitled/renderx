#include "vulkan_command_buffer.hpp"


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::command_buffer::command_buffer(void) noexcept
: _buffer{VK_NULL_HANDLE} {}

/* logical device and command pool constructor */
vulkan::command_buffer::command_buffer(const vulkan::logical_device& device,
									   const vulkan::command_pool&   pool)
: _buffer{VK_NULL_HANDLE} {
	// create info
	const auto info = self::create_info(pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1);
	// allocate command buffer
	if (::vkAllocateCommandBuffers(device, &info, &_buffer) != VK_SUCCESS)
		throw engine::exception{"failed to allocate command buffer"};
}

/* move constructor */
vulkan::command_buffer::command_buffer(self&& other) noexcept
: _buffer{other._buffer} {
	other._buffer = VK_NULL_HANDLE;
}


// -- private assignment operators --------------------------------------------

/* move assignment operator */
auto vulkan::command_buffer::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	_buffer = other._buffer;
	other._buffer = VK_NULL_HANDLE;
	return *this;
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::command_buffer::destroy(const vulkan::logical_device& device,
									 const vulkan::command_pool& pool) noexcept -> void {
	if (_buffer == VK_NULL_HANDLE)
		return;
	::vkFreeCommandBuffers(device, pool, 1, &_buffer);
	_buffer = VK_NULL_HANDLE;
}


// -- public conversion operators ---------------------------------------------

/* VkCommandBuffer conversion operator */
vulkan::command_buffer::operator ::VkCommandBuffer(void) const noexcept {
	return _buffer;
}


// -- public methods ----------------------------------------------------------

/* begin */
auto vulkan::command_buffer::begin(void) const -> void {
	// begin info
	const auto info = ::VkCommandBufferBeginInfo{
		.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext            = nullptr,
		.flags            = 0,
		.pInheritanceInfo = nullptr
	};

	// begin command buffer
	if (::vkBeginCommandBuffer(_buffer, &info) != VK_SUCCESS)
		throw engine::exception{"failed to begin recording command buffer"};


    // VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
	// le command buffer sera ré-enregistré après son utilisation,
	// donc invalidé une fois son exécution terminée
    // VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
	// ce command buffer secondaire sera intégralement exécuté dans une unique render pass
    // VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
	// le command buffer peut être ré-envoyé à la queue alors qu'il y est déjà et/ou est en cours d'exécution

	// Le paramètre pInheritanceInfo n'a de sens que pour les command buffers secondaires.
	// Il indique l'état à hériter de l'appel par le command buffer primaire.

	// Si un command buffer est déjà prêt un appel à vkBeginCommandBuffer le regénèrera implicitement.
	// Il n'est pas possible d'enregistrer un command buffer en plusieurs fois.

}

/* renderpass begin */
auto vulkan::command_buffer::renderpass_begin(void) const noexcept -> void {

	const ::VkClearValue clear_color{
		.color = ::VkClearColorValue{
			.float32 = {0.2f, 0.2f, 0.2f, 1.0f}
		}
	};

	::VkRenderPassBeginInfo info{
		.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext           = nullptr,
		.renderPass      = VK_NULL_HANDLE, // renderpass
		.framebuffer     = VK_NULL_HANDLE, // framebuffer from swapchain
		.renderArea      = ::VkRect2D{
			.offset = ::VkOffset2D{0, 0},
			.extent = ::VkExtent2D{800, 600} // swapchain extent
		},
		.clearValueCount = 1,
		.pClearValues    = &clear_color
	};

	::vkCmdBeginRenderPass(_buffer, &info,
			// primary command buffer or secondary command buffer ?
			VK_SUBPASS_CONTENTS_INLINE
			);
}


/* bind pipeline */
auto vulkan::command_buffer::bind_pipeline(const ::VkPipelineBindPoint point,
										   const ::VkPipeline pipeline) const noexcept -> void {
	::vkCmdBindPipeline(_buffer, point, pipeline);
}

/* draw */
auto vulkan::command_buffer::draw(const ::uint32_t vertex_count,
								  const ::uint32_t instance_count,
								  const ::uint32_t first_vertex,
								  const ::uint32_t first_instance) const noexcept -> void {
	::vkCmdDraw(_buffer, vertex_count, instance_count, first_vertex, first_instance);
}

/* renderpass end */
auto vulkan::command_buffer::renderpass_end(void) const noexcept -> void {
	::vkCmdEndRenderPass(_buffer);
}

/* end */
auto vulkan::command_buffer::end(void) const -> void {
	if (::vkEndCommandBuffer(_buffer) != VK_SUCCESS)
		throw engine::exception{"failed to record command buffer"};
}



// -- private static methods --------------------------------------------------

/* create info */
auto vulkan::command_buffer::create_info(const vulkan::command_pool& pool,
										 const ::VkCommandBufferLevel level,
										 const ::uint32_t count) noexcept -> ::VkCommandBufferAllocateInfo {
    // VK_COMMAND_BUFFER_LEVEL_PRIMARY
	// peut être envoyé à une queue pour y être exécuté
	// mais ne peut être appelé par d'autres command buffers
    // VK_COMMAND_BUFFER_LEVEL_SECONDARY
	// ne peut pas être directement émis à une queue
	// mais peut être appelé par un autre command buffer

	return ::VkCommandBufferAllocateInfo{
		// type of structure
		.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		// pointer to next structure
		.pNext              = nullptr,
		// command pool from which buffers are allocated
		.commandPool        = pool,
		// level of command buffer (primary or secondary)
		.level              = level,
		// number of command buffers to allocate
		.commandBufferCount = count,
	};
}

/* create buffers */
auto vulkan::command_buffer::create_buffers(const vulkan::logical_device& device,
											const vulkan::command_pool& pool,
											const ::uint32_t count) -> xns::vector<self> {
	// create info
	const auto info = self::create_info(pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, count);
	// allocate vector of command buffers
	xns::vector<self> buffers{};
	buffers.resize(count);
	// get data pointer
	auto data = reinterpret_cast<::VkCommandBuffer*>(buffers.data());
	// allocate command buffers
	if (::vkAllocateCommandBuffers(device, &info, data) != VK_SUCCESS)
		throw engine::exception{"failed to allocate command buffers"};
	// return vector
	return buffers;
}

