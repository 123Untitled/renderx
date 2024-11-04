#ifndef ___ve_vulkan_pipeline_tesselation_state___
#define ___ve_vulkan_pipeline_tesselation_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- T E S S E L A T I O N  S T A T E ------------------------------------

	class pipeline::tesselation_state final {


		public:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::tesselation_state;

			/* underlying type */
			using type = ::vk_pipeline_tesselation_state_create_info;


			// -- private members ---------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr tesselation_state(void) noexcept
			: vk::pipeline::tesselation_state{0U} {
			}

			/* parameters constructor */
			constexpr tesselation_state(const vk::u32& points) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// patch control points
				.patchControlPoints = points} {
			}

			/* copy constructor */
			constexpr tesselation_state(const self&) noexcept = default;

			/* move constructor */
			constexpr tesselation_state(self&&) noexcept = default;

			/* destructor */
			~tesselation_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* patch control points */
			constexpr auto patch_control_points(const vk::u32& points) noexcept -> self& {
				info.patchControlPoints = points;
				return *this;
			}

	}; // class tesselation_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_tesselation_state___
