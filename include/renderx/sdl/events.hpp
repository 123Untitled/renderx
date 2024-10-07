#ifndef ___RENDERX_SDL_EVENTS_HPP___
#define ___RENDERX_SDL_EVENTS_HPP___

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include "renderx/sdl/typedefs.hpp"
#include "renderx/hint.hpp"
#include "renderx/sdl/window.hpp"

#include "renderx/running.hpp"

#include <iostream>

// -- S D L -------------------------------------------------------------------

namespace rx::sdl {


	// -- E V E N T S ---------------------------------------------------------

	class events final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::sdl::events;


			// -- private members ---------------------------------------------

			/* events */
			::sdl_event _events;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self ___ins;
				return ___ins;
			}


			static auto _callback(void* userdata, ::sdl_event* event) -> bool {

				std::cout << "callback" << std::endl;

				return true;
			}

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			events(void)
			: _events{} {

				// setup relative mouse mode
				if (::sdl_set_window_relative_mouse_mode(&rx::sdl::window::shared(), true) != true)
					throw "failed to set relative mouse mode";


				// disable events
				//::sdl_set_event_enabled(SDL_EVENT_FIRST | SDL_EVENT_LAST, false);

			}

			/* deleted copy constructor */
			events(const ___self&) = delete;

			/* deleted move constructor */
			events(___self&&) = delete;

			/* destructor */
			~events(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private methods ---------------------------------------------

			/* handle key down */
			auto _handle_key_down(const ::sdl_keyboard_event& key_ev) -> void {

				const ::sdl_keycode keycode = key_ev.key;

				switch (keycode) {

					rx::hint::info("key down");

					case SDLK_ESCAPE:
						rx::hint::info("escape");
						ws::running::stop();
						break;

					case SDLK_LEFT:
						rx::hint::info("left");
						break;

					case SDLK_RIGHT:
						rx::hint::info("right");
						break;

					case SDLK_UP:
						rx::hint::info("up");
						break;

					case SDLK_DOWN:
						rx::hint::info("down");
						break;

					default:
						return;
				}

			}

			// mouse angle
			float _x = 0.0f;
			float _y = 0.0f;


			/* handle mouse motion */
			auto _handle_mouse_motion(const ::sdl_mouse_motion_event& motion_ev) -> void {

				float sens = 0.005f;

				_x += (motion_ev.xrel * sens);
				_y += (motion_ev.yrel * sens);


				constexpr double pi2 = 2.0 * 3.14159265358979323846264338327950288;

				// stay in radian range
				_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
				_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);

				std::cout << _x << " " << _y << std::endl;
				//std::cout << motion_ev.x << " " << motion_ev.y << std::endl;
			}

			/* handle window resized */
			auto _handle_window_resized(const ::sdl_window_event& window_ev) -> void {

				// get window size
				std::cout << "window x: " << window_ev.data1 << std::endl;
				std::cout << "window y: " << window_ev.data2 << std::endl;
			}

			/* handle */
			auto _handle(const ::sdl_event& ev) -> void {

				switch (ev.type) {

					case SDL_EVENT_WINDOW_RESIZED:
						___self::_handle_window_resized(ev.window);
						break;

					case SDL_EVENT_QUIT:
						break;

					case SDL_EVENT_MOUSE_BUTTON_DOWN:
						break;

					case SDL_EVENT_KEY_UP:
						//rx::hint::info("key up");
						break;

					case SDL_EVENT_KEY_DOWN:
						//rx::hint::info("key down");
						___self::_handle_key_down(_events.key);
						break;

					case SDL_EVENT_MOUSE_MOTION:
						//rx::hint::info("mouse motion");
						___self::_handle_mouse_motion(_events.motion);
						break;

					default:
						return;
				}

			}


		public:

			// -- public static accessors -------------------------------------

			/* x */
			static auto x(void) noexcept -> float {
				return ___self::_shared()._x;
			}

			/* y */
			static auto y(void) noexcept -> float {
				return ___self::_shared()._y;
			}

			// -- public static methods ---------------------------------------

			/* poll */
			static auto poll(void) /*noexcept*/ -> bool {

				//static std::vector<::sdl_event> events{1024};
				//::sdl_event events[1024];
				//
				//	const int ret = ::sdl_peep_events(nullptr, 1024, SDL_PEEKEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
				//	std::cout << "peeped: " << ret << std::endl;
				//
				//	if (ret == -1)
				//		throw "failed to peep events";
				//
				//	if (ret == 0)
				//		return false;
				//
				//	//events.resize(ret);
				//
				//	const int add = ::sdl_peep_events(events, ret, SDL_GETEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
				//	std::cout << "getevent: " << add << std::endl;
				//
				//	if (add == -1)
				//		throw "failed to peep events";
				//
				//	//events.resize(ret);
				//
				//	for (int i = 0; i < add; i++) {
				//		___self::_shared()._handle(events[i]);
				//	}
				//
				//	return add > 0;
				//
				//rx::hint::warning("events in queue");


				// poll event
				const bool ev = ::sdl_poll_event(&___self::_shared()._events);
				// handle
				if (ev)
					___self::_shared()._handle(___self::_shared()._events);

				return ev;
			}

			/* quit */
			static auto is_quit(void) noexcept -> bool {

				// check if quit
				return ___self::_shared()._events.type == SDL_EVENT_QUIT;
			}

	}; // class events

} // namespace rx::sdl

#endif // ___RENDERX_SDL_EVENTS_HPP___



//
//	switch (_key) {
//		case SDLK_ESCAPE:
//			App::isRunning = false;
//			break;
//		case SDLK_LEFT:
//			if (_observer)
//				_observer->update(1);
//			break;
//		case SDLK_RIGHT:
//			_observer->update(2);
//			break;
//		case SDLK_UP:
//			_observer->update(3);
//			break;
//		case SDLK_DOWN:
//			_observer->update(4);
//			break;
//		default:
//			return;
//	}
//}
//
//void Event::getMouseMotion(void) {
//	_cursor.x += _motion.xrel;
//	_cursor.y += _motion.yrel;
//}
//
//void Event::getMouseButtonDown(void) {
//	switch (_button) {
//		case SDL_BUTTON_LEFT:
//			_observer->update(6);
//			break;
//		case SDL_BUTTON_RIGHT:
//			_observer->update(7);
//			break;
//		default:
//			return;
//	}
//
//}


	//catchEvent[POOL](&_event);



//Uint8&					Event::_button		= _event.button.button;
//Observer*				Event::_observer = nullptr;
//SDL_Event				Event::_event;

//SDL_Keycode&			Event::_key		= _event.key.keysym.sym;

//SDL_MouseMotionEvent&	Event::_motion	= _event.motion;

//Uint32&					Event::_type	= _event.type;
//SDL_Point				Event::_cursor;
//int (*Event::catchEvent[2])(SDL_Event*)	= {&SDL_WaitEvent, &SDL_PollEvent};
