#include "vulkan_framebuffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::framebuffer::framebuffer(void) noexcept
: _buffer{VK_NULL_HANDLE}, _device{VK_NULL_HANDLE} {

	::VkFramebufferCreateInfo info{};
	info.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info.pNext           = nullptr;
	info.flags           = 0;
	info.renderPass      = VK_NULL_HANDLE;
	info.attachmentCount = 0;
	info.pAttachments    = nullptr;
	info.width           = 0;
	info.height          = 0;
	info.layers          = 0;

}

/* move constructor */
vulkan::framebuffer::framebuffer(self&& other) noexcept
: _buffer{other._buffer}, _device{other._device} {
	other.init();
}

/* destructor */
vulkan::framebuffer::~framebuffer(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::framebuffer::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	_buffer = other._buffer;
	_device = other._device;
	other.init();
	return *this;
}

// -- private static methods --------------------------------------------------

/* create */
auto vulkan::framebuffer::create(::VkFramebufferCreateInfo& info) -> ::VkFramebuffer {
	::VkFramebuffer buffer{VK_NULL_HANDLE};
	if (::vkCreateFramebuffer(nullptr /* logical device */,
				&info, nullptr, &buffer) != VK_SUCCESS)
		throw engine::exception{"failed to create framebuffer"};
	return buffer;
}

// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::framebuffer::free(void) noexcept -> void {
	if (_buffer == VK_NULL_HANDLE)
		return;
	::vkDestroyFramebuffer(_device, _buffer, nullptr);
}

/* init */
auto vulkan::framebuffer::init(void) noexcept -> void {
	_buffer = VK_NULL_HANDLE;
	_device = VK_NULL_HANDLE;
}
