#ifndef ___RENDERX_SYSTEM_CLOSEABLE___
#define ___RENDERX_SYSTEM_CLOSEABLE___


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- C L O S E A B L E ---------------------------------------------------

	class closeable {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::closeable;


		protected:

			// -- protected members -------------------------------------------

			/* descriptor */
			int _desc;


		public:

			// -- public constants --------------------------------------------

			/* invalid descriptor */
			enum : int { INVALID_DESCRIPTOR = -1 };


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			closeable(void) noexcept;

			/* closeable constructor */
			closeable(const int) noexcept;

			/* deleted copy constructor */
			closeable(const ___self&) = delete;

			/* move constructor */
			closeable(___self&&) noexcept;

			/* destructor */
			~closeable(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;

			/* int assignment operator */
			auto operator=(const int) noexcept -> ___self&;


			// -- public conversion operators ---------------------------------

			/* int conversion operator */
			operator int(void) const noexcept;

			/* bool conversion operator */
			explicit operator bool(void) const noexcept;


			// -- public operators --------------------------------------------

			/* not operator */
			auto operator!(void) const noexcept -> bool;


			// -- public modifiers --------------------------------------------

			/* close */
			auto close(void) noexcept -> void;


		private:

			// -- private methods ---------------------------------------------

			/* close */
			auto _close(void) noexcept -> void;

	}; // class descriptor

} // namespace rx

#endif // ___RENDERX_SYSTEM_CLOSEABLE___
