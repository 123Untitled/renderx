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
			image_view(const vulkan::logical_device&, ::VkImage&, ::VkFormat&);

			/* deleted copy constructor */
			image_view(const self&) = delete;

			/* move constructor */
			image_view(self&&) noexcept;

			/* destructor */
			~image_view(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkImageView&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkImageView&;



		private:

			// -- private static methods --------------------------------------

			/* create image view */
			static auto create_image_view(const vulkan::logical_device&,
										  const ::VkImageViewCreateInfo&) -> ::VkImageView;

			/* create image view info */
			static auto create_image_view_info(::VkImage&,
											  ::VkFormat&) noexcept -> ::VkImageViewCreateInfo;

			
			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* view */
			::VkImageView _view;

			/* device */
			::VkDevice _device;

	}; // class image_view

} // namespace vulkan

#endif // ifndef ENGINE_VULKAN_IMAGE_VIEW_HPP
