#ifndef ___ve_diagnostics_runtime_error___
#define ___ve_diagnostics_runtime_error___


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- R U N T I M E  E R R O R --------------------------------------------

	class runtime_error final {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::runtime_error;


			// -- private members ---------------------------------------------

			/* what */
			const char* _what;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) = delete;

			/* where and what constructor */
			exception(const char* what) noexcept
			: _where{what != nullptr ? what : "unknown"}, _what{self::_strerror(what)} {
			}

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> const char* override;


	}; // class runtime_error

} // namespace ve

#endif // ___ve_diagnostics_runtime_error___
