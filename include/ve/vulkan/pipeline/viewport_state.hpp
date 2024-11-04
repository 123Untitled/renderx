#ifndef ___ve_vulkan_pipeline_viewport_state___
#define ___ve_vulkan_pipeline_viewport_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- V I E W P O R T  S T A T E ------------------------------------------

	class pipeline::viewport_state final {


		public:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::viewport_state;

			/* underlying type */
			using type = ::vk_pipeline_viewport_state_create_info;


			// -- private members ---------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr viewport_state(void) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// viewport count
				.viewportCount = 1U,
				// pointer to viewports
				.pViewports = nullptr,
				// scissor count
				.scissorCount = 1U,
				// pointer to scissors
				.pScissors = nullptr} {
			}

			/* parameters constructor */
			template <vk::u32 V, vk::u32 S>
			constexpr viewport_state(const ::vk_viewport (&viewports)[V],
									 const ::vk_rect2D (&scissors)[S]) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// viewport count
				.viewportCount = V,
				// pointer to viewports
				.pViewports = viewports,
				// scissor count
				.scissorCount = S,
				// pointer to scissors
				.pScissors = scissors} {
			}

			/* copy constructor */
			viewport_state(const self&) noexcept = default;

			/* move constructor */
			viewport_state(self&&) noexcept = default;

			/* destructor */
			~viewport_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;

	}; // class viewport_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_viewport_state___
