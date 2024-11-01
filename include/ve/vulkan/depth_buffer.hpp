#ifndef ___ve_vulkan_depth_buffer___
#define ___ve_vulkan_depth_buffer___


#include "ve/vulkan/image.hpp"
#include "ve/vulkan/image_view.hpp"
#include "ve/vulkan/multisampling.hpp"

#include "ve/vk/array.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/device.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- D E P T H  B U F F E R ----------------------------------------------

	class depth_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::depth_buffer;


			// -- private members ---------------------------------------------

			/* image */
			ve::image _image;

			/* view */
			ve::image_view _view;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			depth_buffer(void) noexcept = default;

			/* constructor */
			depth_buffer(const vk::extent2D& extent)
			: _image{extent.width, extent.height, ve::depth_buffer::format(),
				ve::multisampling::max(),
				VK_IMAGE_TILING_OPTIMAL,
				VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
			 _view{_image, ve::depth_buffer::format(), VK_IMAGE_ASPECT_DEPTH_BIT} {
			}

			/* deleted copy constructor */
			depth_buffer(const ___self&) = delete;

			/* move constructor */
			depth_buffer(___self&&) noexcept = default;

			/* destructor */
			~depth_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* view */
			auto view(void) const noexcept -> const vk::image_view& {
				return static_cast<const vk::image_view&>(_view);
			}


		private:

			// -- private static methods --------------------------------------

			/* find supported format */
			static auto _find_supported_format(void) -> vk::format {

				const vk::array<vk::format, 3U> candidates {
					VK_FORMAT_D32_SFLOAT,
					VK_FORMAT_D32_SFLOAT_S8_UINT,
					VK_FORMAT_D24_UNORM_S8_UINT
				};

				const vk::image_tiling tiling{VK_IMAGE_TILING_OPTIMAL};

				vk::format_feature_flags features{VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT};

				vk::physical_device pdevice = vulkan::device::physical();


				for (vk::u32 i = 0U; i < candidates.size(); ++i) {

					vk::format_properties props;

					::vk_get_physical_device_format_properties(pdevice, candidates[i], &props);

					if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
						return candidates[i];

					}

					else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
						return candidates[i];
					}
				}

				throw std::runtime_error("failed to find supported format!");
			}


			/* has stencil component */
			static auto has_stencil_component(const vk::format& format) -> bool {
				return format == VK_FORMAT_D32_SFLOAT_S8_UINT
					|| format == VK_FORMAT_D24_UNORM_S8_UINT;
			}


		public:

			// -- public static methods ---------------------------------------

			/* format */
			static auto format(void) -> vk::format {
				static const vk::format format = ___self::_find_supported_format();
				return format;
			}


	}; // class depth_buffer

} // namespace ve

#endif // ___ve_vulkan_depth_buffer___
