#ifndef ___ve_vulkan_pipeline_color_blend_state___
#define ___ve_vulkan_pipeline_color_blend_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- C O L O R  B L E N D  S T A T E -------------------------------------

	class pipeline::color_blend_state final {


		private:

			// -- private members ---------------------------------------------

			/* attachments */
			std::vector<::vk_pipeline_color_blend_attachment_state> attachments;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::pipeline::color_blend_state;


			// -- public members ----------------------------------------------

			/* create info */
			::vk_pipeline_color_blend_state_create_info info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			color_blend_state(void) noexcept
			: attachments{}, info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// logic operation enable
				.logicOpEnable = VK_FALSE,
				// logic operation
				.logicOp = VK_LOGIC_OP_COPY,
				// attachment count
				.attachmentCount = 0U,
				// attachments
				.pAttachments = nullptr,
				// blend constants
				.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}} {
			}

			/* copy constructor */
			color_blend_state(const self&) = default;

			/* move constructor */
			color_blend_state(self&&) noexcept = default;

			/* destructor */
			~color_blend_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;



			// -- public modifiers --------------------------------------------

			/* attachment */
			auto attachment(const ::vk_bool32& blend_enable,
							const ::vk_blend_factor& src_color_blend_factor,
							const ::vk_blend_factor& dst_color_blend_factor,
							const ::vk_blend_op& color_blend_op,
							const ::vk_blend_factor& src_alpha_blend_factor,
							const ::vk_blend_factor& dst_alpha_blend_factor,
							const ::vk_blend_op& alpha_blend_op,
							const ::vk_color_component_flags& color_write_mask) -> self& {

				attachments.emplace_back(
						::vk_pipeline_color_blend_attachment_state{
							// blend enable
							.blendEnable = blend_enable,
							// source color blend factor
							.srcColorBlendFactor = src_color_blend_factor,
							// destination color blend factor
							.dstColorBlendFactor = dst_color_blend_factor,
							// color blend operation
							.colorBlendOp = color_blend_op,
							// source alpha blend factor
							.srcAlphaBlendFactor = src_alpha_blend_factor,
							// destination alpha blend factor
							.dstAlphaBlendFactor = dst_alpha_blend_factor,
							// alpha blend operation
							.alphaBlendOp = alpha_blend_op,
							// color write mask
							.colorWriteMask = color_write_mask});

				// update info
				info.attachmentCount = static_cast<vk::u32>(attachments.size());
				info.pAttachments = attachments.data();

				return *this;
			}

			/* attachment */
			auto attachment(void) -> self& {

				attachments.emplace_back(
						::vk_pipeline_color_blend_attachment_state{
							// blend enable
							.blendEnable = VK_FALSE,
							// source color blend factor
							.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
							// destination color blend factor
							.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
							// color blend operation
							.colorBlendOp = VK_BLEND_OP_ADD,
							// source alpha blend factor
							.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
							// destination alpha blend factor
							.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
							// alpha blend operation
							.alphaBlendOp = VK_BLEND_OP_ADD,
							// color write mask
							.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
											| VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
				});

				// update info
				info.attachmentCount = static_cast<vk::u32>(attachments.size());
				info.pAttachments = attachments.data();

				return *this;
			}
	};

} // namespace vk

#endif // ___ve_vulkan_pipeline_color_blend_state___
