#ifndef ENGINE_VULKAN_RENDERPASS_HPP
#define ENGINE_VULKAN_RENDERPASS_HPP



// vulkan headers
#include <vulkan/vulkan.h>

#include "exceptions.hpp"
#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::render_pass;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			render_pass(void) noexcept = delete;

			/* logical device constructor */
			render_pass(const vulkan::logical_device&);


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* VkRenderPass conversion operator */
			operator ::VkRenderPass(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* renderpass */
			vk::render_pass _render_pass;


	}; // class renderpass

} // namespace vulkan

#endif // ENGINE_VULKAN_RENDERPASS_HPP
