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

#ifndef ENGINE_EXCEPTIONS_HEADER
#define ENGINE_EXCEPTIONS_HEADER

#include <iostream>

// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- E X C E P T I O N ----------------------------------------------------

	class exception final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::exception;

			// -- public lifecycle --------------------------------------------

			/* message constructor */
			exception(const char* message) noexcept
			: message{message} {
			}

			/* deleted copy constructor */
			exception(const self&) noexcept = default;

			/* deleted move constructor */
			exception(self&&) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* print */
			auto print(void) const noexcept -> void {
				std::cerr << "\x1b[31merror: \x1b[0m"
						  << message
						  << std::endl;
			}

		private:

			// -- private members ---------------------------------------------

			/* message */
			const char* message;

	}; // class exception


	/* fatal */
	inline auto fatal(const char* message) -> void {
		throw engine::exception{message};
	}

} // namespace engine

#endif // ENGINE_EXCEPTIONS_HPP
