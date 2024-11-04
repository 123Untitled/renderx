#ifndef ___ve_vulkan_typedefs___
#define ___ve_vulkan_typedefs___

#include "ve/vulkan/vulkan.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	using u8 = ::uint8_t;
	using u16 = ::uint16_t;

	/* unsigned integer 32 type */
	using u32 = ::uint32_t;

	/* 32bit float type */
	using f32 = float;

	/* 64bit float type */
	using f64 = double;

}

/* structure type */
using vk_structure_type = VkStructureType;

/* vk flags */
using vk_flags = VkFlags;

/* bool32 */
using vk_bool32 = VkBool32;

namespace vk {


	/* device size */
	using device_size = ::VkDeviceSize;


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
	using device_create_info                 = ::VkDeviceCreateInfo;

	/* device queue info */
	using device_queue_info                  = ::VkDeviceQueueCreateInfo;


	// -- surface -------------------------------------------------------------

	/* surface */
	using surface                            = ::VkSurfaceKHR;

	/* surface format */
	using surface_format                     = ::VkSurfaceFormatKHR;

	/* color space */
	using color_space                        = ::VkColorSpaceKHR;

	/* present mode */
	using present_mode                       = ::VkPresentModeKHR;

	/* surface capabilities */
	using surface_capabilities               = ::VkSurfaceCapabilitiesKHR;

	/* wayland surface create info */
	#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
	using wayland_surface_create_info_khr    = ::VkWaylandSurfaceCreateInfoKHR;
	#endif



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


}

// -- renderpass ----------------------------------------------------------

/* renderpass */
using vk_render_pass = VkRenderPass;

/* renderpass create info */
using vk_render_pass_create_info = VkRenderPassCreateInfo;

/* renderpass begin info */
using vk_render_pass_begin_info = ::VkRenderPassBeginInfo;



namespace vk {

	// -- subpass -------------------------------------------------------------

	/* subpass description */
	using subpass_description                = ::VkSubpassDescription;

	/* subpass dependency */
	using subpass_dependency                 = ::VkSubpassDependency;

	/* subpass contents */
	using subpass_contents                   = ::VkSubpassContents;


	// -- pipeline ------------------------------------------------------------




	/* pipeline bind point */
	using pipeline_bind_point                = ::VkPipelineBindPoint;


}


// -- pipeline ----------------------------------------------------------------

/* pipeline */
using vk_pipeline = VkPipeline;

/* pipeline shader stage create info */
using vk_pipeline_shader_stage_create_info = VkPipelineShaderStageCreateInfo;

/* pipeline info */
using vk_graphics_pipeline_create_info = VkGraphicsPipelineCreateInfo;

/* pipeline layout */
using vk_pipeline_layout = VkPipelineLayout;

/* pipeline layout info */
using vk_pipeline_layout_create_info = VkPipelineLayoutCreateInfo;


/* pipeline vertex input state create info */
using vk_pipeline_vertex_input_state_create_info = VkPipelineVertexInputStateCreateInfo;

/* vertex input binding description */
using vk_vertex_input_binding_description = VkVertexInputBindingDescription;

/* vertex input rate */
using vk_vertex_input_rate = VkVertexInputRate;

/* vertex input attribute description */
using vk_vertex_input_attribute_description = VkVertexInputAttributeDescription;

/* format */
using vk_format = VkFormat;


/* pipeline input assembly state create info */
using vk_pipeline_input_assembly_state_create_info = VkPipelineInputAssemblyStateCreateInfo;

/* primitive topology */
using vk_primitive_topology = VkPrimitiveTopology;


/* pipeline tesselation state create info */
using vk_pipeline_tesselation_state_create_info = VkPipelineTessellationStateCreateInfo;


/* pipeline viewport state create info */
using vk_pipeline_viewport_state_create_info = VkPipelineViewportStateCreateInfo;


/* pipeline rasterization state create info */
using vk_pipeline_rasterization_state_create_info = VkPipelineRasterizationStateCreateInfo;

/* pipeline rasterization state create flags */
using vk_pipeline_rasterization_state_create_flags = VkPipelineRasterizationStateCreateFlags;


/* polygon mode */
using vk_polygon_mode = VkPolygonMode;

/* cull mode flags */
using vk_cull_mode_flags = VkCullModeFlags;

/* front face */
using vk_front_face = VkFrontFace;

/* pipeline multisample state create info */
using vk_pipeline_multisample_state_create_info = VkPipelineMultisampleStateCreateInfo;

