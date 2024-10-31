#ifndef ___ve_vulkan_image_view___
#define ___ve_vulkan_image_view___


#include "ve/vk/unique.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/device.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- I M A G E  V I E W --------------------------------------------------

	class image_view final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::image_view;


			// -- private members ---------------------------------------------

			/* image view */
			vk::unique<vk::image_view> _view;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			image_view(void) noexcept = default;

			/* parameter constructor */
			image_view(const vk::image& image,
					   const vk::format& format,
					   const vk::image_aspect_flags& aspect)
			: _view{ve::image_view::_create_image_view(image, format, aspect)} {

				/* VK_IMAGE_ASPECT_COLOR_BIT */
			}

			/* deleted copy constructor */
			image_view(const ___self&) = delete;

			/* move constructor */
			image_view(___self&&) noexcept = default;

			/* destructor */
			~image_view(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* const vk::image_view& conversion operator */
			operator const vk::image_view&(void) const noexcept {
				return _view.get();
			}


		private:

			// -- private static methods --------------------------------------

			/* create image view */
			static auto _create_image_view(const vk::image& image,
										   const vk::format& format,
										   const vk::image_aspect_flags& aspect
										) -> vk::unique<vk::image_view> {

				// create info
				const vk::image_view_info info{
					// structure type
					.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					// next structure
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// image
					.image = image,
					// view type
					.viewType = VK_IMAGE_VIEW_TYPE_2D,
					// format
					.format = format,
					// components
					.components = {
						.r = VK_COMPONENT_SWIZZLE_IDENTITY,
						.g = VK_COMPONENT_SWIZZLE_IDENTITY,
						.b = VK_COMPONENT_SWIZZLE_IDENTITY,
						.a = VK_COMPONENT_SWIZZLE_IDENTITY
					},
					// subresource range
					.subresourceRange = {
						.aspectMask = aspect,
						.baseMipLevel = 0U,
						.levelCount = 1U,
						.baseArrayLayer = 0U,
						.layerCount = 1U
					}
				};

				// create image view
				return vk::make_unique<vk::image_view>(info);
			}

	}; // class image_view

} // namespace ve

#endif // ___ve_vulkan_image_view___
