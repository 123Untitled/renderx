#ifndef ___ve_vulkan_pipeline_rasterization_state___
#define ___ve_vulkan_pipeline_rasterization_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- R A S T E R I Z A T I O N  S T A T E --------------------------------

	class pipeline::rasterization_state final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::pipeline::rasterization_state;

			/* underlying type */
			using type = ::vk_pipeline_rasterization_state_create_info;


			// -- public members ----------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr rasterization_state(void) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// depth clamp enable
				.depthClampEnable = VK_FALSE,
				// rasterizer discard enable
				.rasterizerDiscardEnable = VK_FALSE,
				// polygon mode
				.polygonMode = VK_POLYGON_MODE_LINE,
				// cull mode
				.cullMode = VK_CULL_MODE_BACK_BIT,
				// front face
				.frontFace = VK_FRONT_FACE_CLOCKWISE,
				// depth bias enable
				.depthBiasEnable = VK_FALSE,
				// depth bias constant factor
				.depthBiasConstantFactor = 0.0f,
				// depth bias clamp
				.depthBiasClamp = 0.0f,
				// depth bias slope factor
				.depthBiasSlopeFactor = 0.0f,
				// line width
				.lineWidth = 1.0f} {
			}

			/* copy constructor */
			constexpr rasterization_state(const self&) noexcept = default;

			/* move constructor */
			constexpr rasterization_state(self&&) noexcept = default;

			/* destructor */
			~rasterization_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* depth clamp enable */
			constexpr auto depth_clamp_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.depthClampEnable = enable;
				return *this;
			}

			/* rasterizer discard enable */
			constexpr auto rasterizer_discard_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.rasterizerDiscardEnable = enable;
				return *this;
			}

			/* polygon mode */
			constexpr auto polygon_mode(const ::vk_polygon_mode& mode) noexcept -> self& {
				info.polygonMode = mode;
				return *this;
			}

			/* cull mode */
			constexpr auto cull_mode(const ::vk_cull_mode_flags& mode) noexcept -> self& {
				info.cullMode = mode;
				return *this;
			}

			/* front face */
			constexpr auto front_face(const ::vk_front_face& face) noexcept -> self& {
				info.frontFace = face;
				return *this;
			}

			/* depth bias enable */
			constexpr auto depth_bias_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.depthBiasEnable = enable;
				return *this;
			}

			/* depth bias constant factor */
			constexpr auto depth_bias_constant_factor(const float& factor) noexcept -> self& {
				info.depthBiasConstantFactor = factor;
				return *this;
			}

			/* depth bias clamp */
			constexpr auto depth_bias_clamp(const float& clamp) noexcept -> self& {
				info.depthBiasClamp = clamp;
				return *this;
			}

			/* depth bias slope factor */
			constexpr auto depth_bias_slope_factor(const float& factor) noexcept -> self& {
				info.depthBiasSlopeFactor = factor;
				return *this;
			}

			/* line width */
			constexpr auto line_width(const float& width) noexcept -> self& {
				info.lineWidth = width;
				return *this;
			}

	}; // class rasterization_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_rasterization_state___
