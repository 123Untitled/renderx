#ifndef ___void_engine_mouse_delta___
#define ___void_engine_mouse_delta___

#include <vector>
//#include "ve/glfw/events.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {

	namespace mouse {


		class observer {

			public:

				observer(void) noexcept = default;
				observer(const observer&) = delete;
				observer(observer&&) noexcept = default;
				virtual ~observer(void) noexcept = default;
				auto operator=(const observer&) -> observer& = delete;
				auto operator=(observer&&) noexcept -> observer& = default;

				virtual auto mouse_moved(const double&, const double&) noexcept -> void = 0;
		};


		class delta final {


			private:

				// -- private types -----------------------------------------------

				/* self type */
				using self = ve::mouse::delta;


				/* mouse position */
				double _lx, _ly;

				/* mouse delta */
				double _dx, _dy;

				std::vector<observer*> _observers;


				// -- private static methods --------------------------------------

				/* shared */
				static auto _shared(void) -> self& {
					static self instance;
					return instance;
				}


				// -- private lifecycle -------------------------------------------

				/* default constructor */
				delta(void) noexcept
				: _lx{0.0}, _ly{0.0}, _dx{0.0}, _dy{0.0} {
				}


			public:

				/* subscribe */
				static auto subscribe(observer* obs) noexcept -> void {
					self::_shared()._observers.push_back(obs);
				}

				/* unsubscribe */
				static auto unsubscribe(observer* obs) noexcept -> void {

					auto& _observers = self::_shared()._observers;

					for (auto it = _observers.begin(); it != _observers.end(); ++it) {
						if (*it == obs) {
							_observers.erase(it);
							break;
						}
					}
				}

				/* update */
				static auto update(void) noexcept -> void {

					/*
					self& ins = self::_shared();

					double cx, cy;

					// retrieve position
					::glfw_get_cursor_pos(&glfw::window::shared(),
							&cx, &cy);

					ins._dx = cx - ins._lx;
					ins._dy = cy - ins._ly;

					// update last known position
					ins._lx = cx;
					ins._ly = cy;
					*/
				}

				/* update */
				static auto update(const double cx, const double cy) noexcept -> void {

					return;
					self& ins = self::_shared();

					ins._dx = cx - ins._lx;
					ins._dy = cy - ins._ly;

					// update last known position
					ins._lx = cx;
					ins._ly = cy;

				}

				/* dx */
				static auto dx(void) noexcept -> double {
					return self::_shared()._dx;
				}

				/* dy */
				static auto dy(void) noexcept -> double {
					return self::_shared()._dy;
				}

		}; // class delta

	} // namespace mouse

} // namespace ve

#endif // ___void_engine_mouse_delta___
