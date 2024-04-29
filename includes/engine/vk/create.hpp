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

#ifndef ENGINE_VK_CREATE_HPP
#define ENGINE_VK_CREATE_HPP

#include "engine/vk/typedefs.hpp"
#include "engine/vk/utils.hpp"
#include "engine/vk/functions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	// -- C R E A T E ---------------------------------------------------------


	// -- create instance -----------------------------------------------------

	/* create instance */
	inline auto create(const vk::instance_info& ___info) -> vk::instance {
		vk::instance __instance{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateInstance,
					"failed to create vulkan instance",
					&___info, nullptr, &__instance);
		return __instance;
	}


	// -- create device -------------------------------------------------------

	/* create device */
	inline auto create(const vk::physical_device& pdevice,
					   const vk::device_info& ___info) -> vk::device {
		vk::device ___device{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateDevice,
					"failed to create logical device",
					pdevice, &___info, nullptr, &___device);
		return ___device;
	}

	/* create device */
	inline auto create(const vk::device_info& ___info,
					   const vk::physical_device& pdevice) -> vk::device {
		return vk::create(pdevice, ___info);
	}


	// -- create swapchain ----------------------------------------------------

	/* create swapchain */
	inline auto create(const vk::device& ___device,
					   const vk::swapchain_info& ___info) -> vk::swapchain {
		vk::swapchain ___swapchain{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSwapchainKHR,
					"failed to create swapchain",
					___device, &___info, nullptr, &___swapchain);
		return ___swapchain;
	}

	/* create swapchain */
	inline auto create(const vk::swapchain_info& ___info,
					   const vk::device& ___device) -> vk::swapchain {
		return vk::create(___device, ___info);
	}



	// -- create framebuffer --------------------------------------------------

	/* create framebuffer */
	inline auto create(const vk::device& ___device,
					   const vk::framebuffer_info& ___info) -> vk::framebuffer {
		vk::framebuffer ___framebuffer{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateFramebuffer,
					"failed to create framebuffer",
					___device, &___info, nullptr, &___framebuffer);
		return ___framebuffer;
	}

	/* create framebuffer */
	inline auto create(const vk::framebuffer_info& ___info,
					   const vk::device& ___device) -> vk::framebuffer {
		return vk::create(___device, ___info);
	}


	// -- create command pool -------------------------------------------------

	/* create command pool */
	inline auto create(const vk::device& ___device,
					   const vk::command_pool_info& info) -> vk::command_pool {
		vk::command_pool pool{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateCommandPool,
					"failed to create command pool",
					___device, &info, nullptr, &pool);
		return pool;
	}

	/* create command pool */
	inline auto create(const vk::command_pool_info& info,
					   const vk::device& ___device) -> vk::command_pool {
		return vk::create(___device, info);
	}


	// -- command buffer ------------------------------------------------------

	/* create command buffer */
	inline auto create(const vk::device& ___device,
					   const vk::command_buffer_info& info) -> vk::command_buffer {
		vk::command_buffer buffer{VK_NULL_HANDLE};
		vk::try_execute(::vkAllocateCommandBuffers,
						"failed to allocate command buffer",
						___device, &info, &buffer);
		return buffer;
	}

	/* create command buffer */
	inline auto create(const vk::command_buffer_info& info,
					   const vk::device& ___device) -> vk::command_buffer {
		return vk::create(___device, info);
	}

	/* create command buffers */
	inline auto create(const vk::device& ___device,
					   const vk::command_buffer_info& info,
					   vk::command_buffer* buffers) -> vk::command_buffer* {
		vk::try_execute(::vkAllocateCommandBuffers,
						"failed to allocate command buffers",
						___device, &info, buffers);
		return buffers;
	}

	/* create command buffers */
	inline auto create(const vk::command_buffer_info& info,
					   const vk::device& ___device,
					   vk::command_buffer* buffers) -> vk::command_buffer* {
		return vk::create(___device, info, buffers);
	}

	/* create command buffers */
	inline auto create(const vk::device& ___device,
					   vk::command_buffer* buffers,
					   const vk::command_buffer_info& info) -> vk::command_buffer* {
		return vk::create(___device, info, buffers);
	}

	/* create command buffers */
	inline auto create(const vk::command_buffer_info& info,
					   vk::command_buffer* buffers,
					   const vk::device& ___device) -> vk::command_buffer* {
		return vk::create(___device, info, buffers);
	}

	/* create command buffers */
	inline auto create(vk::command_buffer* buffers,
					   const vk::device& ___device,
					   const vk::command_buffer_info& info) -> vk::command_buffer* {
		return vk::create(___device, info, buffers);
	}

	/* create command buffers */
	inline auto create(vk::command_buffer* buffers,
					   const vk::command_buffer_info& info,
					   const vk::device& ___device) -> vk::command_buffer* {
		return vk::create(___device, info, buffers);
	}



	// -- render pass ---------------------------------------------------------

	/* create render pass */
	inline auto create(const vk::device& ___device,
					   const vk::render_pass_info& ___info) -> vk::render_pass {
		vk::render_pass ___render_pass{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateRenderPass,
					"failed to create render pass",
					___device, &___info, nullptr, &___render_pass);
		return ___render_pass;
	}

	/* create render pass */
	inline auto create(const vk::render_pass_info& info,
					   const vk::device& ___device) -> vk::render_pass {
		return vk::create(___device, info);
	}


	// -- create shader module ------------------------------------------------

	/* create shader module */
	inline auto create(const vk::device& ___device,
					   const vk::shader_module_info& info) -> vk::shader_module {
		vk::shader_module module{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateShaderModule,
					"failed to create shader module",
					___device, &info, nullptr, &module);
		return module;
	}

	/* create shader module */
	inline auto create(const vk::shader_module_info& info,
					   const vk::device& ___device) -> vk::shader_module {
		return vk::create(___device, info);
	}


	// -- pipeline ------------------------------------------------------------

	/* create pipeline */
	inline auto create(const vk::device& ___device,
					   const vk::pipeline_info& ___info) -> vk::pipeline {
		vk::pipeline ___pipeline{VK_NULL_HANDLE};

		vk::try_execute<"failed to create pipeline">(
			// function
			::vkCreateGraphicsPipelines,
			// device
			___device,
			// pipeline cache
			VK_NULL_HANDLE,
			// pipeline count
			static_cast<vk::u32>(1U),
			// infos
			&___info,
			// allocator
			nullptr,
			// pipeline
			&___pipeline
		);

		return ___pipeline;
	}

	/* create pipeline */
	inline auto create(const vk::pipeline_info& info,
					   const vk::device& ___device) -> vk::pipeline {
		return vk::create(___device, info);
	}


	// -- pipeline layout -----------------------------------------------------

	/* create pipeline layout */
	inline auto create(const vk::device& ___device,
					   const vk::pipeline_layout_info& info) -> vk::pipeline_layout {
		vk::pipeline_layout layout{VK_NULL_HANDLE};
		vk::try_execute(::vkCreatePipelineLayout,
					"failed to create pipeline layout",
					___device, &info, nullptr, &layout);
		return layout;
	}

	/* create pipeline layout */
	inline auto create(const vk::pipeline_layout_info& info,
					   const vk::device& ___device) -> vk::pipeline_layout {
		return vk::create(___device, info);
	}


	// -- create semaphore ----------------------------------------------------

	/* create semaphore */
	inline auto create(const vk::device& ___device,
					   const vk::semaphore_info& ___info) -> vk::semaphore {
		vk::semaphore ___semaphore{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSemaphore,
					"failed to create semaphore",
					___device, &___info, nullptr, &___semaphore);
		return ___semaphore;
	}

	/* create semaphore */
	inline auto create(const vk::semaphore_info& info,
					   const vk::device& ___device) -> vk::semaphore {
		return vk::create(___device, info);
	}


	// -- image view ----------------------------------------------------------

	/* create image view */
	inline auto create(const vk::device& ___device,
					   const vk::image_view_info& info) -> vk::image_view {
		vk::image_view view{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateImageView,
					"failed to create image view",
					___device, &info, nullptr, &view);
		return view;
	}

	/* create image view */
	inline auto create(const vk::image_view_info& ___info,
					   const vk::device& ___device) -> vk::image_view {
		return vk::create(___device, ___info);
	}



	// -- create debug utils messenger ----------------------------------------

	/* create debug utils messenger */
	inline auto create(const vk::instance& __instance, const vk::debug_utils_messenger_info& info) -> vk::debug_utils_messenger {
		vk::debug_utils_messenger messenger{VK_NULL_HANDLE};
		const auto func = vk::get_instance_proc_addr<vk::pfn_create_debug_utils_messenger>(
				__instance, "vkCreateDebugUtilsMessengerEXT");
		if (func == nullptr)
			throw vk::exception{"failed to get instance proc address", VK_ERROR_EXTENSION_NOT_PRESENT};
		vk::try_execute(func,
					"failed to create vulkan messenger",
					__instance, &info, nullptr, &messenger);
		return messenger;
	}

	/* create debug utils messenger */
	inline auto create(const vk::debug_utils_messenger_info& info, const vk::instance& __instance) -> vk::debug_utils_messenger {
		return vk::create(__instance, info);
	}


	// -- is createable -------------------------------------------------------

	/* is creatable */
	template <typename ___type, typename... ___params>
	concept is_creatable = requires(___params&&... ___args) {
		{ vk::create(xns::forward<___params>(___args)...) } -> xns::is_same<___type>;
	};

	/* create return */
	template <typename... ___params>
	using create_return = decltype(vk::create(xns::declval<___params>()...));


} // namespace vk

#endif // ENGINE_VK_CREATE_HPP
