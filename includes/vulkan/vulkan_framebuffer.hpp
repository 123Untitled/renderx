#ifndef ENGINE_VULKAN_FRAMEBUFFER_HPP
#define ENGINE_VULKAN_FRAMEBUFFER_HPP


// vulkan headers
#include <vulkan/vulkan.h>
#include "exceptions.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- F R A M E B U F F E R -----------------------------------------------

	class framebuffer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::framebuffer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			framebuffer(void) noexcept;

			/* deleted copy constructor */
			framebuffer(const self&) = delete;

			/* move constructor */
			framebuffer(self&&) noexcept;

			/* destructor */
			~framebuffer(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


		private:

			// -- private static methods --------------------------------------

			/* create */
			static auto create(::VkFramebufferCreateInfo&) -> ::VkFramebuffer;


			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* buffer */
			::VkFramebuffer _buffer;

			/* logical device */
			::VkDevice _device;

	}; // class framebuffer

} // namespace vulkan

#endif // ENGINE_VULKAN_FRAMEBUFFER_HPP
