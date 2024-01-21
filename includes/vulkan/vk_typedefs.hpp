#ifndef ENGINE_VK_TYPEDEFS_HPP
#define ENGINE_VK_TYPEDEFS_HPP


// vulkan headers
#include <vulkan/vulkan.h>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* result */
	using result                             = ::VkResult;


	/* extension properties */
	using extension_properties               = ::VkExtensionProperties;

	/* layer properties */
	using layer_properties                   = ::VkLayerProperties;


	// -- instance ------------------------------------------------------------

	/* instance */
	using instance                           = ::VkInstance;

	/* application info */
	using application_info                   = ::VkApplicationInfo;

	/* instance info */
	using instance_info                      = ::VkInstanceCreateInfo;




	// -- swapchain -----------------------------------------------------------

	/* swapchain */
	using swapchain                          = ::VkSwapchainKHR;

	/* swapchain info */
	using swapchain_info                     = ::VkSwapchainCreateInfoKHR;


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



	// -- queue ---------------------------------------------------------------

	/* queue */
	using queue                              = ::VkQueue;

	/* submit info */
	using submit_info                        = ::VkSubmitInfo;


	// -- renderpass ----------------------------------------------------------

	/* renderpass */
	using renderpass                         = ::VkRenderPass;

	/* renderpass info */
	using renderpass_info                    = ::VkRenderPassCreateInfo;


	// -- subpass -------------------------------------------------------------

	/* subpass description */
	using subpass_description                = ::VkSubpassDescription;

	/* subpass dependency */
	using subpass_dependency                 = ::VkSubpassDependency;


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


	// -- messenger -----------------------------------------------------------

	/* debug utils messenger info */
	using debug_utils_messenger_info         = ::VkDebugUtilsMessengerCreateInfoEXT;

	/* pfn create debug utils messenger */
	using pfn_create_debug_utils_messenger   = ::PFN_vkCreateDebugUtilsMessengerEXT;

	/* pfn destroy debug utils messenger */
	using pfn_destroy_debug_utils_messenger  = ::PFN_vkDestroyDebugUtilsMessengerEXT;



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




} // namespace vk

#endif // ENGINE_VK_TYPEDEFS_HPP