/* sample count flag bits */
using vk_sample_count_flag_bits = VkSampleCountFlagBits;

/* sample count flags */
using vk_sample_count_flags = VkSampleCountFlags;

/* sample mask */
using vk_sample_mask = VkSampleMask;

/* pipeline depth stencil state create info */
using vk_pipeline_depth_stencil_state_create_info  = VkPipelineDepthStencilStateCreateInfo;

/* compare op */
using vk_compare_op = VkCompareOp;

/* stencil op */
using vk_stencil_op = VkStencilOp;

/* stencil op state */
using vk_stencil_op_state = VkStencilOpState;

/* pipeline color blend state create info */
using vk_pipeline_color_blend_state_create_info = VkPipelineColorBlendStateCreateInfo;

/* pipeline color blend attachment state */
using vk_pipeline_color_blend_attachment_state = ::VkPipelineColorBlendAttachmentState;

/* blend factor */
using vk_blend_factor = ::VkBlendFactor;

/* blend op */
using vk_blend_op = ::VkBlendOp;

/* color component flags */
using vk_color_component_flags = ::VkColorComponentFlags;



// ...


/* dynamic state */
using vk_dynamic_state = VkDynamicState;

/* pipeline dynamic state info */
using vk_pipeline_dynamic_state_create_info = VkPipelineDynamicStateCreateInfo;


namespace vk {






	/* pipeline stage flags */
	using pipeline_stage_flags               = ::VkPipelineStageFlags;


	// -- compute pipeline ----------------------------------------------------

	/* compute pipeline info */
	using compute_pipeline_info              = ::VkComputePipelineCreateInfo;

	/* compute pipeline create flags */
	using compute_pipeline_create_flags      = ::VkPipelineCreateFlags;




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


	// -- fence ---------------------------------------------------------------

	/* fence */
	using fence                              = ::VkFence;

	/* fence info */
	using fence_info                         = ::VkFenceCreateInfo;

	/* fence create flags */
	using fence_create_flags                 = ::VkFenceCreateFlags;


	// -- image ---------------------------------------------------------------

	/* image */
	using image                              = ::VkImage;

	/* image info */
	using image_info                         = ::VkImageCreateInfo;

	/* image layout */
	using image_layout                       = ::VkImageLayout;

	/* image resolve */
	using image_resolve                      = ::VkImageResolve;

	/* image subresource layers */
	using image_subresource_layers           = ::VkImageSubresourceLayers;

	/* image tiling */
	using image_tiling                       = ::VkImageTiling;

	/* image usage flags */
	using image_usage_flags                  = ::VkImageUsageFlags;

	/* image aspect flags */
	using image_aspect_flags                 = ::VkImageAspectFlags;

	/* sample count flags */
	using sample_count_flags                 = ::VkSampleCountFlags;

	/* sample count flag bits */
	using sample_count_flag_bits             = ::VkSampleCountFlagBits;


	// -- image view ----------------------------------------------------------

	/* image view */
	using image_view                         = ::VkImageView;

	/* image view info */
	using image_view_info                    = ::VkImageViewCreateInfo;


}


// -- shader module -----------------------------------------------------------

/* shader module */
using vk_shader_module
	= VkShaderModule;

/* shader module info */
using vk_shader_module_create_info
	= VkShaderModuleCreateInfo;

/* shader stage flag bits */
using vk_shader_stage_flag_bits
	= VkShaderStageFlagBits;

/* shader stage flags */
using vk_shader_stage_flags = VkShaderStageFlags;


namespace vk {
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


	// -- buffer --------------------------------------------------------------

	/* buffer */
	using buffer                             = ::VkBuffer;

	/* buffer info */
	using buffer_info                        = ::VkBufferCreateInfo;

	/* buffer usage flags */
	using buffer_usage_flags                 = ::VkBufferUsageFlags;

	/* sharing mode */
	using sharing_mode                       = ::VkSharingMode;


	// -- memory --------------------------------------------------------------

	/* device memory */
	using device_memory                      = ::VkDeviceMemory;

	/* memory requirements */
	using memory_requirements                = ::VkMemoryRequirements;

	/* physical device memory properties */
	using physical_device_memory_properties  = ::VkPhysicalDeviceMemoryProperties;

	/* memory property flags */
	using memory_property_flags              = ::VkMemoryPropertyFlags;

	/* memory allocate info */
	using memory_allocate_info               = ::VkMemoryAllocateInfo;

	/* memory map flags */
	using memory_map_flags                   = ::VkMemoryMapFlags;

