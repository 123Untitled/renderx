#include "vulkan_framebuffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* logical device and render pass constructor */
vulkan::framebuffer::framebuffer(const vk::shared<vk::device>& device,
								 const vulkan::render_pass& render_pass,
								 const vulkan::swapchain& swapchain)
// create framebuffer
: _buffer{device, vk::framebuffer_info{
		// structure type
		.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		// next structure
		.pNext           = nullptr,
		// flags (none)
		.flags           = 0,
		// render pass
		.renderPass      = render_pass,
		// attachment count (swapchain image views)
		.attachmentCount = swapchain.image_views_size(),
		// attachments (swapchain image views)
		.pAttachments    = swapchain.image_views_data(),
		// width
		.width           = swapchain.extent().width, 
		// height
		.height          = swapchain.extent().height,
		// layers
		.layers          = 1
	}} {
}
