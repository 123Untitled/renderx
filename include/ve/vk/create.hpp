#ifndef ___void_engine_vk_create___
#define ___void_engine_vk_create___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- descriptor sets -----------------------------------------------------

	/* create descriptor sets */
	inline auto create(const vk::descriptor_set_allocate_info& info,
						vk::descriptor_set* sets) -> vk::descriptor_set {

		vk::descriptor_set set;

		try_execute<"failed to allocate descriptor sets">(
			::vk_allocate_descriptor_sets,
			vulkan::device::logical(), &info, &set);

		return set;
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


	// -- descriptor set layout -----------------------------------------------

	/* create descriptor set layout */
	inline auto create(const vk::descriptor_set_layout_info& info) -> vk::descriptor_set_layout {

		vk::descriptor_set_layout layout;

		try_execute<"failed to create descriptor set layout">(
			::vk_create_descriptor_set_layout,
			vulkan::device::logical(), &info, nullptr, &layout);

		return layout;
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


	// -- pipeline ------------------------------------------------------------

	/* create pipeline */
	inline auto create(const vk::graphics_pipeline_info& info) -> vk::pipeline {

		vk::pipeline pipeline;

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


	// -- pipeline layout -----------------------------------------------------

	/* create pipeline layout */
	inline auto create(const vk::pipeline_layout_info& info) -> vk::pipeline_layout {

		vk::pipeline_layout layout;

		try_execute<"failed to create pipeline layout">(
			::vk_create_pipeline_layout,
			vulkan::device::logical(), &info, nullptr, &layout);

		return layout;
	}


	// -- descriptor pool -----------------------------------------------------

	/* create descriptor pool */
	inline auto create(const vk::descriptor_pool_info& info) -> vk::descriptor_pool {

		vk::descriptor_pool pool;

		try_execute<"failed to create descriptor pool">(
			::vk_create_descriptor_pool,
			vulkan::device::logical(), &info, nullptr, &pool);

		return pool;
	}



	// -- create type ---------------------------------------------------------

	/* create type */
	template <typename... Ts>
	using create_type = decltype(vk::create(std::declval<Ts>()...));

} // namespace vk

#endif // ___void_engine_vk_create___