	/* mapped memory range */
	using mapped_memory_range                = ::VkMappedMemoryRange;


	// -- memory barrier ------------------------------------------------------

	/* memory barrier */
	using memory_barrier                     = ::VkMemoryBarrier;

	/* image memory barrier */
	using image_memory_barrier               = ::VkImageMemoryBarrier;

	/* buffer memory barrier */
	using buffer_memory_barrier              = ::VkBufferMemoryBarrier;

	/* access flags */
	using access_flags                       = ::VkAccessFlags;



	/* dependency flags */
	using dependency_flags                   = ::VkDependencyFlags;



	// -- vertex --------------------------------------------------------------

	/* vertex input binding description */
	using vertex_input_binding_description   = ::VkVertexInputBindingDescription;

	/* vertex input attribute description */
	using vertex_input_attribute_description = ::VkVertexInputAttributeDescription;

	/* pipeline vertex input state info */
	using pipeline_vertex_input_state_info   = ::VkPipelineVertexInputStateCreateInfo;


}



/* viewport */
using vk_viewport = VkViewport;

/* rect2D */
using vk_rect2D = VkRect2D;

/* scissor */
using vk_scissor = ::vk_rect2D;

namespace vk {



	/* offset2D */
	using offset2D                           = ::VkOffset2D;

	/* offset3D */
	using offset3D                           = ::VkOffset3D;


	/* format */
	using format                             = ::VkFormat;

	/* format properties */
	using format_properties                  = ::VkFormatProperties;

	/* extent2D */
	using extent2D                           = ::VkExtent2D;

	/* extent3D */
	using extent3D                           = ::VkExtent3D;

	/* clear value */
	using clear_value                        = ::VkClearValue;

	/* clear color value */
	using clear_color_value                  = ::VkClearColorValue;



	/* sample count flag bits */
	using sample_count_flag_bits             = ::VkSampleCountFlagBits;

	/* image tiling */
	using image_tiling                       = ::VkImageTiling;

	/* format feature flags */
	using format_feature_flags               = ::VkFormatFeatureFlags;



}


// -- descriptor set ----------------------------------------------------------

/* descriptor set */
using vk_descriptor_set = VkDescriptorSet;

/* descriptor set allocate info */
using vk_descriptor_set_allocate_info = VkDescriptorSetAllocateInfo;

/* descriptor buffer info */
using vk_descriptor_buffer_info = VkDescriptorBufferInfo;

/* descriptor image info */
using vk_descriptor_image_info = ::VkDescriptorImageInfo;

/* write descriptor info */
using vk_write_descriptor_set = ::VkWriteDescriptorSet;


// -- descriptor set layout ---------------------------------------------------

/* descriptor set layout */
using vk_descriptor_set_layout = VkDescriptorSetLayout;

/* descriptor set layout binding */
using vk_descriptor_set_layout_binding = VkDescriptorSetLayoutBinding;

/* descriptor type */
using vk_descriptor_type = VkDescriptorType;

/* descriptor set layout create info */
using vk_descriptor_set_layout_create_info = VkDescriptorSetLayoutCreateInfo;


// -- descriptor pool ---------------------------------------------------------

/* descriptor pool */
using vk_descriptor_pool = VkDescriptorPool;

/* descriptor pool size */
using vk_descriptor_pool_size = VkDescriptorPoolSize;

/* descriptor pool create info */
using vk_descriptor_pool_create_info = VkDescriptorPoolCreateInfo;

/* descriptor pool create flags */
using vk_descriptor_pool_create_flags = VkDescriptorPoolCreateFlags;




namespace vk {

	// -- push constant -------------------------------------------------------

	/* push constant range */
	using push_constant_range                = ::VkPushConstantRange;




	// -- index ---------------------------------------------------------------

	/* index type */
	using index_type                         = ::VkIndexType;


} // namespace vk





// -- instance ----------------------------------------------------------------

/* create instance */
#define vk_create_instance vkCreateInstance

/* destroy instance */
#define vk_destroy_instance vkDestroyInstance

/* get instance proc addr */
#define vk_get_instance_proc_addr vkGetInstanceProcAddr


// -- device ------------------------------------------------------------------

/* create device */
#define vk_create_device vkCreateDevice

/* destroy device */
#define vk_destroy_device vkDestroyDevice

/* device wait idle */
#define vk_device_wait_idle vkDeviceWaitIdle


// -- swapchain ---------------------------------------------------------------

/* create swapchain */
#define vk_create_swapchain_khr vkCreateSwapchainKHR

