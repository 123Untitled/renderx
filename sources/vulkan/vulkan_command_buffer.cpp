#include "vulkan_command_buffer.hpp"


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::command_buffer::command_buffer(void) noexcept
: _buffer{VK_NULL_HANDLE} {}

/* logical device and command pool constructor */
vulkan::command_buffer::command_buffer(const vulkan::logical_device& device,
									   const vulkan::command_pool& pool)
// create command buffer
: _buffer{vk::create_command_buffer(device, vk::command_buffer_info{
		// type of structure
		.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		// pointer to next structure
		.pNext              = nullptr,
		// command pool from which buffers are allocated
		.commandPool        = pool,
		// level of command buffer (primary or secondary)
		.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		// number of command buffers to allocate
		.commandBufferCount = 1
	})} {

    // VK_COMMAND_BUFFER_LEVEL_PRIMARY
	// peut être envoyé à une queue pour y être exécuté
	// mais ne peut être appelé par d'autres command buffers
    // VK_COMMAND_BUFFER_LEVEL_SECONDARY
	// ne peut pas être directement émis à une queue
	// mais peut être appelé par un autre command buffer

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
	vk::destroy_command_buffer(device, pool, _buffer);
}


// -- public conversion operators ---------------------------------------------

/* VkCommandBuffer conversion operator */
vulkan::command_buffer::operator const vk::command_buffer&(void) const noexcept {
	return _buffer;
}


// -- public methods ----------------------------------------------------------

/* begin */
auto vulkan::command_buffer::begin(void) const -> void {
	// begin command buffer
	vk::begin_command_buffer(_buffer, vk::command_buffer_begin_info{
		// type of structure
		.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		// pointer to next structure
		.pNext            = nullptr,
		// flags
		.flags            = 0,
		// pointer to inheritance info for secondary command buffers
		.pInheritanceInfo = nullptr
	});
}

/* end */
auto vulkan::command_buffer::end(void) const -> void {
	vk::end_command_buffer(_buffer);
}

/* renderpass begin */
auto vulkan::command_buffer::renderpass_begin(const vulkan::swapchain& swapchain,
											  const vulkan::render_pass& renderpass) const noexcept -> void {

	// clear color
	const vk::clear_value clear{
		.color = vk::clear_color_value{
			.float32 = {0.2f, 0.2f, 0.2f, 1.0f}
		}
	};

	// begin render pass
	vk::cmd_begin_render_pass(_buffer, vk::render_pass_begin_info{
		.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext           = nullptr,
		// renderpass
		.renderPass      = renderpass,
		// framebuffer from swapchain !!! (not implemented)
		.framebuffer     = VK_NULL_HANDLE,
		.renderArea      = vk::rect2D{
			.offset = vk::offset2D{0, 0},
			// swapchain extent
			.extent = swapchain.extent()
		},
		.clearValueCount = 1,
		.pClearValues    = &clear
	// primary command buffer or secondary command buffer ?
	}, VK_SUBPASS_CONTENTS_INLINE);
}


/* bind compute pipeline */
auto vulkan::command_buffer::bind_compute_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
	vk::cmd_bind_pipeline(_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
}

/* bind graphics pipeline */
auto vulkan::command_buffer::bind_graphics_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
	vk::cmd_bind_pipeline(_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

/* bind execution graph amdx pipeline */
#ifdef VK_ENABLE_BETA_EXTENSIONS
auto vulkan::command_buffer::bind_execution_graph_amdx_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
	vk::cmd_bind_pipeline(_buffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline); }
#endif

/* bind ray tracing pipeline */
auto vulkan::command_buffer::bind_ray_tracing_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
	vk::cmd_bind_pipeline(_buffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline);
}

/* bind subpass shading huawei pipeline */
auto vulkan::command_buffer::bind_subpass_shading_huawei_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
	vk::cmd_bind_pipeline(_buffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline);
}

/* draw */
auto vulkan::command_buffer::draw(const vk::u32 vertex_count,
								  const vk::u32 instance_count,
								  const vk::u32 first_vertex,
								  const vk::u32 first_instance) const noexcept -> void {
	vk::cmd_draw(_buffer, vertex_count, instance_count, first_vertex, first_instance);
}

/* renderpass end */
auto vulkan::command_buffer::renderpass_end(void) const noexcept -> void {
	vk::cmd_end_render_pass(_buffer);
}




// -- private static methods --------------------------------------------------


/* create buffers */
auto vulkan::command_buffer::create_buffers(const vulkan::logical_device& device,
											const vulkan::command_pool& pool,
											const ::uint32_t count) -> xns::vector<self> {
	// create info
	//const auto info = self::create_info(pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, count);
	//// allocate vector of command buffers
	//xns::vector<self> buffers{};
	//buffers.resize(count);
	//// get data pointer
	//auto data = reinterpret_cast<::VkCommandBuffer*>(buffers.data());
	//// allocate command buffers
	//if (::vkAllocateCommandBuffers(device, &info, data) != VK_SUCCESS)
	//	throw engine::exception{"failed to allocate command buffers"};
	//// return vector
	//return buffers;
	return {};
}

