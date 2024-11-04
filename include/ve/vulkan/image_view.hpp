#ifndef ___ve_vulkan_image_view___
#define ___ve_vulkan_image_view___

#include "ve/vk/unique.hpp"


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
			image_view(const vk::image&,
					   const vk::format&,
					   const vk::image_aspect_flags&);

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
			operator const vk::image_view&(void) const noexcept;


			// -- public accessors --------------------------------------------

			/* descriptor image info */
			auto descriptor_image_info(const vk::image_layout& layout = VK_IMAGE_LAYOUT_GENERAL
					) const noexcept -> ::vk_descriptor_image_info {
				return ::vk_descriptor_image_info{
					.sampler = nullptr,
					.imageView = _view.get(),
					.imageLayout = layout
				};
			}


		private:

			// -- private static methods --------------------------------------

			/* create image view */
			static auto _create_image_view(const vk::image&,
										   const vk::format&,
										   const vk::image_aspect_flags&
										) -> vk::unique<vk::image_view>;

	}; // class image_view

} // namespace ve

#endif // ___ve_vulkan_image_view___
