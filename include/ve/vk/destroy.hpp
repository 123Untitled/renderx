#ifndef ___void_engine_vk_destroy___
#define ___void_engine_vk_destroy___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- instance ------------------------------------------------------------

	/* destroy instance */
	inline auto destroy(const vk::instance& instance) noexcept -> void {

		::vk_destroy_instance(instance, nullptr);
	}


	// -- device --------------------------------------------------------------

	/* destroy device */
	inline auto destroy(const vk::device& device) noexcept -> void {

		::vk_destroy_device(device, nullptr);
	}


	// -- command pool --------------------------------------------------------

	/* destroy command pool */
	inline auto destroy(const vk::command_pool& pool) noexcept -> void {

		::vk_destroy_command_pool(
				vulkan::device::logical(), pool, nullptr);
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


	// -- image ---------------------------------------------------------------

	/* destroy image */
	inline auto destroy(const vk::image& image) noexcept -> void {

		::vk_destroy_image(
				vulkan::device::logical(), image, nullptr);
	}


	// -- image view ----------------------------------------------------------

	/* destroy image view */
	inline auto destroy(const vk::image_view& view) noexcept -> void {

		::vk_destroy_image_view(
				vulkan::device::logical(), view, nullptr);
	}


	// -- render pass ---------------------------------------------------------

	/* destroy render pass */
	inline auto destroy(const ::vk_render_pass& render_pass) noexcept -> void {

		::vk_destroy_render_pass(
				vulkan::device::logical(), render_pass, nullptr);
	}


	// -- shader module -------------------------------------------------------

	/* destroy shader module */
	inline auto destroy(const ::vk_shader_module& module) noexcept -> void {

		::vk_destroy_shader_module(
				vulkan::device::logical(), module, nullptr);
	}


	// -- pipeline ------------------------------------------------------------

	/* destroy pipeline */
	inline auto destroy(const ::vk_pipeline& pipeline) noexcept -> void {

		::vk_destroy_pipeline(
				vulkan::device::logical(), pipeline, nullptr);
	}


	// -- pipeline layout -----------------------------------------------------

	/* destroy pipeline layout */
	inline auto destroy(const ::vk_pipeline_layout& layout) noexcept -> void {

		::vk_destroy_pipeline_layout(
				vulkan::device::logical(), layout, nullptr);
	}


	// -- descriptor set layout -----------------------------------------------

	/* destroy descriptor set layout */
	inline auto destroy(const ::vk_descriptor_set_layout& layout) noexcept -> void {

		::vk_destroy_descriptor_set_layout(
				vulkan::device::logical(), layout, nullptr);
	}


	// -- descriptor pool -----------------------------------------------------

	/* destroy descriptor pool */
	inline auto destroy(const ::vk_descriptor_pool& pool) noexcept -> void {

		::vk_destroy_descriptor_pool(
				vulkan::device::logical(), pool, nullptr);
	}


	// -- fence ---------------------------------------------------------------

	/* destroy fence */
	inline auto destroy(const vk::fence& fence) noexcept -> void {

		::vk_destroy_fence(
				vulkan::device::logical(), fence, nullptr);
	}


	// -- semaphore -----------------------------------------------------------

	/* destroy semaphore */
	inline auto destroy(const vk::semaphore& semaphore) noexcept -> void {

		::vk_destroy_semaphore(
				vulkan::device::logical(), semaphore, nullptr);
	}


} // namespace vk

#endif // ___void_engine_vk_destroy___
