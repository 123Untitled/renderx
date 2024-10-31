#ifndef ___ve_vulkan_multisampling___
#define ___ve_vulkan_multisampling___

#include "ve/vulkan/image.hpp"
#include "ve/vulkan/image_view.hpp"
#include "ve/vulkan/device.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- M U L T I S A M P L I N G -------------------------------------------

	class multisampling final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::multisampling;


			// -- private members ---------------------------------------------

			/* image */
			ve::image _image;

			/* view */
			ve::image_view _view;


		public:

			// temporary, will be moved to another class
			static constexpr vk::format color_format = VK_FORMAT_B8G8R8A8_SRGB;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			multisampling(void) noexcept = default;

			/* extent constructor */
			multisampling(const vk::extent2D& extent)
			: _image{
				extent.width,
				extent.height,
				color_format,
				ve::multisampling::max(),
				VK_IMAGE_TILING_OPTIMAL,
				VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
			  _view{_image, color_format, VK_IMAGE_ASPECT_COLOR_BIT} {
			}


			// -- public accessors --------------------------------------------

			/* view */
			auto view(void) const -> const ve::image_view& {
				return static_cast<const ve::image_view&>(_view);
			}


			// -- public static methods ---------------------------------------

			/* max */
			static auto max(void) -> const vk::sample_count_flag_bits& {
				static const auto value = ve::multisampling::_max_sample_count();
				//static const auto value = VK_SAMPLE_COUNT_1_BIT;
				return value;
			}


		private:

			// -- private static methods --------------------------------------

			/* max sample count */
			static auto _max_sample_count(void) -> vk::sample_count_flag_bits {

				// get max sample count
				const auto count = vulkan::device::physical()
					.properties()
					.limits
					.framebufferColorSampleCounts;

				// 64 bit
				if (count & VK_SAMPLE_COUNT_64_BIT)
					return VK_SAMPLE_COUNT_64_BIT;

				// 32 bit
				if (count & VK_SAMPLE_COUNT_32_BIT)
					return VK_SAMPLE_COUNT_32_BIT;

				// 16 bit
				if (count & VK_SAMPLE_COUNT_16_BIT)
					return VK_SAMPLE_COUNT_16_BIT;

				// 8 bit
				if (count & VK_SAMPLE_COUNT_8_BIT)
					return VK_SAMPLE_COUNT_8_BIT;

				// 4 bit
				if (count & VK_SAMPLE_COUNT_4_BIT)
					return VK_SAMPLE_COUNT_4_BIT;

				// 2 bit
				if (count & VK_SAMPLE_COUNT_2_BIT)
					return VK_SAMPLE_COUNT_2_BIT;

				// 1 bit
				return VK_SAMPLE_COUNT_1_BIT;
			}


	}; // class multisampling

} // namespace ve

#endif // ___ve_vulkan_multisampling___