/* destroy swapchain */
#define vk_destroy_swapchain_khr vkDestroySwapchainKHR


// -- surface -----------------------------------------------------------------

/* destroy surface khr */
#define vk_destroy_surface_khr vkDestroySurfaceKHR

/* get device queue */
#define vk_get_device_queue vkGetDeviceQueue

/* create wayland surface khr */
#if defined(RENDERX_OS_LINUX)
#	define vk_create_wayland_surface_khr vkCreateWaylandSurfaceKHR
#endif


// -- command pool ------------------------------------------------------------

/* create command pool */
#define vk_create_command_pool vkCreateCommandPool

/* destroy command pool */
#define vk_destroy_command_pool vkDestroyCommandPool

/* reset command pool */
#define vk_reset_command_pool vkResetCommandPool

/* trim command pool */
#define vk_trim_command_pool vkTrimCommandPool


// -- command buffer ----------------------------------------------------------

/* allocate command buffers */
#define vk_allocate_command_buffers vkAllocateCommandBuffers

/* free command buffers */
#define vk_free_command_buffers vkFreeCommandBuffers

/* reset command buffer */
#define vk_reset_command_buffer vkResetCommandBuffer

/* begin command buffer */
#define vk_begin_command_buffer vkBeginCommandBuffer

/* cmd execute commands */
#define vk_cmd_execute_commands vkCmdExecuteCommands

/* end command buffer */
#define vk_end_command_buffer vkEndCommandBuffer

/* cmd begin render pass */
#define vk_cmd_begin_render_pass vkCmdBeginRenderPass

/* cmd end render pass */
#define vk_cmd_end_render_pass vkCmdEndRenderPass

/* cmd draw */
#define vk_cmd_draw vkCmdDraw

/* cmd draw indexed */
#define vk_cmd_draw_indexed vkCmdDrawIndexed

/* cmd bind pipeline */
#define vk_cmd_bind_pipeline vkCmdBindPipeline

/* cmd bind vertex buffers */
#define vk_cmd_bind_vertex_buffers vkCmdBindVertexBuffers

/* cmd bind index buffer */
#define vk_cmd_bind_index_buffer vkCmdBindIndexBuffer

/* cmd bind descriptor sets */
#define vk_cmd_bind_descriptor_sets vkCmdBindDescriptorSets

/* cmd push constants */
#define vk_cmd_push_constants vkCmdPushConstants

/* cmd set viewport */
#define vk_cmd_set_viewport vkCmdSetViewport

/* cmd set scissor */
#define vk_cmd_set_scissor vkCmdSetScissor

/* cmd dispatch */
#define vk_cmd_dispatch vkCmdDispatch

/* cmd resolve image */
#define vk_cmd_resolve_image vkCmdResolveImage

/* cmd pipeline barrier */
#define vk_cmd_pipeline_barrier vkCmdPipelineBarrier


// -- render pass -------------------------------------------------------------

/* create render pass */
#define vk_create_render_pass vkCreateRenderPass

/* destroy render pass */
#define vk_destroy_render_pass vkDestroyRenderPass


// -- shader module -----------------------------------------------------------

/* create shader module */
#define vk_create_shader_module vkCreateShaderModule

/* destroy shader module */
#define vk_destroy_shader_module vkDestroyShaderModule


// -- pipeline ----------------------------------------------------------------

/* create pipeline */
#define vk_create_graphics_pipelines vkCreateGraphicsPipelines

/* create compute pipeline */
#define vk_create_compute_pipelines vkCreateComputePipelines

/* destroy pipeline */
#define vk_destroy_pipeline vkDestroyPipeline


// -- pipeline layout ---------------------------------------------------------

/* create pipeline layout */
#define vk_create_pipeline_layout vkCreatePipelineLayout

/* destroy pipeline layout */
#define vk_destroy_pipeline_layout vkDestroyPipelineLayout



// -- descriptor pool ---------------------------------------------------------

/* create descriptor pool */
#define vk_create_descriptor_pool vkCreateDescriptorPool

/* destroy descriptor pool */
#define vk_destroy_descriptor_pool vkDestroyDescriptorPool

/* reset descriptor pool */
#define vk_reset_descriptor_pool vkResetDescriptorPool


// -- descriptor set layout ---------------------------------------------------

/* create descriptor set layout */
#define vk_create_descriptor_set_layout vkCreateDescriptorSetLayout

/* destroy descriptor set layout */
#define vk_destroy_descriptor_set_layout vkDestroyDescriptorSetLayout


