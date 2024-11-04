#ifndef ___ve_vulkan_pipeline_dynamic_state_create_info___
#define ___ve_vulkan_pipeline_dynamic_state_create_info___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- D Y N A M I C  S T A T E --------------------------------------------

	template <unsigned N = 0U>
	class pipeline::dynamic_state final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::dynamic_state<N>;


			// -- private members ---------------------------------------------

			/* states */
			const ::vk_dynamic_state _states[N ? N : 1U];


		public:

			// -- public members ----------------------------------------------

			/* create info */
			::vk_pipeline_dynamic_state_create_info info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			dynamic_state(void) noexcept requires (N == 0U)
			: _states{},
			  info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// dynamic state count
				.dynamicStateCount = 0U,
				// pointer to dynamic states
				.pDynamicStates = nullptr} {
			}

			/* parameters constructor */
			template <typename... Ts> requires (N == sizeof...(Ts))
			dynamic_state(const Ts&... states) noexcept
			: _states{states...},
			  info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// dynamic state count
				.dynamicStateCount = N,
				// pointer to dynamic states
				.pDynamicStates = _states} {
			}

			/* copy constructor */
			dynamic_state(const self&) noexcept = default;

			/* move constructor */
			dynamic_state(self&&) noexcept = default;

			/* destructor */
			~dynamic_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;

	}; // class dynamic_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_dynamic_state_create_info___
