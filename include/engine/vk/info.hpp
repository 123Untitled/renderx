#ifndef ___ENGINE_VULKAN_INFO___
#define ___ENGINE_VULKAN_INFO___

#include "engine/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- I N F O  N A M E S P A C E ------------------------------------------

	namespace info {


		/* semaphore */
		inline consteval auto semaphore(void) noexcept -> vk::semaphore_info {

			return vk::semaphore_info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (reserved for future use)
				.flags = 0U
			};
		}

		/* fence */
		template <vk::fence_create_flags ___flags>
		inline consteval auto fence(void) noexcept -> vk::fence_info {

			return vk::fence_info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = ___flags
			};
		}

		/* image view */
		inline constexpr auto image_view(const vk::format ___fmt) noexcept -> vk::image_view_info {

			return vk::image_view_info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// image
				.image = nullptr,
				// view type
				.viewType = VK_IMAGE_VIEW_TYPE_2D,
				// format
				.format = ___fmt,
				// components
				.components = {
					.r = VK_COMPONENT_SWIZZLE_IDENTITY,
					.g = VK_COMPONENT_SWIZZLE_IDENTITY,
					.b = VK_COMPONENT_SWIZZLE_IDENTITY,
					.a = VK_COMPONENT_SWIZZLE_IDENTITY
				},
				// subresource range
				.subresourceRange = {
					.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
					.baseMipLevel   = 0U,
					.levelCount     = 1U,
					.baseArrayLayer = 0U,
					.layerCount     = 1U
				}
			};
		}

		/* framebuffer */
		inline constexpr auto framebuffer(const vk::render_pass& ___rpass,
										  const vk::extent2D& ___extent) noexcept -> vk::framebuffer_info {

			return vk::framebuffer_info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags (none)
				.flags = 0U,
				// render pass
				.renderPass = ___rpass,
				// attachment count
				.attachmentCount = 0U,
				// attachments
				.pAttachments = nullptr,
				// width
				.width = ___extent.width,
				// height
				.height = ___extent.height,
				// layers
				.layers = 1U
			};
		}


	} // namespace info

} // namespace vk

#endif // ___ENGINE_VULKAN_INFO___
