#ifndef ENGINE_VK_FUNCTIONS_HPP
#define ENGINE_VK_FUNCTIONS_HPP


// vulkan headers
#include <vulkan/vulkan.h>
#include "vk_typedefs.hpp"
#include "exceptions.hpp"
#include "vulkan_exception.hpp"

#include <xns>
#include "vk_utils.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {




	// -- instance ------------------------------------------------------------

	/* create instance */
	inline auto create_instance(const vk::instance_info& info) -> vk::instance {
		vk::instance instance{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateInstance,
						"failed to create vulkan instance",
						&info, nullptr, &instance);
		return instance;
	}

	/* destroy instance */
	inline auto destroy_instance(vk::instance& instance) noexcept -> void {
		::vkDestroyInstance(instance, nullptr);
		instance = VK_NULL_HANDLE;
	}

	/* get instance extensions properties count */
	inline auto get_instance_extension_properties_count(const char* layer = nullptr) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get number of vulkan instance extension properties",
						layer, &count, nullptr);
		return count;
	}

	/* enumerate instance extensions properties */
	inline auto enumerate_instance_extension_properties(const char* layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto count = vk::get_instance_extension_properties_count(layer);
		vk::vector<vk::extension_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get vulkan instance extension properties",
						layer, &count, properties.data());
		return properties;
	}


	/* get instance layer properties count */
	#if defined(ENGINE_VL_DEBUG)
	inline auto get_instance_layer_properties_count(void) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get number of vulkan instance layer properties",
						&count, nullptr);
		return count;
	}
	#endif

	/* enumerate instance layer properties */
	#if defined(ENGINE_VL_DEBUG)
	inline auto enumerate_instance_layer_properties(void) -> vk::vector<vk::layer_properties> {
		auto count = vk::get_instance_layer_properties_count();
		vk::vector<vk::layer_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get vulkan instance layer properties",
						&count, properties.data());
		return properties;
	}
	#endif

	/* get instance proc address */
	template <typename F>
	inline auto get_instance_proc_addr(const vk::instance& instance, const char* name) -> F {
		auto func = ::vkGetInstanceProcAddr(instance, name);
		if (func == nullptr)
			throw vulkan::exception{"failed to get instance proc address", VK_ERROR_INITIALIZATION_FAILED};
		return reinterpret_cast<F>(func);
	}


	// -- physical devices ----------------------------------------------------

	/* get physical devices count */
	inline auto get_physical_devices_count(const vk::instance& instance) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get number of physical devices",
						instance, &count, nullptr);
		return count;
	}

	/* enumerate physical devices */
	inline auto enumerate_physical_devices(const vk::instance& instance) -> vk::vector<vk::physical_device> {
		auto count = vk::get_physical_devices_count(instance);
		vk::vector<vk::physical_device> devices;
		devices.resize(count);
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get physical devices",
						instance, &count, devices.data());
		return devices;
	}

	/* get device extension properties count */
	inline auto get_device_extension_properties_count(const vk::physical_device& device,
													  const char* layer = nullptr) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get number of vulkan device extension properties",
						device, layer, &count, nullptr);
		return count;
	}

	/* enumerate device extension properties */
	inline auto enumerate_device_extension_properties(const vk::physical_device& device,
													  const char* layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto count = vk::get_device_extension_properties_count(device, layer);
		vk::vector<vk::extension_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get vulkan device extension properties",
						device, layer, &count, properties.data());
		return properties;
	}

	/* get physical device surface capabilities */
	inline auto get_physical_device_surface_capabilities(const vk::physical_device& device,
														 const vk::surface& surface) -> vk::surface_capabilities {
		vk::surface_capabilities capabilities;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
						"failed to get physical device surface capabilities",
						device, surface, &capabilities);
		return capabilities;
	}

	/* supports swapchain */
	inline auto supports_swapchain(const vk::extension_properties& property) noexcept -> bool {
		return xns::string_view{property.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	}

	/* get physical device properties */
	inline auto get_physical_device_properties(const vk::physical_device& device) noexcept -> vk::physical_device_properties {
		vk::physical_device_properties properties;
		::vkGetPhysicalDeviceProperties(device, &properties);
		return properties;
	}

	/* get physical device features */
	inline auto get_physical_device_features(const vk::physical_device& device) noexcept -> vk::physical_device_features {
		vk::physical_device_features features;
		::vkGetPhysicalDeviceFeatures(device, &features);
		return features;
	}

	/* get physical device surface support */
	inline auto get_physical_device_surface_support(const vk::physical_device& device,
													const vk::surface& surface, vk::u32 family) -> bool {
		vk::u32 present = false;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceSupportKHR,
						"failed to get physical device surface support",
						device, family, surface, &present);
		return present == VK_TRUE;
	}


	// -- logical devices -----------------------------------------------------

	/* create device */
	inline auto create_device(const vk::physical_device& pdevice, const vk::device_info& info) -> vk::device {
		vk::device device{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateDevice,
						"failed to create logical device",
						pdevice, &info, nullptr, &device);
		return device;
	}

	/* device wait idle */
	inline auto device_wait_idle(const vk::device& device) -> void {
		vk::try_execute(::vkDeviceWaitIdle,
						"failed to wait device idle",
						device);
	}

	/* destroy device */
	inline auto destroy_device(vk::device& device) noexcept -> void {
		if (device == VK_NULL_HANDLE)
			return;
		::vkDestroyDevice(device, nullptr);
		device = VK_NULL_HANDLE;
	}


	// -- surface formats -----------------------------------------------------

	/* get physical device surface formats count */
	inline auto get_physical_device_surface_formats_count(const vk::physical_device& device,
														  const vk::surface& surface) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get number of physical device surface formats",
						device, surface, &count, nullptr);
		return count;
	}

	/* get physical device surface formats */
	inline auto get_physical_device_surface_formats(const vk::physical_device& device,
													const vk::surface& surface) -> vk::vector<vk::surface_format> {
		auto count = vk::get_physical_device_surface_formats_count(device, surface);
		vk::vector<vk::surface_format> formats;
		formats.resize(count);
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get physical device surface formats",
						device, surface, &count, formats.data());
		return formats;
	}


	/* get physical device surface present modes count */
	inline auto get_physical_device_surface_present_modes_count(const vk::physical_device& device,
																const vk::surface& surface) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get number of physical device surface present modes",
						device, surface, &count, nullptr);
		return count;
	}

	/* get physical device surface present modes */
	inline auto get_physical_device_surface_present_modes(const vk::physical_device& device,
														  const vk::surface& surface) -> vk::vector<vk::present_mode> {
		auto count = vk::get_physical_device_surface_present_modes_count(device, surface);
		vk::vector<vk::present_mode> modes;
		modes.resize(count);
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get physical device surface present modes",
						device, surface, &count, modes.data());
		return modes;
	}


	/* destroy surface */
	inline auto destroy_surface(const vk::instance& instance, vk::surface& surface) noexcept -> void {
		::vkDestroySurfaceKHR(instance, surface, nullptr);
		surface = VK_NULL_HANDLE;
	}



	// -- queue families ------------------------------------------------------

	/* get physical device queue family properties count */
	inline auto get_physical_device_queue_family_properties_count(const vk::physical_device& device) noexcept -> vk::u32 {
		vk::u32 count = 0;
		::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
		return count;
	}

	/* get physical device queue family properties */
	inline auto get_physical_device_queue_family_properties(const vk::physical_device& device) -> vk::vector<vk::queue_family_properties> {
		auto count = vk::get_physical_device_queue_family_properties_count(device);
		vk::vector<vk::queue_family_properties> properties;
		properties.resize(count);
		::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, properties.data());
		return properties;
	}


	// -- queue ---------------------------------------------------------------

	/* get device queue */
	inline auto get_device_queue(const vk::device& device, vk::u32 family, vk::u32 index = 0) noexcept -> vk::queue {
		vk::queue queue{VK_NULL_HANDLE};
		::vkGetDeviceQueue(device, family, index, &queue);
		return queue;
	}


	// -- swapchain -----------------------------------------------------------

	/* create swapchain */
	inline auto create_swapchain(const vk::device& device, const vk::swapchain_info& info) -> vk::swapchain {
		vk::swapchain swapchain{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSwapchainKHR,
						"failed to create swapchain",
						device, &info, nullptr, &swapchain);
		return swapchain;
	}

	/* destroy swapchain */
	inline auto destroy_swapchain(const vk::device& device, vk::swapchain& swapchain) noexcept -> void {
		::vkDestroySwapchainKHR(device, swapchain, nullptr);
	}

	/* get swapchain images count */
	inline auto get_swapchain_images_count(const vk::device& device, const vk::swapchain& swapchain) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkGetSwapchainImagesKHR,
						"failed to get number of swapchain images",
						device, swapchain, &count, nullptr);
		return count;
	}

	/* get swapchain images */
	inline auto get_swapchain_images(const vk::device& device, const vk::swapchain& swapchain) -> vk::vector<vk::image> {
		auto count = vk::get_swapchain_images_count(device, swapchain);
		vk::vector<vk::image> images;
		images.resize(count);
		vk::try_execute(::vkGetSwapchainImagesKHR,
						"failed to get swapchain images",
						device, swapchain, &count, images.data());
		return images;
	}


	// -- framebuffer ---------------------------------------------------------

	/* create framebuffer */
	inline auto create_framebuffer(const vk::device& device,
								   const vk::framebuffer_info& info) -> vk::framebuffer {
		vk::framebuffer framebuffer{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateFramebuffer,
						"failed to create framebuffer",
						device, &info, nullptr, &framebuffer);
		return framebuffer;
	}

	/* destroy framebuffer */
	inline auto destroy_framebuffer(const vk::device& device,
									vk::framebuffer& framebuffer) noexcept -> void {
		if (framebuffer == VK_NULL_HANDLE)
			return;
		::vkDestroyFramebuffer(device, framebuffer, nullptr);
		framebuffer = VK_NULL_HANDLE;
	}



	// -- command pool --------------------------------------------------------

	/* create command pool */
	inline auto create_command_pool(const vk::device& device, const vk::command_pool_info& info) -> vk::command_pool {
		vk::command_pool pool{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateCommandPool,
						"failed to create command pool",
						device, &info, nullptr, &pool);
		return pool;
	}

	/* destroy command pool */
	inline auto destroy_command_pool(const vk::device& device, vk::command_pool& pool) noexcept -> void {
		if (pool == VK_NULL_HANDLE)
			return;
		::vkDestroyCommandPool(device, pool, nullptr);
		pool = VK_NULL_HANDLE;
	}


	// -- command buffer ------------------------------------------------------

	/* create command buffer */
	inline auto create_command_buffer(const vk::device& device, const vk::command_buffer_info& info) -> vk::command_buffer {
		vk::command_buffer buffer{VK_NULL_HANDLE};
		vk::try_execute(::vkAllocateCommandBuffers,
						"failed to create command buffer",
						device, &info, &buffer);
		return buffer;
	}

	/* destroy command buffer */
	inline auto destroy_command_buffer(const vk::device& device,
									   const vk::command_pool& pool,
									   vk::command_buffer& buffer) noexcept -> void {
		if (buffer == VK_NULL_HANDLE)
			return;
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
		buffer = VK_NULL_HANDLE;
	}

	/* begin command buffer */
	inline auto begin_command_buffer(const vk::command_buffer& buffer,
									 const vk::command_buffer_begin_info& info) -> void {
		try_execute(::vkBeginCommandBuffer,
					"failed to begin command buffer",
					buffer, &info);
	}

	/* end command buffer */
	inline auto end_command_buffer(const vk::command_buffer& buffer) -> void {
		try_execute(::vkEndCommandBuffer,
					"failed to end command buffer",
					buffer);
	}

	/* cmd draw */
	inline auto cmd_draw(const vk::command_buffer& buffer,
						 const vk::u32 vertex_count,
						 const vk::u32 instance_count,
						 const vk::u32 first_vertex,
						 const vk::u32 first_instance) noexcept -> void {
		::vkCmdDraw(buffer, vertex_count, instance_count, first_vertex, first_instance);
	}


	// -- render pass ---------------------------------------------------------

	/* create render_pass */
	inline auto create_render_pass(const vk::device& device, const vk::render_pass_info& info) -> vk::render_pass {
		vk::render_pass render_pass{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateRenderPass,
						"failed to create renderpass",
						device, &info, nullptr, &render_pass);
		return render_pass;
	}

	/* destroy renderpass */
	//inline auto destroy_renderpass(const vk::device& device, vk::renderpass& renderpass) noexcept -> void {
	//	if (renderpass == VK_NULL_HANDLE)
	//		return;
	//	::vkDestroyRenderPass(device, renderpass, nullptr);
	//	renderpass = VK_NULL_HANDLE;
	//}

	/* cmd begin render pass */
	inline auto cmd_begin_render_pass(const vk::command_buffer& buffer,
									  const vk::render_pass_begin_info& info,
									  const vk::subpass_contents& contents = VK_SUBPASS_CONTENTS_INLINE) noexcept -> void {
		::vkCmdBeginRenderPass(buffer, &info, contents);
	}

	/* cmd end render pass */
	inline auto cmd_end_render_pass(const vk::command_buffer& buffer) noexcept -> void {
		::vkCmdEndRenderPass(buffer);
	}


	// -- pipeline ------------------------------------------------------------

	/* cmd bind pipeline */
	inline auto cmd_bind_pipeline(const vk::command_buffer& buffer,
								  const vk::pipeline_bind_point& point,
								  const vk::pipeline& pipeline) noexcept -> void {
		::vkCmdBindPipeline(buffer, point, pipeline);
	}


	// -- semaphore -----------------------------------------------------------

	/* create semaphore */
	inline auto create_semaphore(const vk::device& device, const vk::semaphore_info& info) -> vk::semaphore {
		vk::semaphore semaphore{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSemaphore,
						"failed to create semaphore",
						device, &info, nullptr, &semaphore);
		return semaphore;
	}

	/* destroy semaphore */
	inline auto destroy_semaphore(const vk::device& device, vk::semaphore& semaphore) noexcept -> void {
		if (semaphore == VK_NULL_HANDLE)
			return;
		::vkDestroySemaphore(device, semaphore, nullptr);
		semaphore = VK_NULL_HANDLE;
	}


	// -- image view ----------------------------------------------------------

	/* create image view */
	inline auto create_image_view(const vk::device& device, const vk::image_view_info& info) -> vk::image_view {
		vk::image_view view{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateImageView,
						"failed to create image view",
						device, &info, nullptr, &view);
		return view;
	}

	/* destroy image view */
	inline auto destroy_image_view(const vk::device& device, vk::image_view& view) noexcept -> void {
		if (view == VK_NULL_HANDLE)
			return;
		::vkDestroyImageView(device, view, nullptr);
		view = VK_NULL_HANDLE;
	}


	// -- shader module -------------------------------------------------------

	///* destroy shader module */
	//inline auto destroy_shader_module(const vk::device& device, vk::shader_module& module) noexcept -> void {
	//	if (module == VK_NULL_HANDLE)
	//		return;
	//	::vkDestroyShaderModule(device, module, nullptr);
	//	module = VK_NULL_HANDLE;
	//}





} // namespace vk

#endif // ENGINE_VK_FUNCTIONS_HPP
