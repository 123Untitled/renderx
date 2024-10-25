#ifndef ___void_engine_vk_destroy___
#define ___void_engine_vk_destroy___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* destroy pipeline layout */
	inline auto destroy(const vk::pipeline_layout& layout) noexcept -> void {

		::vk_destroy_pipeline_layout(
				vulkan::device::logical(), layout, nullptr);
	}


} // namespace vk

#endif // ___void_engine_vk_destroy___