// -- descriptor sets ---------------------------------------------------------

/* allocate descriptor sets */
#define vk_allocate_descriptor_sets vkAllocateDescriptorSets

/* free descriptor sets */
#define vk_free_descriptor_sets vkFreeDescriptorSets

/* update descriptor sets */
#define vk_update_descriptor_sets vkUpdateDescriptorSets


// -- buffer ------------------------------------------------------------------

/* create buffer */
#define vk_create_buffer vkCreateBuffer

/* destroy buffer */
#define vk_destroy_buffer vkDestroyBuffer


// -- device memory -----------------------------------------------------------

/* allocate memory */
#define vk_allocate_memory vkAllocateMemory

/* free memory */
#define vk_free_memory vkFreeMemory

/* bind buffer memory */
#define vk_bind_buffer_memory vkBindBufferMemory

/* bind image memory */
#define vk_bind_image_memory vkBindImageMemory

/* map memory */
#define vk_map_memory vkMapMemory

/* unmap memory */
#define vk_unmap_memory vkUnmapMemory

/* flush mapped memory ranges */
#define vk_flush_mapped_memory_ranges vkFlushMappedMemoryRanges

/* invalidate mapped memory ranges */
#define vk_invalidate_mapped_memory_ranges vkInvalidateMappedMemoryRanges

/* get buffer memory requirements */
#define vk_get_buffer_memory_requirements vkGetBufferMemoryRequirements

/* get image memory requirements */
#define vk_get_image_memory_requirements vkGetImageMemoryRequirements

/* get physical device memory properties */
#define vk_get_physical_device_memory_properties vkGetPhysicalDeviceMemoryProperties


// -- image -------------------------------------------------------------------

/* acquire next image khr */
#define vk_acquire_next_image_khr vkAcquireNextImageKHR

/* create image */
#define vk_create_image vkCreateImage

/* destroy image */
#define vk_destroy_image vkDestroyImage


// -- image view --------------------------------------------------------------

/* create image view */
#define vk_create_image_view vkCreateImageView

/* destroy image view */
#define vk_destroy_image_view vkDestroyImageView


// -- framebuffer -------------------------------------------------------------

/* create framebuffer */
#define vk_create_framebuffer vkCreateFramebuffer

/* destroy framebuffer */
#define vk_destroy_framebuffer vkDestroyFramebuffer


// -- queue -------------------------------------------------------------------

/* submit queue */
#define vk_queue_submit vkQueueSubmit

/* present queue */
#define vk_queue_present_khr vkQueuePresentKHR


// -- fence -------------------------------------------------------------------

/* create fence */
#define vk_create_fence vkCreateFence

/* destroy fence */
#define vk_destroy_fence vkDestroyFence

/* reset fences */
#define vk_reset_fences vkResetFences

/* wait for fences */
#define vk_wait_for_fences vkWaitForFences



// -- semaphore ---------------------------------------------------------------

/* create semaphore */
#define vk_create_semaphore vkCreateSemaphore

/* destroy semaphore */
#define vk_destroy_semaphore vkDestroySemaphore


// -- physical device ---------------------------------------------------------

/* get physical device format properties */
#define vk_get_physical_device_format_properties vkGetPhysicalDeviceFormatProperties

/* get physical device queue family properties */
#define vk_get_physical_device_queue_family_properties vkGetPhysicalDeviceQueueFamilyProperties

#define vk_get_physical_device_surface_capabilities_khr vkGetPhysicalDeviceSurfaceCapabilitiesKHR
#define vk_get_physical_device_surface_support_khr vkGetPhysicalDeviceSurfaceSupportKHR
#define vk_get_physical_device_surface_formats_khr vkGetPhysicalDeviceSurfaceFormatsKHR
#define vk_get_physical_device_surface_present_modes_khr vkGetPhysicalDeviceSurfacePresentModesKHR
#define vk_get_swapchain_images_khr vkGetSwapchainImagesKHR



// -- enumerate ---------------------------------------------------------------

#define vk_enumerate_instance_extension_properties vkEnumerateInstanceExtensionProperties
#define vk_enumerate_instance_layer_properties vkEnumerateInstanceLayerProperties
#define vk_enumerate_physical_devices vkEnumeratePhysicalDevices
#define vk_enumerate_device_extension_properties vkEnumerateDeviceExtensionProperties


// -- get ---------------------------------------------------------------------



#endif // ENGINE_VK_TYPEDEFS_HEADER
