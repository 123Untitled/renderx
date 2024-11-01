#include "ve/vulkan/command_buffer.hpp"


// -- C O M M A N D  B U F F E R ----------------------------------------------




// -- public methods ----------------------------------------------------------

/* bind graphics pipeline */
auto vulkan::command_buffer::bind_graphics_pipeline(const vk::pipeline& pipeline) const noexcept -> void {

	// bind pipeline
	::vk_cmd_bind_pipeline(
			_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

/* bind compute pipeline */
auto vulkan::command_buffer::bind_compute_pipeline(const vk::pipeline& pipeline) const noexcept -> void {

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
