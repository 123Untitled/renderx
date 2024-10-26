#ifndef ___void_engine_mouse_delta___
#define ___void_engine_mouse_delta___

#include "ve/glfw/events.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	class mouse_delta final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::mouse_delta;


			/* mouse position */
			double _lx, _ly;

			/* mouse delta */
			double _dx, _dy;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self ___ins;
				return ___ins;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			mouse_delta(void) noexcept
			: _lx{0.0}, _ly{0.0},
			  _dx{0.0}, _dy{0.0} {
			}

		public:

			/* update */
			static auto update(void) noexcept -> void {

				___self& ins = ___self::_shared();

				double cx, cy;

				// retrieve position
				::glfw_get_cursor_pos(&glfw::window::shared(),
						&cx, &cy);

				ins._dx = cx - ins._lx;
				ins._dy = cy - ins._ly;

				// update last known position
				ins._lx = cx;
				ins._ly = cy;

				//if (ins._dx != 0.0 || ins._dy != 0.0)
				//	std::cout << "dx: " << ins._dx << " dy: " << ins._dy << std::endl;
			}

			/* dx */
			static auto dx(void) noexcept -> double {
				return ___self::_shared()._dx;
			}

			/* dy */
			static auto dy(void) noexcept -> double {
				return ___self::_shared()._dy;
			}

	}; // class mouse_delta

} // namespace ve

#endif // ___void_engine_mouse_delta___
