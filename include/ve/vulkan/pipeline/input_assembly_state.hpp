#ifndef ___ve_vulkan_pipeline_input_assembly_state___
#define ___ve_vulkan_pipeline_input_assembly_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- I N P U T  A S S E M B L Y  S T A T E -------------------------------

	class pipeline::input_assembly_state final {


		public:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::input_assembly_state;

			/* underlying type */
			using type = ::vk_pipeline_input_assembly_state_create_info;


			// -- private members ---------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr input_assembly_state(void) noexcept
			: vk::pipeline::input_assembly_state{
				VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST} {
			}

			/* parameters constructor */
			constexpr input_assembly_state(const ::vk_primitive_topology& topology,
										   const vk::bool32& restart = VK_FALSE) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved)
				.flags = 0U,
				// topology
				.topology = topology,
				// primitive restart enable
				.primitiveRestartEnable = restart} {
			}

			/* copy constructor */
			constexpr input_assembly_state(const self&) noexcept = default;

			/* move constructor */
			constexpr input_assembly_state(self&&) noexcept = default;

			/* destructor */
			~input_assembly_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* topology */
			constexpr auto topology(const ::vk_primitive_topology& topology) noexcept -> self& {
				info.topology = topology;
				return *this;
			}

			/* restart */
			constexpr auto restart(const ::vk_bool32& restart) noexcept -> self& {
				info.primitiveRestartEnable = restart;
				return *this;
			}

	}; // class input_assembly_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_input_assembly_state___
