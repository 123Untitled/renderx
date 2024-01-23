#ifndef ENGINE_VK_DESTROY_HPP
#define ENGINE_VK_DESTROY_HPP

#include "vk_typedefs.hpp"
#include "vk_functions.hpp"

#define pretty std::cout << __PRETTY_FUNCTION__ << std::endl

// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- D E S T R O Y -------------------------------------------------------

	/* destroy instance */
	inline auto destroy(const vk::instance& instance) noexcept -> void {
		::vkDestroyInstance(instance, nullptr);
	}

	/* destroy device */
	inline auto destroy(const vk::device& device) noexcept -> void {
		::vkDestroyDevice(device, nullptr);
	}

	/* destroy framebuffer */
	inline auto destroy(const vk::device& device,
						const vk::framebuffer& framebuffer) noexcept -> void {
		::vkDestroyFramebuffer(device, framebuffer, nullptr);
	}

	inline auto destroy(const vk::framebuffer& framebuffer,
						const vk::device& device) noexcept -> void {
		::vkDestroyFramebuffer(device, framebuffer, nullptr);
	}



	/* destroy surface */
	inline auto destroy(const vk::instance& instance,
						const vk::surface& surface) noexcept -> void {
		::vkDestroySurfaceKHR(instance, surface, nullptr);
	}

	inline auto destroy(const vk::surface& surface,
						const vk::instance& instance) noexcept -> void {
		::vkDestroySurfaceKHR(instance, surface, nullptr);
	}


	/* destroy swapchain */
	inline auto destroy(const vk::device& device,
						const vk::swapchain& swapchain) noexcept -> void {
		::vkDestroySwapchainKHR(device, swapchain, nullptr);
	}

	inline auto destroy(const vk::swapchain& swapchain,
						const vk::device& device) noexcept -> void {
		::vkDestroySwapchainKHR(device, swapchain, nullptr);
	}


	// -- semaphore -----------------------------------------------------------

	/* destroy semaphore */
	inline auto destroy(const vk::device& device,
						const vk::semaphore& semaphore) noexcept -> void {
		::vkDestroySemaphore(device, semaphore, nullptr);
	}

	/* destroy semaphore */
	inline auto destroy(const vk::semaphore& semaphore,
						const vk::device& device) noexcept -> void {
		::vkDestroySemaphore(device, semaphore, nullptr);
	}


	// -- image view ----------------------------------------------------------

	/* destroy image view */
	inline auto destroy(const vk::device& device,
						const vk::image_view& view) noexcept -> void {
		::vkDestroyImageView(device, view, nullptr);
	}

	inline auto destroy(const vk::image_view& view,
						const vk::device& device) noexcept -> void {
		::vkDestroyImageView(device, view, nullptr);
	}



	// -- shader module -------------------------------------------------------

	/* destroy shader module */
	inline auto destroy(const vk::device& device,
						const vk::shader_module& module) noexcept -> void {
		::vkDestroyShaderModule(device, module, nullptr);
	}

	/* destroy shader module */
	inline auto destroy(const vk::shader_module& module,
						const vk::device& device) noexcept -> void {
		::vkDestroyShaderModule(device, module, nullptr);
	}


	// -- pipeline ------------------------------------------------------------

	/* destroy pipeline */
	inline auto destroy(const vk::device& device,
						const vk::pipeline& pipeline) noexcept -> void {
		::vkDestroyPipeline(device, pipeline, nullptr);
	}

	/* destroy pipeline */
	inline auto destroy(const vk::pipeline& pipeline,
						const vk::device& device) noexcept -> void {
		::vkDestroyPipeline(device, pipeline, nullptr);
	}

	// -- pipeline layout -----------------------------------------------------

	/* destroy pipeline layout */
	inline auto destroy(const vk::device& device,
						const vk::pipeline_layout& layout) noexcept -> void {
		::vkDestroyPipelineLayout(device, layout, nullptr);
	}

	/* destroy pipeline layout */
	inline auto destroy(const vk::pipeline_layout& layout,
						const vk::device& device) noexcept -> void {
		::vkDestroyPipelineLayout(device, layout, nullptr);
	}


	// -- command buffer ------------------------------------------------------

	/* destroy command buffer */
	inline auto destroy(const vk::device& device,
						const vk::command_pool& pool,
						const vk::command_buffer& buffer) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}

	/* destroy command buffer */
	inline auto destroy(const vk::device& device,
						const vk::command_buffer& buffer,
						const vk::command_pool& pool) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}

	/* destroy command buffer */
	inline auto destroy(const vk::command_pool& pool,
						const vk::device& device,
						const vk::command_buffer& buffer) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}

	/* destroy command buffer */
	inline auto destroy(const vk::command_pool& pool,
						const vk::command_buffer& buffer,
						const vk::device& device) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}

	/* destroy command buffer */
	inline auto destroy(const vk::command_buffer& buffer,
						const vk::device& device,
						const vk::command_pool& pool) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}

	/* destroy command buffer */
	inline auto destroy(const vk::command_buffer& buffer,
						const vk::command_pool& pool,
						const vk::device& device) noexcept -> void {
		::vkFreeCommandBuffers(device, pool, 1, &buffer);
	}


	// -- command pool --------------------------------------------------------

	/* destroy command pool */
	inline auto destroy(const vk::device& device,
						const vk::command_pool& pool) noexcept -> void {
		::vkDestroyCommandPool(device, pool, nullptr);
	}

	/* destroy command pool */
	inline auto destroy(const vk::command_pool& pool,
						const vk::device& device) noexcept -> void {
		::vkDestroyCommandPool(device, pool, nullptr);
	}


	// -- render pass ---------------------------------------------------------

	/* destroy renderpass */
	inline auto destroy(const vk::device& device,
						const vk::render_pass& renderpass) noexcept -> void {
		::vkDestroyRenderPass(device, renderpass, nullptr);
	};

	/* destroy renderpass */
	inline auto destroy(const vk::render_pass& renderpass,
						const vk::device& device) noexcept -> void {
		::vkDestroyRenderPass(device, renderpass, nullptr);
	};


	// -- destroy debug utils messenger ---------------------------------------

	/* destroy debug utils messenger */
	inline auto destroy(const vk::instance& instance,
						const vk::debug_utils_messenger& messenger) noexcept -> void {
		const auto func = vk::get_instance_proc_addr<vk::pfn_destroy_debug_utils_messenger>(
				instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func == nullptr)
			return;
			// don't throw, to keep the same behaviour as vk::destroy
			//throw vulkan::exception{"failed to get instance proc address", VK_ERROR_EXTENSION_NOT_PRESENT};
		func(instance, messenger, nullptr);
	}

	/* destroy debug utils messenger */
	inline auto destroy(const vk::debug_utils_messenger& messenger,
						const vk::instance& instance) -> void {
		vk::destroy(instance, messenger);
	}


	// -- is destroyable ------------------------------------------------------

	/* is destroyable */
	template <typename... A>
	concept is_destroyable = requires(A&&... args) {
		{ vk::destroy(xns::forward<A>(args)...) } -> xns::is_same<void>;
	};



} // namespace vk

#endif // ENGINE_VK_DESTROY_HPP
