#ifndef ___ve_vulkan_pipeline_multisample_state___
#define ___ve_vulkan_pipeline_multisample_state___

#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- M U L T I S A M P L E  S T A T E ------------------------------------

	class pipeline::multisample_state final {


		public:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline::multisample_state;

			/* underlying type */
			using type = ::vk_pipeline_multisample_state_create_info;


			// -- public members ----------------------------------------------

			/* create info */
			self::type info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr multisample_state(void) noexcept
			: vk::pipeline::multisample_state{VK_SAMPLE_COUNT_1_BIT} {
			}

			/* parameters constructor */
			constexpr multisample_state(const ::vk_sample_count_flag_bits& samples) noexcept
			: info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// rasterization samples
				.rasterizationSamples = samples,
				// sample shading enable
				.sampleShadingEnable = VK_FALSE,
				// min sample shading
				.minSampleShading = 1.0f,
				// sample mask
				.pSampleMask = nullptr,
				// alpha to coverage enable
				.alphaToCoverageEnable = VK_FALSE,
				// alpha to one enable
				.alphaToOneEnable = VK_FALSE} {
			}

			/* copy constructor */
			constexpr multisample_state(const self&) noexcept = default;

			/* move constructor */
			constexpr multisample_state(self&&) noexcept = default;

			/* destructor */
			~multisample_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* rasterization samples */
			constexpr auto rasterization_samples(const ::vk_sample_count_flag_bits& samples) noexcept -> self& {
				info.rasterizationSamples = samples;
				return *this;
			}

			/* sample shading enable */
			constexpr auto sample_shading_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.sampleShadingEnable = enable;
				return *this;
			}

			/* min sample shading */
			constexpr auto min_sample_shading(const float& min) noexcept -> self& {
				info.minSampleShading = min;
				return *this;
			}

			/* sample mask */
			constexpr auto sample_mask(const ::vk_sample_mask& mask) noexcept -> self& {
				info.pSampleMask = &mask;
				return *this;
			}

			/* alpha to coverage enable */
			constexpr auto alpha_to_coverage_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.alphaToCoverageEnable = enable;
				return *this;
			}

			/* alpha to one enable */
			constexpr auto alpha_to_one_enable(const ::vk_bool32& enable) noexcept -> self& {
				info.alphaToOneEnable = enable;
				return *this;
			}

	}; // class multisample_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_multisample_state___
