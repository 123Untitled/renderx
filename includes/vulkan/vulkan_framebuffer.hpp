#ifndef ENGINE_VULKAN_FRAMEBUFFER_HPP
#define ENGINE_VULKAN_FRAMEBUFFER_HPP


// vulkan headers
#include <vulkan/vulkan.h>
#include "exceptions.hpp"

#include "vulkan_logical_device.hpp"
#include "vulkan_render_pass.hpp"
#include "vulkan_swapchain.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- F R A M E B U F F E R -----------------------------------------------

	class framebuffer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::framebuffer;


			// -- public lifecycle --------------------------------------------

			/* logical device and render pass constructor */
			framebuffer(const vulkan::logical_device&,
						const vulkan::render_pass&,
						const vulkan::swapchain&);

			/* copy constructor */
			framebuffer(const self&) noexcept;

			/* move constructor */
			framebuffer(self&&) noexcept;

			/* destructor */
			~framebuffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


		private:

			// -- private members ---------------------------------------------

			/* buffer */
			vk::framebuffer _buffer;

	}; // class framebuffer

} // namespace vulkan

#endif // ENGINE_VULKAN_FRAMEBUFFER_HPP
