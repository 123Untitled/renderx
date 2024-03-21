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

#ifndef ENGINE_VULKAN_EXCEPTION_HEADER
#define ENGINE_VULKAN_EXCEPTION_HEADER

#include "vk_typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::exception;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr exception(void) noexcept;

			/* message and result constructor */
			template <decltype(sizeof(0)) N>
			constexpr exception(const char (&msg)[N], const vk::result result = VkResult::VK_ERROR_UNKNOWN) noexcept
			: _message{msg}, _size{N}, _result{result} {
			}

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> void;


		private:

			// -- private members ---------------------------------------------

			/* message */
			const char* _message;

			/* size */
			vk::u32 _size;

			/* result */
			vk::result _result;

	}; // class exception

} // namespace vulkan

#endif // ENGINE_VULKAN_EXCEPTION_HEADER
