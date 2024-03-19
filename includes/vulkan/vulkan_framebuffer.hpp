/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_FRAMEBUFFER_HEADER
#define ENGINE_VULKAN_FRAMEBUFFER_HEADER


// vulkan headers
#include <vulkan/vulkan.h>
#include "exceptions.hpp"

#include "vulkan/vk_shared.hpp"

#include "vulkan_device.hpp"
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

			/* default constructor */
			framebuffer(void) noexcept = default;

			/* logical device and render pass constructor */
			framebuffer(const vk::shared<vk::device>&,
						const vulkan::render_pass&,
						const vulkan::swapchain&);

			/* copy constructor */
			framebuffer(const self&) noexcept = default;

			/* move constructor */
			framebuffer(self&&) noexcept = default;

			/* destructor */
			~framebuffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


		private:

			// -- private members ---------------------------------------------

			/* buffer */
			vk::shared<vk::framebuffer> _buffer;

	}; // class framebuffer

} // namespace vulkan

#endif // ENGINE_VULKAN_FRAMEBUFFER_HPP
