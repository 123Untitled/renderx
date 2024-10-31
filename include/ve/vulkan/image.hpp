#ifndef ___ve_vulkan_image___
#define ___ve_vulkan_image___

#include "ve/vk/unique.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/device.hpp"
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
			image(const vk::u32& width,
				  const vk::u32& height,
				  const vk::format& format,
				  const vk::sample_count_flag_bits& samples,
				  const vk::image_tiling& tiling,
				  const vk::image_usage_flags& usage,
				  const vk::memory_property_flags& properties)

			// create image
			: _image{___self::_create_image(width, height, format, samples, tiling, usage)},
			// allocate memory
			  _alloc{vulkan::allocator<vulkan::gpu_memory>::allocate_image(_image.get())} {
			}

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
			operator const vk::image&(void) const noexcept {
				return _image.get();
			}


		private:

			// -- private static methods --------------------------------------

			/* create image */
			static auto _create_image(const vk::u32& width,
									  const vk::u32& height,
									  const vk::format& format,
									  const vk::sample_count_flag_bits& samples,
									  const vk::image_tiling& tiling,
									  const vk::image_usage_flags& usage) -> vk::unique<vk::image> {

				const vk::image_info info {
					// structure type
					.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
					// next structure
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// image type
					.imageType = VK_IMAGE_TYPE_2D,
					// format
					.format = format,
					// extent 3D
					.extent {
						.width = width,
						.height = height,
						.depth = 1
					},
					// mip levels
					.mipLevels = 1,
					// array layers
					.arrayLayers = 1,
					// samples
					.samples = samples,
					// tiling
					.tiling = tiling,
					// usage
					.usage = usage,
					// sharing mode
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
					// queue family index count
					.queueFamilyIndexCount = 0U,
					// queue family indices
					.pQueueFamilyIndices = nullptr,
					// initial layout
					.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
				};


				return vk::make_unique<vk::image>(info);
			}

	}; // class image

} // namespace ve

#endif // ___ve_vulkan_image___
