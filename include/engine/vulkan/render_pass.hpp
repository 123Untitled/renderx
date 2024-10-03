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

#ifndef ENGINE_VULKAN_RENDERPASS_HEADER
#define ENGINE_VULKAN_RENDERPASS_HEADER

// vulkan headers
#include <vulkan/vulkan.h>

#include "engine/vk/typedefs.hpp"
#include "engine/vk/shared.hpp"


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
			render_pass(void) noexcept = default;

			/* logical device constructor */
			render_pass(const vk::shared<vk::device>&);

			/* copy constructor */
			render_pass(const self&) noexcept = default;

			/* move constructor */
			render_pass(self&&) noexcept = default;

			/* destructor */
			~render_pass(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::render_pass conversion operator */
			operator const vk::render_pass&(void) const noexcept;


			// -- public accessors --------------------------------------------

			/* shared */
			auto shared(void) const noexcept -> const vk::shared<vk::render_pass>&;

			/* handle */
			auto handle(void) const noexcept -> const vk::render_pass&;


		private:

			// -- private members ---------------------------------------------

			/* render pass */
			vk::shared<vk::render_pass> _render_pass;

	}; // class renderpass

} // namespace vulkan

#endif // ENGINE_VULKAN_RENDERPASS_HEADER
