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
#include "engine/vk/typedefs.hpp"
#include "engine/vulkan/physical_device.hpp"
#include "engine/vulkan/surface.hpp"
#include "engine/vk/shared.hpp"



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
			auto family(void) const noexcept -> const vk::u32&;

			/* shared */
			auto shared(void) const noexcept -> const vk::shared<vk::device>&;

			/* handle */
			auto handle(void) const noexcept -> const vk::device&;



			// -- public methods ----------------------------------------------

			/* wait idle */
			auto wait_idle(void) const -> void;


		private:

			// -- private static methods --------------------------------------

			/* pick physical device */
			static auto pick_physical_device(const vulkan::surface&) -> vulkan::physical_device;


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
