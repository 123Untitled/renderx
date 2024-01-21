#include "vulkan_framebuffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::framebuffer::framebuffer(const vulkan::renderpass& renderpass,
								 ::uint32_t width, ::uint32_t height)
: _buffer{VK_NULL_HANDLE}, _device{VK_NULL_HANDLE} {

	// swapchain image views (attachments)
	xns::vector<::VkImageView> attachments{};

	::VkFramebufferCreateInfo info{};
	// structure type
	info.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info.pNext           = nullptr;
	info.flags           = 0;
	info.renderPass      = renderpass;
	// attachments (swapchain images)
	info.attachmentCount = static_cast<::uint32_t>(attachments.size());
	info.pAttachments    = attachments.data();
	info.width           = width;
	info.height          = height;
	info.layers          = 1;

	if (::vkCreateFramebuffer(nullptr /* logical device */,
				&info, nullptr, &_buffer) != VK_SUCCESS)
		throw engine::exception{"failed to create framebuffer"};
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


// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::framebuffer::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_buffer == VK_NULL_HANDLE)
		return;
	::vkDestroyFramebuffer(device, _buffer, nullptr);
	_buffer = VK_NULL_HANDLE;
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
