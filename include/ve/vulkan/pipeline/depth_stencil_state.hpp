#ifndef ___ve_vulkan_pipeline_depth_stencil_state___
#define ___ve_vulkan_pipeline_depth_stencil_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- D E P T H  S T E N C I L  S T A T E ---------------------------------

	class pipeline::depth_stencil_state final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::pipeline::depth_stencil_state;

			/* underlying type */
			using type = ::vk_pipeline_depth_stencil_state_create_info;


			// -- public members ----------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr depth_stencil_state(void) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// depth test enable
				.depthTestEnable = VK_FALSE,
				// depth write enable
				.depthWriteEnable = VK_FALSE,
				// depth compare operation
				.depthCompareOp = VK_COMPARE_OP_NEVER,
				// depth bounds test enable
				.depthBoundsTestEnable = VK_FALSE,
				// stencil test enable
				.stencilTestEnable = VK_FALSE,
				// front stencil operation
				.front = {},
				// back stencil operation
				.back = {},
				// min depth bounds
				.minDepthBounds = 0.0f,
				// max depth bounds
				.maxDepthBounds = 1.0f} {
			}

			/* copy constructor */
			constexpr depth_stencil_state(const self&) noexcept = default;

			/* move constructor */
			constexpr depth_stencil_state(self&&) noexcept = default;

			/* destructor */
			~depth_stencil_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* depth test enable */
			constexpr auto depth_test_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.depthTestEnable = enable;
				return *this;
			}

			/* depth write enable */
			constexpr auto depth_write_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.depthWriteEnable = enable;
				return *this;
			}

			/* depth compare operation */
			constexpr auto depth_compare_op(const ::vk_compare_op& op) noexcept -> self& {
				info.depthCompareOp = op;
				return *this;
			}

			/* depth bounds test enable */
			constexpr auto depth_bounds_test_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.depthBoundsTestEnable = enable;
				return *this;
			}

			/* stencil test enable */
			constexpr auto stencil_test_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.stencilTestEnable = enable;
				return *this;
			}

			/* front stencil operation */
			constexpr auto front_stencil_op(const ::vk_stencil_op_state& op) noexcept -> self& {
				info.front = op;
				return *this;
			}

			/* back stencil operation */
			constexpr auto back_stencil_op(const ::vk_stencil_op_state& op) noexcept -> self& {
				info.back = op;
				return *this;
			}

			/* min depth bounds */
			constexpr auto min_depth_bounds(const float& bounds) noexcept -> self& {
				info.minDepthBounds = bounds;
				return *this;
			}

			/* max depth bounds */
			constexpr auto max_depth_bounds(const float& bounds) noexcept -> self& {
				info.maxDepthBounds = bounds;
				return *this;
			}

	}; // class depth_stencil_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_depth_stencil_state___
