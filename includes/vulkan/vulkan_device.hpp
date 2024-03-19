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
#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan/vk_shared.hpp"



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- D E V I C E ---------------------------------------------------------

	class device final {
		
		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			device(void) noexcept = default;

			/* surface constructor */
			device(const vulkan::surface&);

			/* copy constructor */
			device(const self&) noexcept = default;

			/* move constructor */
			device(self&&) noexcept = default;

			/* destructor */
			~device(void) noexcept = default;


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


			// -- public accessors --------------------------------------------

			/* physical device */
			auto physical_device(void) const noexcept -> const vulkan::physical_device&;

			/* queue family */



			// -- public methods ----------------------------------------------

			/* wait idle */
			auto wait_idle(void) const -> void;


		private:

			// -- private members ---------------------------------------------

			/* logical device */
			vk::shared<vk::device> _ldevice;

			/* physical device */
			vulkan::physical_device _pdevice;

			/* queue family */
			vk::u32 _family;

			/* queue priority */
			float _priority;

	}; // class device

} // namespace vulkan

#endif // ENGINE_VULKAN_DEVICE_HEADER
