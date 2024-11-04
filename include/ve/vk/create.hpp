#ifndef ___void_engine_vk_create___
#define ___void_engine_vk_create___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- instance ------------------------------------------------------------

	/* create instance */
	inline auto create(const vk::instance_info& info) -> vk::instance {

		vk::instance instance;

		try_execute<"failed to create instance">(
			::vk_create_instance,
			&info, nullptr, &instance);

		return instance;
	}


	// -- device --------------------------------------------------------------

	/* create device */
	inline auto create(const vk::device_create_info& info) -> vk::device {

		vk::device device;

		try_execute<"failed to create device">(
			::vk_create_device,
			vulkan::device::physical(), &info, nullptr, &device);

		return device;
	}


	// -- command pool --------------------------------------------------------

	/* create command pool */
	inline auto create(const vk::command_pool_info& info) -> vk::command_pool {

		vk::command_pool pool;

		try_execute<"failed to create command pool">(
			::vk_create_command_pool,
			vulkan::device::logical(), &info, nullptr, &pool);

		return pool;
	}


	// -- buffer --------------------------------------------------------------

	/* create buffer */
	inline auto create(const vk::buffer_info& info) -> vk::buffer {

		vk::buffer buffer;

		try_execute<"failed to create buffer">(
			::vk_create_buffer,
			vulkan::device::logical(), &info, nullptr, &buffer);

		return buffer;
	}


	// -- swapchain -----------------------------------------------------------

	/* create swapchain */
	inline auto create(const vk::swapchain_info& info) -> vk::swapchain {

		vk::swapchain swapchain;

		try_execute<"failed to create swapchain">(
			::vk_create_swapchain_khr,
			vulkan::device::logical(), &info, nullptr, &swapchain);

		return swapchain;
	}


	// -- image ---------------------------------------------------------------

	/* create image */
	inline auto create(const vk::image_info& info) -> vk::image {

		vk::image image;

		try_execute<"failed to create image">(
			::vk_create_image,
			vulkan::device::logical(), &info, nullptr, &image);

		return image;
	}


	// -- image view ----------------------------------------------------------

	/* create image view */
	inline auto create(const vk::image_view_info& info) -> vk::image_view {

		vk::image_view view;

		try_execute<"failed to create image view">(
			::vk_create_image_view,
			vulkan::device::logical(), &info, nullptr, &view);

		return view;
	}


	// -- render pass ---------------------------------------------------------

	/* create render pass */
	inline auto create(const ::vk_render_pass_create_info& info) -> ::vk_render_pass {

		::vk_render_pass render_pass;

		try_execute<"failed to create render pass">(
			::vk_create_render_pass,
			vulkan::device::logical(), &info, nullptr, &render_pass);

		return render_pass;
	}


	// -- shader module -------------------------------------------------------

	/* create shader module */
	inline auto create(const ::vk_shader_module_create_info& info) -> ::vk_shader_module {

		::vk_shader_module module;

		try_execute<"failed to create shader module">(
			::vk_create_shader_module,
			vulkan::device::logical(), &info, nullptr, &module);

		return module;
	}


	// -- pipeline ------------------------------------------------------------

	/* create pipeline */
	inline auto create(const ::vk_graphics_pipeline_create_info& info) -> ::vk_pipeline {

		::vk_pipeline pipeline;

		try_execute<"failed to create graphics pipeline">(
			// function
			::vk_create_graphics_pipelines,
			// logical device
			vulkan::device::logical(),
			// pipeline cache
			nullptr,
			// create info count
			1U,
			// create info
			&info,
			// allocator
			nullptr,
			// pipeline
			&pipeline);

		return pipeline;
	}


	// -- compute pipeline ----------------------------------------------------

	/* create compute pipeline */
	inline auto create(const vk::compute_pipeline_info& info) -> ::vk_pipeline {

		::vk_pipeline pipeline;

		try_execute<"failed to create compute pipeline">(
			::vk_create_compute_pipelines,
			vulkan::device::logical(), nullptr, 1U, &info, nullptr, &pipeline);

		return pipeline;
	}


	// -- pipeline layout -----------------------------------------------------

	/* create pipeline layout */
	inline auto create(const ::vk_pipeline_layout_create_info& info) -> ::vk_pipeline_layout {

		::vk_pipeline_layout layout;

		try_execute<"failed to create pipeline layout">(
			::vk_create_pipeline_layout,
			vulkan::device::logical(), &info, nullptr, &layout);

		return layout;
	}


	// -- descriptor sets -----------------------------------------------------

	/* create descriptor sets */
	/*
	inline auto create(const vk::descriptor_set_allocate_info& info,
						vk::descriptor_set* sets) -> vk::descriptor_set {

		vk::descriptor_set set;

		try_execute<"failed to allocate descriptor sets">(
			::vk_allocate_descriptor_sets,
			vulkan::device::logical(), &info, &set);

		return set;
	}
	*/


	// -- descriptor set layout -----------------------------------------------

	/* create descriptor set layout */
	inline auto create(const ::vk_descriptor_set_layout_create_info& info) -> ::vk_descriptor_set_layout {

		::vk_descriptor_set_layout layout;

		try_execute<"failed to create descriptor set layout">(
			::vk_create_descriptor_set_layout,
			vulkan::device::logical(), &info, nullptr, &layout);

		return layout;
	}


	// -- descriptor pool -----------------------------------------------------

	/* create descriptor pool */
	inline auto create(const ::vk_descriptor_pool_create_info& info) -> ::vk_descriptor_pool {

		::vk_descriptor_pool pool;

		try_execute<"failed to create descriptor pool">(
			::vk_create_descriptor_pool,
			vulkan::device::logical(), &info, nullptr, &pool);

		return pool;
	}


	// -- fence ---------------------------------------------------------------

	/* create fence */
	inline auto create(const vk::fence_info& info) -> vk::fence {

		vk::fence fence;

		try_execute<"failed to create fence">(
			::vk_create_fence,
			vulkan::device::logical(), &info, nullptr, &fence);

		return fence;
	}


	// -- semaphore -----------------------------------------------------------

	/* create semaphore */
	inline auto create(const vk::semaphore_info& info) -> vk::semaphore {

		vk::semaphore semaphore;

		try_execute<"failed to create semaphore">(
			::vk_create_semaphore,
			vulkan::device::logical(), &info, nullptr, &semaphore);

		return semaphore;
	}



	// -- create type ---------------------------------------------------------

	/* create type */
	template <typename... Ts>
	using create_type = decltype(vk::create(std::declval<Ts>()...));

} // namespace vk

#endif // ___void_engine_vk_create___
