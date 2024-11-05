#ifndef ___ve_vulkan_sampler___
#define ___ve_vulkan_sampler___

#include "ve/vk/unique.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- S A M P L E R -------------------------------------------------------

	class sampler final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::sampler;


			// -- private members ---------------------------------------------

			/* sampler */
			vk::unique<::vk_sampler> _sampler;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			sampler(void)
			: _sampler{self::_create_sample()} {
			}

			/* deleted copy constructor */
			sampler(const self&) = delete;

			/* move constructor */
			sampler(self&&) noexcept = default;

			/* destructor */
			~sampler(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const vk::sampler& conversion operator */
			operator const ::vk_sampler&(void) const noexcept {
				return _sampler.get();
			}


		private:

			// -- private static methods --------------------------------------

			/* create sampler */
			static auto _create_sample(void) -> vk::unique<::vk_sampler> {

				// create info
				const ::vk_sampler_create_info info {
					// structure type
					.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
					// next structure
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// mag filter
					.magFilter = VK_FILTER_LINEAR,
					// min filter
					.minFilter = VK_FILTER_LINEAR,
					// mipmap mode
					.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
					// address mode u
					.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
					// address mode v
					.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
					// address mode w
					.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
					// mip lod bias
					.mipLodBias = 0.0f,
					// anisotropy enable
					.anisotropyEnable = VK_FALSE,
					// max anisotropy
					.maxAnisotropy = 1.0f,
					// compare enable
					.compareEnable = VK_FALSE,
					// compare op
					.compareOp = VK_COMPARE_OP_NEVER,
					// min lod
					.minLod = 0.0f,
					// max lod
					.maxLod = 0.0f,
					// border color
					.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
					// unnormalized coordinates
					.unnormalizedCoordinates = VK_FALSE
				};

				return vk::make_unique<::vk_sampler>(info);
			}


	}; // class sampler

} // namespace vk

#endif // ___ve_vulkan_sampler___
