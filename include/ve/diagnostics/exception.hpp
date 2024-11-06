#ifndef ___ve_diagnostics_exception___
#define ___ve_diagnostics_exception___


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::exception;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) noexcept = default;

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			virtual ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public interface --------------------------------------------

			/* what */
			virtual auto what(void) const noexcept -> const char* = 0;

	}; // class exception

} // namespace ve

#endif // ___ve_diagnostics_exception___
