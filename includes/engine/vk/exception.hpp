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

#include "engine/vk/typedefs.hpp"


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
			constexpr exception(void) noexcept
			: _msg{"unknown exception"}, _size{17U}, _result{VkResult::VK_ERROR_UNKNOWN} {
			}

			/* message and result constructor */
			template <decltype(sizeof(0)) ___size>
			constexpr exception(const char (&___msg)[___size], const vk::result ___result = VkResult::VK_ERROR_UNKNOWN) noexcept
			: _msg{___msg}, _size{___size}, _result{___result} {
			}

			/* copy constructor */
			constexpr exception(const self&) noexcept = default;

			/* move constructor */
			constexpr exception(self&&) noexcept = default;

			/* destructor */
			constexpr ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> void;


		private:

			// -- private members ---------------------------------------------

			/* message */
			const char* _msg;

			/* size */
			vk::u32 _size;

			/* result */
			vk::result _result;

	}; // class exception

} // namespace vulkan

#endif // ENGINE_VULKAN_EXCEPTION_HEADER
