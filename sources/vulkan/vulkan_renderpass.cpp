#include "vulkan_renderpass.hpp"



// -- public lifecycle --------------------------------------------------------

/* logical device constructor */
vulkan::renderpass::renderpass(const vulkan::logical_device& device)
: _renderpass{VK_NULL_HANDLE} {

	const vk::attachment_description attachment{
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

	const vk::attachment_reference reference{
		.attachment = 0,
		.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	};


	const vk::subpass_description subpass{
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


	const vk::subpass_dependency dependency{
		.srcSubpass      = VK_SUBPASS_EXTERNAL,
		.dstSubpass      = 0,

		.srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask   = 0,

		.dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,

		.dependencyFlags = 0
	};


	const vk::renderpass_info info{
		.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pNext           = nullptr,
		.flags           = 0,
		.attachmentCount = 1,
		.pAttachments    = &attachment,
		.subpassCount    = 1,
		.pSubpasses      = &subpass,
		.dependencyCount = 1,
		.pDependencies   = &dependency,
	};


	// create renderpass
	_renderpass = vk::create_renderpass(device, info);
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



