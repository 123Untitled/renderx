#ifndef ENGINE_VULKAN_IMAGE_VIEW_HPP
#define ENGINE_VULKAN_IMAGE_VIEW_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- I M A G E  V I E W ---------------------------------------------------

	class image_view final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::image_view;



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			image_view(const vulkan::logical_device& device) noexcept
			: _view{nullptr}, _device{device.underlying()} {
				// create image view info
				auto info = self::create_image_view_info();
				// create image view
				auto result = self::create_image_view(device, info, _view);
			}

			/* deleted copy constructor */
			image_view(const self&) = delete;

			/* move constructor */
			image_view(self&& other) noexcept
			: _view{other._view} {
				other.init();
			}

			/* destructor */
			~image_view(void) noexcept {
				free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				free();
				  _view = other._view;
				_device = other._device;
				other.init();
				return *this;
			}


		private:

			// -- private methods ---------------------------------------------

			/* create image view */
			static auto create_image_view(const vulkan::logical_device& device,
										  const ::VkImageViewCreateInfo& info,
												::VkImageView& view) noexcept -> ::VkResult {
				return ::vkCreateImageView(device.underlying(), &info, nullptr, &view);
			}

			/* create image view info */
			static auto create_image_view_info(void) noexcept -> ::VkImageViewCreateInfo {
				return ::VkImageViewCreateInfo{
					.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					.pNext      = nullptr,
					.flags      = 0,
					.image      = nullptr, // not implemented
					.viewType   = VK_IMAGE_VIEW_TYPE_2D,
					.format     = VK_FORMAT_UNDEFINED, // not implemented
					.components = {
						.r = VK_COMPONENT_SWIZZLE_IDENTITY,
						.g = VK_COMPONENT_SWIZZLE_IDENTITY,
						.b = VK_COMPONENT_SWIZZLE_IDENTITY,
						.a = VK_COMPONENT_SWIZZLE_IDENTITY,
					},
					.subresourceRange   = {
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = 0,
						.layerCount     = 1,
					}
				};
			}

			
			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				if (_view == nullptr)
					return;
				::vkDestroyImageView(_device, _view, nullptr);
			}

			/* init */
			auto init(void) noexcept -> void {
				  _view = VK_NULL_HANDLE;
				_device = VK_NULL_HANDLE;
			}


			// -- private members ---------------------------------------------

			/* view */
			::VkImageView _view;

			/* device */
			::VkDevice _device;

	}; // class image_view

} // namespace vulkan

#endif // ifndef ENGINE_VULKAN_IMAGE_VIEW_HPP
