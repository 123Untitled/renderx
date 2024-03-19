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

#ifndef ENGINE_VULKAN_DEVICE_HEADER
#define ENGINE_VULKAN_DEVICE_HEADER

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"
#include "vulkan/vk_shared.hpp"



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- D E V I C E ---------------------------------------------------------

	class logical_device final {
		
		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::logical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			logical_device(void) noexcept = default;

			/* surface constructor */
			logical_device(const vulkan::surface&);

			/* copy constructor */
			logical_device(const self&) noexcept = default;

			/* move constructor */
			logical_device(self&&) noexcept = default;

			/* destructor */
			~logical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::device conversion operator */
			operator const vk::device&(void) const noexcept;

			/* vk::shared<vk::device> conversion operator */
			operator const vk::shared<vk::device>&(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* wait idle */
			auto wait_idle(void) const -> void;


		private:

			// -- private members ---------------------------------------------

			/* vulkan device */
			vk::shared<vk::device> _device;

			/* queue priority */
			float _priority;

	}; // class device

} // namespace vulkan

#endif // ENGINE_VULKAN_DEVICE_HEADER
