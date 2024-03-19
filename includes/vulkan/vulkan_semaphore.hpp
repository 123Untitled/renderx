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

#ifndef ENGINE_VULKAN_SEMAPHORE_HPP
#define ENGINE_VULKAN_SEMAPHORE_HPP


// vulkan headers
#include <vulkan/vulkan.h>

#include "vulkan_device.hpp"

#include "vk_shared.hpp"



// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S E M A P H O R E ----------------------------------------------------

	class semaphore final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::semaphore;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			semaphore(void) noexcept;

			/* logical device constructor */
			semaphore(const vk::shared<vk::device>&);

			/* copy constructor */
			semaphore(const self&) noexcept = default;

			/* move constructor */
			semaphore(self&&) noexcept = default;

			/* destructor */
			~semaphore(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::semaphore conversion operator */
			operator const vk::semaphore&(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* semaphore */
			vk::shared<vk::semaphore> _semaphore;

	}; // class semaphore

} // namespace vulkan

#endif // ENGINE_VULKAN_SEMAPHORE_HPP
