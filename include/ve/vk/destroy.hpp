#ifndef ___void_engine_vk_destroy___
#define ___void_engine_vk_destroy___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- descriptor set layout -----------------------------------------------

	/* destroy descriptor set layout */
	inline auto destroy(const vk::descriptor_set_layout& layout) noexcept -> void {

		::vk_destroy_descriptor_set_layout(
				vulkan::device::logical(), layout, nullptr);
	}


	// -- buffer --------------------------------------------------------------

	/* destroy buffer */
	inline auto destroy(const vk::buffer& buffer) noexcept -> void {

		::vk_destroy_buffer(
				vulkan::device::logical(), buffer, nullptr);
	}


	// -- swapchain -----------------------------------------------------------

	/* destroy swapchain */
	inline auto destroy(const vk::swapchain& swapchain) noexcept -> void {

		// wait for logical device to be idle
		vulkan::device::wait_idle();

		::vk_destroy_swapchain_khr(
				vulkan::device::logical(), swapchain, nullptr);
	}


	// -- pipeline ------------------------------------------------------------

	/* destroy pipeline */
	inline auto destroy(const vk::pipeline& pipeline) noexcept -> void {

		::vk_destroy_pipeline(
				vulkan::device::logical(), pipeline, nullptr);
	}


	// -- pipeline layout -----------------------------------------------------

	/* destroy pipeline layout */
	inline auto destroy(const vk::pipeline_layout& layout) noexcept -> void {

		::vk_destroy_pipeline_layout(
				vulkan::device::logical(), layout, nullptr);
	}


	// -- descriptor pool -----------------------------------------------------

	/* destroy descriptor pool */
	inline auto destroy(const vk::descriptor_pool& pool) noexcept -> void {

		::vk_destroy_descriptor_pool(
				vulkan::device::logical(), pool, nullptr);
	}


} // namespace vk

#endif // ___void_engine_vk_destroy___
