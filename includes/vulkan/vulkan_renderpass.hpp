#ifndef ENGINE_VULKAN_RENDERPASS_HPP
#define ENGINE_VULKAN_RENDERPASS_HPP



// vulkan headers
#include <vulkan/vulkan.h>

#include "exceptions.hpp"
#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- R E N D E R P A S S -------------------------------------------------

	class renderpass final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::renderpass;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderpass(void);


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* VkRenderPass conversion operator */
			operator ::VkRenderPass(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* renderpass */
			::VkRenderPass _renderpass;


	}; // class renderpass

} // namespace vulkan

#endif // ENGINE_VULKAN_RENDERPASS_HPP
