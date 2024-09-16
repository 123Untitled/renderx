/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VK_TYPEDEFS_HEADER
#define ENGINE_VK_TYPEDEFS_HEADER


// vulkan headers
#include <vulkan/vulkan.h>

#include <xns/vector.hpp>


//#include <vector>

// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* unsigned integer 32 type */
	using u32 = ::uint32_t;

	/* vector type */
	template <typename T>
	using vector = xns::vector<T>;


	/* result */
	using result                             = ::VkResult;

	/* bool32 */
	using bool32                             = ::VkBool32;


	/* extension properties */
	using extension_properties               = ::VkExtensionProperties;

	/* layer properties */
	using layer_properties                   = ::VkLayerProperties;


	// -- instance ------------------------------------------------------------

	/* instance */
	using instance                           = ::VkInstance;

	/* instance create flags */
	using instance_create_flags              = ::VkInstanceCreateFlags;

	/* application info */
	using application_info                   = ::VkApplicationInfo;

	/* instance info */
	using instance_info                      = ::VkInstanceCreateInfo;




	// -- swapchain -----------------------------------------------------------

	/* swapchain */
	using swapchain                          = ::VkSwapchainKHR;

	/* swapchain info */
	using swapchain_info                     = ::VkSwapchainCreateInfoKHR;


	// -- framebuffer ---------------------------------------------------------

	/* framebuffer */
	using framebuffer                        = ::VkFramebuffer;

	/* framebuffer info */
	using framebuffer_info                   = ::VkFramebufferCreateInfo;


	// -- physical device -----------------------------------------------------

	/* physical device */
	using physical_device                    = ::VkPhysicalDevice;

	/* physical device properties */
	using physical_device_properties         = ::VkPhysicalDeviceProperties;

	/* physical device type */
	using physical_device_type               = ::VkPhysicalDeviceType;

	/* physical device features */
	using physical_device_features           = ::VkPhysicalDeviceFeatures;


	// -- logical device ------------------------------------------------------

	/* device */
	using device                             = ::VkDevice;

	/* device info */
	using device_info                        = ::VkDeviceCreateInfo;

	/* device queue info */
	using device_queue_info                  = ::VkDeviceQueueCreateInfo;


	// -- surface -------------------------------------------------------------

	/* surface */
	using surface                            = ::VkSurfaceKHR;

	/* surface format */
	using surface_format                     = ::VkSurfaceFormatKHR;

	/* present mode */
	using present_mode                       = ::VkPresentModeKHR;

	/* surface capabilities */
	using surface_capabilities               = ::VkSurfaceCapabilitiesKHR;


	// -- queue family --------------------------------------------------------

	/* queue family properties */
	using queue_family_properties            = ::VkQueueFamilyProperties;

	/* queue flags */
	using queue_flags                        = ::VkQueueFlags;

	/* queue flags bits */
	using queue_flags_bits                   = ::VkQueueFlagBits;



	// -- queue ---------------------------------------------------------------

	/* queue */
	using queue                              = ::VkQueue;

	/* submit info */
	using submit_info                        = ::VkSubmitInfo;




	/* present info */
	using present_info                       = ::VkPresentInfoKHR;




	// -- command pool --------------------------------------------------------

	/* command pool */
	using command_pool                       = ::VkCommandPool;

	/* command pool info */
	using command_pool_info                  = ::VkCommandPoolCreateInfo;

	/* command pool create flags */
	using command_pool_create_flags          = ::VkCommandPoolCreateFlags;

	/* command pool reset flags */
	using command_pool_reset_flags           = ::VkCommandPoolResetFlags;

	/* command pool trim flags (reserved for future use) */
	using command_pool_trim_flags            = ::VkCommandPoolTrimFlags;


	// -- command buffer ------------------------------------------------------

	/* command buffer */
	using command_buffer                     = ::VkCommandBuffer;

	/* command buffer info */
	using command_buffer_info                = ::VkCommandBufferAllocateInfo;

	/* command buffer begin info */
	using command_buffer_begin_info          = ::VkCommandBufferBeginInfo;

	/* command buffer inheritance info */
	using command_buffer_inheritance_info    = ::VkCommandBufferInheritanceInfo;

	/* command buffer level */
	using command_buffer_level               = ::VkCommandBufferLevel;

	/* command buffer reset flags */
	using command_buffer_reset_flags         = ::VkCommandBufferResetFlags;


	// -- renderpass ----------------------------------------------------------

	/* renderpass */
	using render_pass                        = ::VkRenderPass;

	/* renderpass info */
	using render_pass_info                    = ::VkRenderPassCreateInfo;

	/* renderpass begin info */
	using render_pass_begin_info              = ::VkRenderPassBeginInfo;


	// -- subpass -------------------------------------------------------------

	/* subpass description */
	using subpass_description                = ::VkSubpassDescription;

	/* subpass dependency */
	using subpass_dependency                 = ::VkSubpassDependency;

	/* subpass contents */
	using subpass_contents                   = ::VkSubpassContents;


	// -- pipeline ------------------------------------------------------------

	/* pipeline */
	using pipeline                           = ::VkPipeline;

	/* pipeline info */
	using pipeline_info                      = ::VkGraphicsPipelineCreateInfo;

	/* pipeline layout */
	using pipeline_layout                    = ::VkPipelineLayout;

	/* pipeline layout info */
	using pipeline_layout_info               = ::VkPipelineLayoutCreateInfo;

	/* graphics pipeline info */
	using graphics_pipeline_info             = ::VkGraphicsPipelineCreateInfo;


	/* pipeline bind point */
	using pipeline_bind_point                = ::VkPipelineBindPoint;


	/* pipeline shader stage info */
	using pipeline_shader_stage_info         = ::VkPipelineShaderStageCreateInfo;

	/* pipeline input assembly state info */
	using pipeline_input_assembly_state_info = ::VkPipelineInputAssemblyStateCreateInfo;

	/* pipeline tesselation state info */
	using pipeline_tesselation_state_info    = ::VkPipelineTessellationStateCreateInfo;

	/* pipeline viewport state info */
	using pipeline_viewport_state_info       = ::VkPipelineViewportStateCreateInfo;

	/* pipeline rasterization state info */
	using pipeline_rasterization_state_info  = ::VkPipelineRasterizationStateCreateInfo;

	/* pipeline multisample state info */
	using pipeline_multisample_state_info    = ::VkPipelineMultisampleStateCreateInfo;

	/* pipeline depth stencil state info */
	using pipeline_depth_stencil_state_info  = ::VkPipelineDepthStencilStateCreateInfo;

	/* pipeline color blend state info */
	using pipeline_color_blend_state_info    = ::VkPipelineColorBlendStateCreateInfo;

	/* pipeline color blend attachment state */
	using pipeline_color_blend_attachment_state = ::VkPipelineColorBlendAttachmentState;

	/* dynamic state */
	using dynamic_state                      = ::VkDynamicState;

	/* pipeline dynamic state info */
	using pipeline_dynamic_state_info        = ::VkPipelineDynamicStateCreateInfo;


	/* pipeline stage flags */
	using pipeline_stage_flags               = ::VkPipelineStageFlags;

	/* primitive topology */
	using primitive_topology                  = ::VkPrimitiveTopology;




	// -- attachment ----------------------------------------------------------

	/* attachment description */
	using attachment_description             = ::VkAttachmentDescription;

	/* attachment reference */
	using attachment_reference               = ::VkAttachmentReference;


	// -- semaphore -----------------------------------------------------------

	/* semaphore */
	using semaphore                          = ::VkSemaphore;

	/* semaphore info */
	using semaphore_info                     = ::VkSemaphoreCreateInfo;


	// -- image view ----------------------------------------------------------

	/* image view */
	using image_view                         = ::VkImageView;

	/* image view info */
	using image_view_info                    = ::VkImageViewCreateInfo;


	// -- image ---------------------------------------------------------------

	/* image */
	using image                              = ::VkImage;

	/* image info */
	using image_info                         = ::VkImageCreateInfo;


	// -- shader module -------------------------------------------------------

	/* shader module */
	using shader_module                      = ::VkShaderModule;

	/* shader module info */
	using shader_module_info                 = ::VkShaderModuleCreateInfo;

	/* shader stage flag bits */
	using shader_stage_flag_bits             = ::VkShaderStageFlagBits;

	/* specialization info */
	using specialization_info                = ::VkSpecializationInfo;

	/* specialization map entry */
	using specialization_map_entry           = ::VkSpecializationMapEntry;




	// -- messenger -----------------------------------------------------------

	/* debug utils messenger */
	using debug_utils_messenger              = ::VkDebugUtilsMessengerEXT;

	/* debug utils messenger info */
	using debug_utils_messenger_info         = ::VkDebugUtilsMessengerCreateInfoEXT;

	/* pfn create debug utils messenger */
	using pfn_create_debug_utils_messenger   = ::PFN_vkCreateDebugUtilsMessengerEXT;

	/* pfn destroy debug utils messenger */
	using pfn_destroy_debug_utils_messenger  = ::PFN_vkDestroyDebugUtilsMessengerEXT;

	/* message severity */
	using debug_utils_message_severity_flag_bit = ::VkDebugUtilsMessageSeverityFlagBitsEXT;

	/* message type */
	using debug_utils_message_type_flags        = ::VkDebugUtilsMessageTypeFlagsEXT;

	/* callback data */
	using debug_utils_messenger_callback_data   = ::VkDebugUtilsMessengerCallbackDataEXT;


	// -- functions -----------------------------------------------------------

	/* pfn void function */
	using pfn_void_function                  = ::PFN_vkVoidFunction;


	// -- vertex --------------------------------------------------------------

	/* vertex input binding description */
	using vertex_input_binding_description   = ::VkVertexInputBindingDescription;

	/* vertex input attribute description */
	using vertex_input_attribute_description = ::VkVertexInputAttributeDescription;

	/* pipeline vertex input state info */
	using pipeline_vertex_input_state_info   = ::VkPipelineVertexInputStateCreateInfo;


	/* primitive topology */
	using primitive_topology                 = ::VkPrimitiveTopology;


	/* viewport */
	using viewport                           = ::VkViewport;

	/* rect2D */
	using rect2D                             = ::VkRect2D;

	/* scissor */
	using scissor = vk::rect2D;

	/* offset2D */
	using offset2D                           = ::VkOffset2D;


	/* format */
	using format                             = ::VkFormat;

	/* extent2D */
	using extent2D                           = ::VkExtent2D;

	/* clear value */
	using clear_value                        = ::VkClearValue;

	/* clear color value */
	using clear_color_value                  = ::VkClearColorValue;


} // namespace vk

#endif // ENGINE_VK_TYPEDEFS_HEADER
