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

#ifndef ENGINE_VK_DESTROY_HPP
#define ENGINE_VK_DESTROY_HPP

#include "engine/vk/typedefs.hpp"
#include "engine/vk/functions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- D E S T R O Y -------------------------------------------------------


	// -- instance ------------------------------------------------------------

	/* destroy instance */
	inline auto destroy(const vk::instance& ___instance) noexcept -> void {
		::vkDestroyInstance(___instance, nullptr);
	}


	// -- device --------------------------------------------------------------

	/* destroy device */
	inline auto destroy(const vk::device& ___device) noexcept -> void {
		::vkDestroyDevice(___device, nullptr);
	}


	// -- framebuffer ---------------------------------------------------------

	/* destroy framebuffer */
	inline auto destroy(const vk::device& ___device,
						const vk::framebuffer& ___framebuffer) noexcept -> void {
		::vkDestroyFramebuffer(___device, ___framebuffer, nullptr);
	}

	inline auto destroy(const vk::framebuffer& ___framebuffer,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyFramebuffer(___device, ___framebuffer, nullptr);
	}


	// -- surface -------------------------------------------------------------

	/* destroy surface */
	inline auto destroy(const vk::instance& ___instance,
						const vk::surface& ___surface) noexcept -> void {
		::vkDestroySurfaceKHR(___instance, ___surface, nullptr);
	}

	inline auto destroy(const vk::surface& ___surface,
						const vk::instance& ___instance) noexcept -> void {
		::vkDestroySurfaceKHR(___instance, ___surface, nullptr);
	}


	// -- swapchain -----------------------------------------------------------

	/* destroy swapchain */
	inline auto destroy(const vk::device& ___device,
						const vk::swapchain& ___swapchain) noexcept -> void {
		::vkDestroySwapchainKHR(___device, ___swapchain, nullptr);
	}

	inline auto destroy(const vk::swapchain& ___swapchain,
						const vk::device& ___device) noexcept -> void {
		::vkDestroySwapchainKHR(___device, ___swapchain, nullptr);
	}


	// -- semaphore -----------------------------------------------------------

	/* destroy semaphore */
	inline auto destroy(const vk::device& ___device,
						const vk::semaphore& ___semaphore) noexcept -> void {
		::vkDestroySemaphore(___device, ___semaphore, nullptr);
	}

	/* destroy semaphore */
	inline auto destroy(const vk::semaphore& ___semaphore,
						const vk::device& ___device) noexcept -> void {
		::vkDestroySemaphore(___device, ___semaphore, nullptr);
	}


	// -- image view ----------------------------------------------------------

	/* destroy image view */
	inline auto destroy(const vk::device& ___device,
						const vk::image_view& ___image_view) noexcept -> void {
		::vkDestroyImageView(___device, ___image_view, nullptr);
	}

	inline auto destroy(const vk::image_view& ___image_view,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyImageView(___device, ___image_view, nullptr);
	}



	// -- shader module -------------------------------------------------------

	/* destroy shader module */
	inline auto destroy(const vk::device& ___device,
						const vk::shader_module& ___module) noexcept -> void {
		::vkDestroyShaderModule(___device, ___module, nullptr);
	}

	/* destroy shader module */
	inline auto destroy(const vk::shader_module& ___module,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyShaderModule(___device, ___module, nullptr);
	}


	// -- pipeline ------------------------------------------------------------

	/* destroy pipeline */
	inline auto destroy(const vk::device& ___device,
						const vk::pipeline& ___pipeline) noexcept -> void {
		::vkDestroyPipeline(___device, ___pipeline, nullptr);
	}

	/* destroy pipeline */
	inline auto destroy(const vk::pipeline& ___pipeline,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyPipeline(___device, ___pipeline, nullptr);
	}


	// -- pipeline layout -----------------------------------------------------

	/* destroy pipeline layout */
	inline auto destroy(const vk::device& ___device,
						const vk::pipeline_layout& ___layout) noexcept -> void {
		::vkDestroyPipelineLayout(___device, ___layout, nullptr);
	}

	/* destroy pipeline layout */
	inline auto destroy(const vk::pipeline_layout& ___layout,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyPipelineLayout(___device, ___layout, nullptr);
	}


	// -- command pool --------------------------------------------------------

	/* destroy command pool */
	inline auto destroy(const vk::device& ___device,
						const vk::command_pool& ___pool) noexcept -> void {
		::vkDestroyCommandPool(___device, ___pool, nullptr);
	}

	/* destroy command pool */
	inline auto destroy(const vk::command_pool& ___pool,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyCommandPool(___device, ___pool, nullptr);
	}


	// -- command buffer ------------------------------------------------------

	/* destroy command buffer */
	inline auto destroy(const vk::device& ___device,
						const vk::command_pool& ___pool,
						const vk::command_buffer* ___buffer,
						const vk::u32 ___size) noexcept -> void {
		::vkFreeCommandBuffers(___device, ___pool, ___size, ___buffer);
	}


	// -- render pass ---------------------------------------------------------

	/* destroy renderpass */
	inline auto destroy(const vk::device& ___device,
						const vk::render_pass& ___renderpass) noexcept -> void {
		::vkDestroyRenderPass(___device, ___renderpass, nullptr);
	};

	/* destroy renderpass */
	inline auto destroy(const vk::render_pass& ___renderpass,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyRenderPass(___device, ___renderpass, nullptr);
	};


	// -- debug utils messenger -----------------------------------------------

	/* destroy debug utils messenger */
	inline auto destroy(const vk::instance& ___instance,
						const vk::debug_utils_messenger& ___messenger) noexcept -> void {
		const auto ___func = vk::get_instance_proc_addr<vk::pfn_destroy_debug_utils_messenger>(
				___instance, "vkDestroyDebugUtilsMessengerEXT");
		if (___func == nullptr)
			return;
			// don't throw, to keep the same behaviour as vk::destroy
			//throw vulkan::exception{"failed to get instance proc address", VK_ERROR_EXTENSION_NOT_PRESENT};
		___func(___instance, ___messenger, nullptr);
		// maybe get function at startup to avoid error in destructors
	}

	/* debug utils messenger */
	inline auto destroy(const vk::debug_utils_messenger& ___messenger,
						const vk::instance& ___instance) -> void {
		vk::destroy(___instance, ___messenger);
	}


	// -- buffer --------------------------------------------------------------

	/* destroy buffer */
	inline auto destroy(const vk::device& ___device,
						const vk::buffer& ___buffer) noexcept -> void {
		::vkDestroyBuffer(___device, ___buffer, nullptr);
	}

	/* destroy buffer */
	inline auto destroy(const vk::buffer& ___buffer,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyBuffer(___device, ___buffer, nullptr);
	}


	// -- device memory -------------------------------------------------------

	/* destroy device memory */
	inline auto destroy(const vk::device& ___device,
						const vk::device_memory& ___memory) noexcept -> void {
		::vkFreeMemory(___device, ___memory, nullptr);
	}

	/* destroy device memory */
	inline auto destroy(const vk::device_memory& ___memory,
						const vk::device& ___device) noexcept -> void {
		::vkFreeMemory(___device, ___memory, nullptr);
	}



	// -- I S  D E S T R O Y A B L E ------------------------------------------

	/* is destroyable */
	template <typename... ___params>
	concept is_destroyable = requires(___params&&... ___args) {
		{ vk::destroy(xns::forward<___params>(___args)...) } -> xns::is_same<void>;
	};


} // namespace vk

#endif // ENGINE_VK_DESTROY_HPP
