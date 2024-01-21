#include "vulkan_renderpass.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::renderpass::renderpass(void)
: _renderpass{VK_NULL_HANDLE} {

	::VkAttachmentDescription attachment{
		.flags          = 0,
		.format         = VK_FORMAT_B8G8R8A8_SRGB, // here swapchain format !
		.samples        = VK_SAMPLE_COUNT_1_BIT, // here multisampling !
		.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
		// stencil
		.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		// layout (texture ?)
		.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};

	::VkAttachmentReference reference{
		.attachment = 0,
		.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	};


	::VkSubpassDescription subpass{
		.flags                   = 0,
		.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.inputAttachmentCount    = 0,
		.pInputAttachments       = nullptr,
		.colorAttachmentCount    = 1,
		.pColorAttachments       = &reference,
		.pResolveAttachments     = nullptr,
		.pDepthStencilAttachment = nullptr,
		.preserveAttachmentCount = 0,
		.pPreserveAttachments    = nullptr
	};


	const ::VkSubpassDependency dependency{
		.srcSubpass      = VK_SUBPASS_EXTERNAL,
		.dstSubpass      = 0,

		.srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask   = 0,

		.dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,

		.dependencyFlags = 0
	};


	::VkRenderPassCreateInfo info{};
	info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.pNext           = nullptr;
	info.flags           = 0;
	info.attachmentCount = 1;
	info.pAttachments    = &attachment;
	info.subpassCount    = 1;
	info.pSubpasses      = &subpass;
	info.dependencyCount = 1;
	info.pDependencies   = &dependency;


	VkDevice device{nullptr};

	if (::vkCreateRenderPass(device, &info, nullptr, &_renderpass) != VK_SUCCESS)
		throw engine::exception{"failed to create renderpass"};

}



// -- public modifiers --------------------------------------------------------

/* destroy */
auto vulkan::renderpass::destroy(const vulkan::logical_device& device) noexcept -> void {
	if (_renderpass == VK_NULL_HANDLE)
		return;
	::vkDestroyRenderPass(device, _renderpass, nullptr);
	_renderpass = VK_NULL_HANDLE;
}


// -- public conversion operators ---------------------------------------------

/* VkRenderPass conversion operator */
vulkan::renderpass::operator ::VkRenderPass(void) const noexcept {
	return _renderpass;
}



