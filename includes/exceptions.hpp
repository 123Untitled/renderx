#ifndef ENGINE_EXCEPTIONS_HPP
#define ENGINE_EXCEPTIONS_HPP

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
			: message{message} {}

			/* deleted copy constructor */
			exception(const self&) = delete;

			/* deleted move constructor */
			exception(self&&) noexcept = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


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
