#ifndef ENGINE_VULKAN_RENDERPASS_HPP
#define ENGINE_VULKAN_RENDERPASS_HPP

// vulkan headers
#include <vulkan/vulkan.h>

#include "vk_typedefs.hpp"
#include "vulkan_resource.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::render_pass;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			render_pass(void) noexcept;

			/* logical device constructor */
			render_pass(const vk::shared<vk::device>&);

			/* copy constructor */
			render_pass(const self&) noexcept;

			/* move constructor */
			render_pass(self&&) noexcept;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* vk::render_pass conversion operator */
			operator const vk::render_pass&(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* render pass */
			vk::managed<vk::render_pass,
						vk::shared<vk::device>> _render_pass;


	}; // class renderpass

} // namespace vulkan

#endif // ENGINE_VULKAN_RENDERPASS_HPP
