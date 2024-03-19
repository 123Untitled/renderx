#include "vulkan_command_buffer.hpp"

#include <vulkan/vulkan.h>

// -- private lifecycle -------------------------------------------------------

/* logical device and command pool constructor */
vulkan::command_buffer::command_buffer(const vk::shared<vk::command_pool>& pool,
									   const vk::u32 size)
// create command buffer
: _buffer{pool, size, vk::command_buffer_info{
		// type of structure
		.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		// pointer to next structure
		.pNext              = nullptr,
		// command pool from which buffers are allocated
		.commandPool        = pool,
		// level of command buffer (primary or secondary)
		.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		// number of command buffers to allocate
		.commandBufferCount = size
	}} {

    // VK_COMMAND_BUFFER_LEVEL_PRIMARY
	// peut être envoyé à une queue pour y être exécuté
	// mais ne peut être appelé par d'autres command buffers
    // VK_COMMAND_BUFFER_LEVEL_SECONDARY
	// ne peut pas être directement émis à une queue
	// mais peut être appelé par un autre command buffer

}


// -- public accessors --------------------------------------------------------

/* size */
auto vulkan::command_buffer::size(void) const noexcept -> vk::u32 {
	return _buffer.size();
}


// -- public methods ----------------------------------------------------------

/* begin */
auto vulkan::command_buffer::begin(void) const -> void {

	vk::command_buffer_begin_info info {
			// type of structure
			.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			// pointer to next structure
			.pNext            = nullptr,
			// flags
			.flags            = 0,
			// pointer to inheritance info for secondary command buffers
			.pInheritanceInfo = nullptr
	};

	/* flags:
	 * VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT 
		le command buffer sera ré-enregistré après son utilisation, donc invalidé une fois son exécution terminée
     * VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
		ce command buffer secondaire sera intégralement exécuté dans une unique render pass
	 * VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
		le command buffer peut être ré-envoyé à la queue alors qu'il y est déjà et/ou est en cours d'exécution
	 */


	vk::command_buffer buffer = _buffer;

	// loop over command buffers
	for (vk::u32 i = 0; i < _buffer.size(); ++i) {
		// begin command buffer
		vk::begin_command_buffer((&buffer)[i], info);
	}


}

/* end */
auto vulkan::command_buffer::end(void) const -> void {
	vk::end_command_buffer(_buffer);
}

/* renderpass begin */
auto vulkan::command_buffer::renderpass_begin(const vulkan::swapchain& swapchain,
											  const vulkan::render_pass& render_pass) const noexcept -> void {

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
		.renderPass      = render_pass,
		// framebuffer from swapchain !!! (not implemented)
		.framebuffer     = VK_NULL_HANDLE,
		.renderArea      = vk::rect2D{.offset = vk::offset2D{0, 0},
									  .extent = swapchain.extent()},
		.clearValueCount = 1,
		.pClearValues    = &clear
	// primary command buffer or secondary command buffer ?
	}, VK_SUBPASS_CONTENTS_INLINE);
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
