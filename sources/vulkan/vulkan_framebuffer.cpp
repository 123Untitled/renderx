#include "vulkan_framebuffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* logical device and render pass constructor */
vulkan::framebuffer::framebuffer(const vulkan::logical_device& device,
								 const vulkan::render_pass& render_pass,
								 const vulkan::swapchain& swapchain)
// create framebuffer
: _buffer{vk::create_framebuffer(device, vk::framebuffer_info{
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
	})} {
}

/* copy constructor */
vulkan::framebuffer::framebuffer(const self& other) noexcept
: _buffer{other._buffer} {
}

/* move constructor */
vulkan::framebuffer::framebuffer(self&& other) noexcept
: self{other} /* copy */ {
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::framebuffer::operator=(const self& other) noexcept -> self& {
	_buffer = other._buffer;
	return *this;
}

/* move assignment operator */
auto vulkan::framebuffer::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::framebuffer::destroy(const vulkan::logical_device& device) noexcept -> void {
	vk::destroy_framebuffer(device, _buffer);
}

