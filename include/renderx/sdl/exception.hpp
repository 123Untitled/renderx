#ifndef ___RENDERX_SDL_EXCEPTION_HPP___
#define ___RENDERX_SDL_EXCEPTION_HPP___


// -- S D L -------------------------------------------------------------------

namespace rx::sdl {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception final {


		private:

			const char* _message;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) = delete;

			/* message constructor */
			exception(const char* message)
			: _message{message} {
			}

			auto what(void) const noexcept -> const char* {
				return _message;
			}

	}; // class exception

} // namespace rx::sdl

#endif // ___RENDERX_SDL_EXCEPTION_HPP___
