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

#include "vk_typedefs.hpp"
#include "vk_utils.hpp"
#include "vk_functions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	// -- C R E A T E ---------------------------------------------------------


	// -- create instance -----------------------------------------------------

	/* create instance */
	inline auto create(const vk::instance_info& info) -> vk::instance {
		vk::instance instance{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateInstance,
					"failed to create vulkan instance",
					&info, nullptr, &instance);
		return instance;
	}


	// -- create device -------------------------------------------------------

	/* create device */
	inline auto create(const vk::physical_device& pdevice,
					   const vk::device_info& info) -> vk::device {
		vk::device device{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateDevice,
					"failed to create logical device",
					pdevice, &info, nullptr, &device);
		return device;
	}

	/* create device */
	inline auto create(const vk::device_info& info,
					   const vk::physical_device& pdevice) -> vk::device {
		return vk::create(pdevice, info);
	}


	// -- create swapchain ----------------------------------------------------

	/* create swapchain */
	inline auto create(const vk::device& device,
					   const vk::swapchain_info& info) -> vk::swapchain {
		vk::swapchain swapchain{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSwapchainKHR,
					"failed to create swapchain",
					device, &info, nullptr, &swapchain);
		return swapchain;
	}

	/* create swapchain */
	inline auto create(const vk::swapchain_info& info,
					   const vk::device& device) -> vk::swapchain {
		return vk::create(device, info);
	}



	// -- create framebuffer --------------------------------------------------

	/* create framebuffer */
	inline auto create(const vk::device& device,
					   const vk::framebuffer_info& info) -> vk::framebuffer {
		vk::framebuffer framebuffer{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateFramebuffer,
					"failed to create framebuffer",
					device, &info, nullptr, &framebuffer);
		return framebuffer;
	}

	/* create framebuffer */
	inline auto create(const vk::framebuffer_info& info,
					   const vk::device& device) -> vk::framebuffer {
		return vk::create(device, info);
	}


	// -- create command pool -------------------------------------------------

	/* create command pool */
	inline auto create(const vk::device& device,
					   const vk::command_pool_info& info) -> vk::command_pool {
		vk::command_pool pool{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateCommandPool,
					"failed to create command pool",
					device, &info, nullptr, &pool);
		return pool;
	}

	/* create command pool */
	inline auto create(const vk::command_pool_info& info,
					   const vk::device& device) -> vk::command_pool {
		return vk::create(device, info);
	}


	// -- command buffer ------------------------------------------------------

	/* create command buffer */
	inline auto create(const vk::device& device,
					   const vk::command_buffer_info& info) -> vk::command_buffer {
		vk::command_buffer buffer{VK_NULL_HANDLE};
		vk::try_execute(::vkAllocateCommandBuffers,
					"failed to allocate command buffer",
					device, &info, &buffer);
		return buffer;
	}

	/* create command buffer */
	inline auto create(const vk::command_buffer_info& info,
					   const vk::device& device) -> vk::command_buffer {
		return vk::create(device, info);
	}



	// -- render pass ---------------------------------------------------------

	/* create render pass */
	inline auto create(const vk::device& device,
					   const vk::render_pass_info& info) -> vk::render_pass {
		vk::render_pass render_pass{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateRenderPass,
					"failed to create render pass",
					device, &info, nullptr, &render_pass);
		return render_pass;
	}

	/* create render pass */
	inline auto create(const vk::render_pass_info& info,
					   const vk::device& device) -> vk::render_pass {
		return vk::create(device, info);
	}


	// -- create shader module ------------------------------------------------

	/* create shader module */
	inline auto create(const vk::device& device,
					   const vk::shader_module_info& info) -> vk::shader_module {
		vk::shader_module module{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateShaderModule,
					"failed to create shader module",
					device, &info, nullptr, &module);
		return module;
	}

	/* create shader module */
	inline auto create(const vk::shader_module_info& info,
					   const vk::device& device) -> vk::shader_module {
		return vk::create(device, info);
	}


	// -- pipeline ------------------------------------------------------------

	/* create pipeline */
	inline auto create(const vk::device& device,
					   const vk::pipeline_info& info) -> vk::pipeline {
		vk::pipeline pipeline{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateGraphicsPipelines,
					"failed to create pipeline",
					device, VK_NULL_HANDLE,  // pipeline cache
					static_cast<vk::u32>(1), // pipeline count
					&info, nullptr, &pipeline);
		return pipeline;
	}

	/* create pipeline */
	inline auto create(const vk::pipeline_info& info,
					   const vk::device& device) -> vk::pipeline {
		return vk::create(device, info);
	}


	// -- pipeline layout -----------------------------------------------------

	/* create pipeline layout */
	inline auto create(const vk::device& device,
					   const vk::pipeline_layout_info& info) -> vk::pipeline_layout {
		vk::pipeline_layout layout{VK_NULL_HANDLE};
		vk::try_execute(::vkCreatePipelineLayout,
					"failed to create pipeline layout",
					device, &info, nullptr, &layout);
		return layout;
	}

	/* create pipeline layout */
	inline auto create(const vk::pipeline_layout_info& info,
					   const vk::device& device) -> vk::pipeline_layout {
		return vk::create(device, info);
	}


	// -- create semaphore ----------------------------------------------------

	/* create semaphore */
	inline auto create(const vk::device& device,
					   const vk::semaphore_info& info) -> vk::semaphore {
		vk::semaphore semaphore{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSemaphore,
					"failed to create semaphore",
					device, &info, nullptr, &semaphore);
		return semaphore;
	}

	/* create semaphore */
	inline auto create(const vk::semaphore_info& info,
					   const vk::device& device) -> vk::semaphore {
		return vk::create(device, info);
	}


	// -- image view ----------------------------------------------------------

	/* create image view */
	inline auto create(const vk::device& device,
					   const vk::image_view_info& info) -> vk::image_view {
		vk::image_view view{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateImageView,
					"failed to create image view",
					device, &info, nullptr, &view);
		return view;
	}

	/* create image view */
	inline auto create(const vk::image_view_info& info,
					   const vk::device& device) -> vk::image_view {
		return vk::create(device, info);
	}



	// -- create debug utils messenger ----------------------------------------

	/* create debug utils messenger */
	inline auto create(const vk::instance& instance, const vk::debug_utils_messenger_info& info) -> vk::debug_utils_messenger {
		vk::debug_utils_messenger messenger{VK_NULL_HANDLE};
		const auto func = vk::get_instance_proc_addr<vk::pfn_create_debug_utils_messenger>(
				instance, "vkCreateDebugUtilsMessengerEXT");
		if (func == nullptr)
			throw vulkan::exception{"failed to get instance proc address", VK_ERROR_EXTENSION_NOT_PRESENT};
		vk::try_execute(func,
					"failed to create vulkan messenger",
					instance, &info, nullptr, &messenger);
		return messenger;
	}

	/* create debug utils messenger */
	inline auto create(const vk::debug_utils_messenger_info& info, const vk::instance& instance) -> vk::debug_utils_messenger {
		return vk::create(instance, info);
	}


	// -- is createable -------------------------------------------------------

	/* is creatable */
	template <typename T, typename... A>
	concept is_creatable = requires(A&&... args) {
		{ vk::create(xns::forward<A>(args)...) } -> xns::is_same<T>;
	};

	template <typename... A>
	using create_return = decltype(vk::create(xns::declval<A>()...));


} // namespace vk

#endif // ENGINE_VK_CREATE_HPP
