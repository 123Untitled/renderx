#ifndef ___ve_diagnostics_runtime_error___
#define ___ve_diagnostics_runtime_error___

#include "ve/diagnostics/exception.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- R U N T I M E  E R R O R --------------------------------------------

	class runtime_error final : public ve::exception {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ve::runtime_error;


			// -- private members ---------------------------------------------

			/* what */
			const char* _what;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			runtime_error(void) = delete;

			/* where and what constructor */
			runtime_error(const char* what) noexcept
			: _what{what != nullptr ? what : "unknown"} {
			}

			/* copy constructor */
			runtime_error(const self&) noexcept = default;

			/* move constructor */
			runtime_error(self&&) noexcept = default;

			/* destructor */
			~runtime_error(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> const char* override {
				return _what;
			}


	}; // class runtime_error

} // namespace ve

#endif // ___ve_diagnostics_runtime_error___
