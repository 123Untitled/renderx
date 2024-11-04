#include "ve/vulkan/command_buffer.hpp"


// -- C O M M A N D  B U F F E R ----------------------------------------------




// -- public methods ----------------------------------------------------------


/* set viewport */
auto vulkan::command_buffer::set_viewport(const vk::extent2D& extent) const noexcept -> void {

	// create viewport
	const ::vk_viewport viewport {
			.x        = 0.0f,
			.y        = 0.0f,
			.width    = static_cast<float>(extent.width),
			.height   = static_cast<float>(extent.height),
			.minDepth = 0.0f,
			.maxDepth = 1.0f
	};

	// set viewport
	::vk_cmd_set_viewport(
			// command buffer
			_buffer,
			// first viewport
			0U,
			// viewport count
			1U,
			// viewports
			&viewport);
}

/* set scissor */
auto vulkan::command_buffer::set_scissor(const vk::extent2D& extent) const noexcept -> void {

	const ::vk_rect2D scissor {
		// offset
		vk::offset2D{0, 0},
			// extent
			extent
	};

	// set scissor
	::vk_cmd_set_scissor(
			// command buffer
			_buffer,
			// first scissor
			0U,
			// scissor count
			1U,
			// scissors
			&scissor);
}

/* set viewport and scissor */
auto vulkan::command_buffer::set_viewport_and_scissor(
		const vk::extent2D& extent) const noexcept -> void {
	set_viewport(extent);
	set_scissor(extent);
}






/* bind graphics pipeline */
auto vulkan::command_buffer::bind_graphics_pipeline(const ::vk_pipeline& pipeline) const noexcept -> void {

	// bind pipeline
	::vk_cmd_bind_pipeline(
			_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

/* bind compute pipeline */
auto vulkan::command_buffer::bind_compute_pipeline(const ::vk_pipeline& pipeline) const noexcept -> void {

	// bind pipeline
	::vk_cmd_bind_pipeline(
			_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
}

/* dispatch */
auto vulkan::command_buffer::dispatch(const vk::u32 x,
									  const vk::u32 y,
									  const vk::u32 z) const noexcept -> void {

	// dispatch
	::vk_cmd_dispatch(
			_buffer, x, y, z);
}


// -- public conversion operators ---------------------------------------------

/* const vk::command_buffer& conversion operator */
vulkan::command_buffer::operator const vk::command_buffer&(void) const noexcept {
	return _buffer;
}
