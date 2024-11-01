#ifndef ___ve_vulkan_image___
#define ___ve_vulkan_image___

#include "ve/vk/unique.hpp"
#include "ve/vulkan/allocator.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- I M A G E -----------------------------------------------------------

	class image final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::image;


			// -- private members ---------------------------------------------

			/* image */
			vk::unique<vk::image> _image;

			/* allocation */
			vulkan::allocation _alloc;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			image(void) noexcept = default;

			/* parameter constructor */
			image(const vk::u32&,
				  const vk::u32&,
				  const vk::format&,
				  const vk::sample_count_flag_bits&,
				  const vk::image_tiling&,
				  const vk::image_usage_flags&,
				  const vk::image_layout&,
				  const vk::memory_property_flags&);

			/* deleted copy constructor */
			image(const ___self&) = delete;

			/* move constructor */
			image(___self&&) noexcept = default;

			/* destructor */
			~image(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* const vk::image& conversion operator */
			operator const vk::image&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create image */
			static auto _create_image(const vk::u32&, const vk::u32&,
									  const vk::format&,
									  const vk::sample_count_flag_bits&,
									  const vk::image_tiling&,
									  const vk::image_usage_flags&,
									  const vk::image_layout& = VK_IMAGE_LAYOUT_UNDEFINED
									  ) -> vk::unique<vk::image>;

	}; // class image

} // namespace ve

#endif // ___ve_vulkan_image___
