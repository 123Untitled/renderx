#ifndef ENGINE_VK_TYPEDEFS_HPP
#define ENGINE_VK_TYPEDEFS_HPP


// vulkan headers
#include <vulkan/vulkan.h>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	/* primitive topology */
	using primitive_topology                 = ::VkPrimitiveTopology;

	/* pipeline input assembly state info */
	using pipeline_input_assembly_state_info = ::VkPipelineInputAssemblyStateCreateInfo;

	/* viewport */
	using viewport                           = ::VkViewport;

	/* rect2D */
	using rect2D                             = ::VkRect2D;

	/* pipeline viewport state info */
	using pipeline_viewport_state_info       = ::VkPipelineViewportStateCreateInfo;

	/* pipeline rasterization state info */
	using pipeline_rasterization_state_info  = ::VkPipelineRasterizationStateCreateInfo;

	/* pipeline multisample state info */
	using pipeline_multisample_state_info    = ::VkPipelineMultisampleStateCreateInfo;

	/* image */
	using image                              = ::VkImage;

	/* format */
	using format                             = ::VkFormat;

	/* extent2D */
	using extent2D                           = ::VkExtent2D;

	/* device */
	using device                             = ::VkDevice;

	/* swapchain */
	using swapchain                          = ::VkSwapchainKHR;

	/* result */
	using result                             = ::VkResult;


} // namespace vk

#endif // ENGINE_VK_TYPEDEFS_HPP
