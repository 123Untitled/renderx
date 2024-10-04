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

#ifndef ENGINE_VK_FUNCTIONS_HEADER
#define ENGINE_VK_FUNCTIONS_HEADER


// vulkan headers
#include <vulkan/vulkan.h>

#include "engine/vk/typedefs.hpp"
//#include "engine/exceptions.hpp"
#include "engine/vk/exception.hpp"

#include "engine/vk/utils.hpp"

#include <xns/string.hpp>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {




	/* get instance extensions properties count */
	inline auto get_instance_extension_properties_count(const char* ___layer = nullptr) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get number of vulkan instance extension properties",
						___layer, &___count, nullptr);
		return ___count;
	}

	/* enumerate instance extensions properties */
	inline auto enumerate_instance_extension_properties(const char* ___layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto ___count = vk::get_instance_extension_properties_count(___layer);
		vk::vector<vk::extension_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get vulkan instance extension properties",
						___layer, &___count, ___properties.data());
		return ___properties;
	}


	/* get instance layer properties count */
	#if defined(ENGINE_VL_DEBUG)
	inline auto get_instance_layer_properties_count(void) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get number of vulkan instance layer properties",
						&___count, nullptr);
		return ___count;
	}
	#endif

	/* enumerate instance layer properties */
	#if defined(ENGINE_VL_DEBUG)
	inline auto enumerate_instance_layer_properties(void) -> vk::vector<vk::layer_properties> {
		auto ___count = vk::get_instance_layer_properties_count();
		vk::vector<vk::layer_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get vulkan instance layer properties",
						&___count, ___properties.data());
		return ___properties;
	}
	#endif

	/* get instance proc address */
	template <typename F>
	inline auto get_instance_proc_addr(const vk::instance& ___instance, const char* ___name) -> F {
		auto ___func = ::vkGetInstanceProcAddr(___instance, ___name);
		if (___func == nullptr)
			throw vk::exception{"failed to get instance proc address", VK_ERROR_INITIALIZATION_FAILED};
		return reinterpret_cast<F>(___func);
	}


	// -- physical devices ----------------------------------------------------

	/* get physical devices count */
	inline auto get_physical_devices_count(const vk::instance& ___instance) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get number of physical devices",
						___instance, &___count, nullptr);
		return ___count;
	}

	/* enumerate physical devices */
	template <typename T>
	auto enumerate_physical_devices(const vk::instance& ___instance) -> vk::vector<T> {

		static_assert(sizeof(T) == sizeof(vk::physical_device),
					  "T must be same size as vk::physical_device");

		auto ___count = vk::get_physical_devices_count(___instance);
		vk::vector<T> ___devices;
		___devices.resize(___count);
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get physical devices",
						___instance, &___count,
						reinterpret_cast<vk::physical_device*>(___devices.data()));
		return ___devices;
	}

	/* get device extension properties count */
	inline auto get_device_extension_properties_count(const vk::physical_device& ___device,
													  const char* ___layer = nullptr) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get number of vulkan device extension properties",
						___device, ___layer, &___count, nullptr);
		return ___count;
	}

	/* enumerate device extension properties */
	inline auto enumerate_device_extension_properties(const vk::physical_device& ___device,
													  const char* ___layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto ___count = vk::get_device_extension_properties_count(___device, ___layer);
		vk::vector<vk::extension_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get vulkan device extension properties",
						___device, ___layer, &___count, ___properties.data());
		return ___properties;
	}

	/* get physical device surface capabilities */
	inline auto get_physical_device_surface_capabilities(const vk::physical_device& ___device,
														 const vk::surface& ___surface) -> vk::surface_capabilities {
		vk::surface_capabilities ___capabilities;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
						"failed to get physical device surface capabilities",
						___device, ___surface, &___capabilities);
		return ___capabilities;
	}

	/* supports swapchain */
	inline auto supports_swapchain(const vk::extension_properties& ___property) noexcept -> bool {
		return xns::string_view{___property.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	}

	/* get physical device properties */
	inline auto get_physical_device_properties(const vk::physical_device& ___device) noexcept -> vk::physical_device_properties {
		vk::physical_device_properties ___properties;
		::vkGetPhysicalDeviceProperties(___device, &___properties);
		return ___properties;
	}

	/* get physical device features */
	inline auto get_physical_device_features(const vk::physical_device& ___device) noexcept -> vk::physical_device_features {
		vk::physical_device_features ___features;
		::vkGetPhysicalDeviceFeatures(___device, &___features);
		return ___features;
	}

	/* get physical device surface support */
	inline auto get_physical_device_surface_support(const vk::physical_device& ___device,
													const vk::surface& ___surface, vk::u32 ___family) -> bool {
		vk::u32 ___present = VK_FALSE;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceSupportKHR,
						"failed to get physical device surface support",
						___device, ___family, ___surface, &___present);
		return ___present == VK_TRUE;
	}


	// -- logical devices -----------------------------------------------------

	/* device wait idle */
	inline auto device_wait_idle(const vk::device& ___device) -> void {

		vk::try_execute<"[vk::device_wait_idle] failed">(
				::vkDeviceWaitIdle,
				___device
		);
	}


	// -- surface formats -----------------------------------------------------

	/* get physical device surface formats count */
	inline auto get_physical_device_surface_formats_count(const vk::physical_device& ___device,
														  const vk::surface& ___surface) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get number of physical device surface formats",
						___device, ___surface, &___count, nullptr);
		return ___count;
	}

	/* get physical device surface formats */
	inline auto get_physical_device_surface_formats(const vk::physical_device& ___device,
													const vk::surface& ___surface) -> vk::vector<vk::surface_format> {
		auto ___count = vk::get_physical_device_surface_formats_count(___device, ___surface);
		vk::vector<vk::surface_format> ___formats;
		___formats.resize(___count);
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get physical device surface formats",
						___device, ___surface, &___count, ___formats.data());
		return ___formats;
	}


	/* get physical device surface present modes count */
	inline auto get_physical_device_surface_present_modes_count(const vk::physical_device& ___device,
																const vk::surface& ___surface) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get number of physical device surface present modes",
						___device, ___surface, &___count, nullptr);
		return ___count;
	}

	/* get physical device surface present modes */
	inline auto get_physical_device_surface_present_modes(const vk::physical_device& ___device,
														  const vk::surface& ___surface) -> vk::vector<vk::present_mode> {
		auto ___count = vk::get_physical_device_surface_present_modes_count(___device, ___surface);
		vk::vector<vk::present_mode> ___modes;
		___modes.resize(___count);
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get physical device surface present modes",
						___device, ___surface, &___count, ___modes.data());
		return ___modes;
	}


	/* destroy surface */
	inline auto destroy_surface(const vk::instance& ___instance, vk::surface& ___surface) noexcept -> void {
		::vkDestroySurfaceKHR(___instance, ___surface, nullptr);
		___surface = VK_NULL_HANDLE;
	}



	// -- queue families ------------------------------------------------------

	/* get physical device queue family properties count */
	inline auto get_physical_device_queue_family_properties_count(const vk::physical_device& ___device) noexcept -> vk::u32 {
		vk::u32 ___count = 0U;
		::vkGetPhysicalDeviceQueueFamilyProperties(___device, &___count, nullptr);
		return ___count;
	}

	/* get physical device queue family properties */
	inline auto get_physical_device_queue_family_properties(const vk::physical_device& ___device) -> vk::vector<vk::queue_family_properties> {
		auto ___count = vk::get_physical_device_queue_family_properties_count(___device);
		vk::vector<vk::queue_family_properties> ___properties;
		___properties.resize(___count);
		::vkGetPhysicalDeviceQueueFamilyProperties(___device, &___count, ___properties.data());
		return ___properties;
	}


	// -- queue ---------------------------------------------------------------

	/* get device queue */
	inline auto get_device_queue(const vk::device& ___device, vk::u32 ___family, vk::u32 ___index = 0U) noexcept -> vk::queue {
		vk::queue ___queue{VK_NULL_HANDLE};
		::vkGetDeviceQueue(___device, ___family, ___index, &___queue);
		return ___queue;
	}


	// -- swapchain -----------------------------------------------------------

	/* create swapchain */
	inline auto create_swapchain(const vk::device& ___device, const vk::swapchain_info& ___info) -> vk::swapchain {
		vk::swapchain ___swapchain{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSwapchainKHR,
						"failed to create swapchain",
						___device, &___info, nullptr, &___swapchain);
		return ___swapchain;
	}

	/* destroy swapchain */
	inline auto destroy_swapchain(const vk::device& ___device, vk::swapchain& ___swapchain) noexcept -> void {
		::vkDestroySwapchainKHR(___device, ___swapchain, nullptr);
	}

	/* get swapchain images count */
	inline auto get_swapchain_images_count(const vk::device& ___device, const vk::swapchain& ___swapchain) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute(::vkGetSwapchainImagesKHR,
						"failed to get number of swapchain images",
						___device, ___swapchain, &___count, nullptr);
		return ___count;
	}

	/* get swapchain images */
	inline auto get_swapchain_images(const vk::device& ___device, const vk::swapchain& ___swapchain) -> vk::vector<vk::image> {
		auto ___count = vk::get_swapchain_images_count(___device, ___swapchain);
		vk::vector<vk::image> ___images;
		___images.resize(___count);
		vk::try_execute(::vkGetSwapchainImagesKHR,
						"failed to get swapchain images",
						___device, ___swapchain, &___count, ___images.data());
		return ___images;
	}


	// -- command pool --------------------------------------------------------

	/* reset command pool */
	inline auto reset_command_pool(const vk::device& ___device,
								   const vk::command_pool& ___pool,
								   const vk::command_pool_reset_flags& ___flags) -> void {
		vk::try_execute(::vkResetCommandPool,
						"failed to reset command pool",
						___device, ___pool, ___flags);
	}

	/* trim command pool */
	inline auto trim_command_pool(const vk::device& ___device,
								  const vk::command_pool& ___pool) noexcept -> void {
		::vkTrimCommandPool(___device, ___pool, 0U /* reserved for future use */);
	}


	// -- command buffer ------------------------------------------------------

	/* reset command buffer */
	inline auto reset_command_buffer(const vk::command_buffer& ___buffer,
									 const vk::command_buffer_reset_flags& ___flags) -> void {
		vk::try_execute(::vkResetCommandBuffer,
						"failed to reset command buffer",
						___buffer, ___flags);
	}

	/* cmd execute commands */
	inline auto cmd_execute_commands(const vk::command_buffer& ___buffer,
									 const vk::u32 ___count,
									 const vk::command_buffer* ___buffers) noexcept -> void {
		::vkCmdExecuteCommands(___buffer, ___count, ___buffers);
	}

	/* begin command buffer */
	inline auto begin_command_buffer(const vk::command_buffer& ___buffer,
									 const vk::command_buffer_begin_info& ___info) -> void {
		try_execute(::vkBeginCommandBuffer,
					"failed to begin command buffer",
					___buffer, &___info);
	}

	/* end command buffer */
	inline auto end_command_buffer(const vk::command_buffer& ___buffer) -> void {
		vk::try_execute<"[end_command_buffer] failed">(
				::vkEndCommandBuffer,
				___buffer);
	}

	/* cmd draw */
	inline auto cmd_draw(const vk::command_buffer& ___buffer,
						 const vk::u32 ___vertex_count,
						 const vk::u32 ___instance_count,
						 const vk::u32 ___first_vertex,
						 const vk::u32 ___first_instance) noexcept -> void {
		::vkCmdDraw(___buffer, ___vertex_count, ___instance_count, ___first_vertex, ___first_instance);
	}


	/* cmd begin render pass */
	inline auto cmd_begin_render_pass(const vk::command_buffer& ___buffer,
									  const vk::render_pass_begin_info& ___info,
									  const vk::subpass_contents& ___contents = VK_SUBPASS_CONTENTS_INLINE) noexcept -> void {
		::vkCmdBeginRenderPass(___buffer, &___info, ___contents);
	}

	/* cmd end render pass */
	inline auto cmd_end_render_pass(const vk::command_buffer& ___buffer) noexcept -> void {
		::vkCmdEndRenderPass(___buffer);
	}


	// -- pipeline ------------------------------------------------------------

	/* cmd bind pipeline */
	inline auto cmd_bind_pipeline(const vk::command_buffer& ___buffer,
								  const vk::pipeline& ___pipeline,
								  const vk::pipeline_bind_point& ___point) noexcept -> void {
		::vkCmdBindPipeline(___buffer, ___point, ___pipeline);
	}


	// -- vertex buffers ------------------------------------------------------

	/* cmd bind vertex buffers */
	inline auto cmd_bind_vertex_buffers(const vk::command_buffer& ___buffer,
										const vk::u32 ___first_binding,
										const vk::u32 ___binding_count,
										const vk::buffer* ___buffers,
										const vk::device_size* ___offsets) noexcept -> void {
		::vkCmdBindVertexBuffers(___buffer, ___first_binding, ___binding_count, ___buffers, ___offsets);
	}



	// -- memory --------------------------------------------------------------

	/* get buffer memory requirements */
	inline auto get_buffer_memory_requirements(const vk::device& ___device,
											   const vk::buffer& ___buffer) -> vk::memory_requirements {
		vk::memory_requirements ___requirements;
		::vkGetBufferMemoryRequirements(___device, ___buffer, &___requirements);
		return ___requirements;
	}

	/* get physical device memory properties */
	inline auto get_physical_device_memory_properties(const vk::physical_device& ___device) -> vk::physical_device_memory_properties {
		vk::physical_device_memory_properties ___properties;
		::vkGetPhysicalDeviceMemoryProperties(___device, &___properties);
		return ___properties;
	}

	/* bind buffer memory */
	inline auto bind_buffer_memory(const vk::device& ___dev,
								   const vk::buffer& ___buf,
								   const vk::device_memory& ___mem,
								   const vk::device_size& ___sz = 0U) -> void {

		vk::try_execute<"[vk::bind_buffer_memory] failed">(
				::vkBindBufferMemory,
				___dev, ___buf, ___mem, ___sz);
	}

	/* map memory */
	inline auto map_memory(const vk::device& ___dev,
						   const vk::device_memory& ___mem,
						   const vk::device_size& ___offset,
						   const vk::device_size& ___size) -> void* {

		void* ___data;

		vk::try_execute<"[vk::map_memory] failed">(
				// function to execute
				::vkMapMemory,
				// logical device
				___dev,
				// device memory
				___mem,
				// offset
				___offset,
				// size
				___size,
				// flags (reserved for future use, not implemented yet by the Vulkan API)
				0U,
				// data pointer to store the mapped memory
				&___data);

		return ___data;
	}

	/* unmap memory */
	inline auto unmap_memory(const vk::device& ___dev, const vk::device_memory& ___mem) noexcept -> void {
		::vkUnmapMemory(___dev, ___mem);
	}




} // namespace vk

#endif // ENGINE_VK_FUNCTIONS_HEADER
