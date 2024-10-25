#ifndef ___void_engine_vk_create___
#define ___void_engine_vk_create___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* create pipeline layout */
	inline auto create(const vk::pipeline_layout& layout,
					   const vk::pipeline_layout_info& info) noexcept -> void {

		try_execute<"failed to create pipeline layout">(
			::vk_create_pipeline_layout,
			vulkan::device::logical(), &info, nullptr, &layout);
	}


} // namespace vk

#endif // ___void_engine_vk_create___
