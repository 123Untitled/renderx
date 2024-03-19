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
			image_view(const vulkan::logical_device&,
					   const vk::image&,
					   const vk::format&);

			/* copy constructor */
			image_view(const self&) noexcept;

			/* move constructor */
			image_view(self&&) noexcept;

			/* destructor */
			~image_view(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* vk::image_view conversion operator */
			operator const vk::image_view&() const noexcept;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;



		private:

			// -- private members ---------------------------------------------

			/* view */
			vk::image_view _view;

	}; // class image_view

} // namespace vulkan

#endif // ifndef ENGINE_VULKAN_IMAGE_VIEW_HPP
