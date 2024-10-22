#ifndef ___DIAGNOSTICS_EXCEPTION___
#define ___DIAGNOSTICS_EXCEPTION___


namespace rx {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::exception;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) noexcept = default;

			/* copy constructor */
			exception(const ___self&) noexcept = default;

			/* move constructor */
			exception(___self&&) noexcept = default;

			/* destructor */
			virtual ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public interface --------------------------------------------

			/* what */
			virtual auto what(void) const noexcept -> const char* = 0;

	}; // class exception

} // namespace rx

#endif // ___DIAGNOSTICS_EXCEPTION___
