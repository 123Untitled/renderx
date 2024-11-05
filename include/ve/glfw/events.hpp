#ifndef ___RENDERX_GLFW_EVENTS___
#define ___RENDERX_GLFW_EVENTS___

#include "ve/glfw/typedefs.hpp"
#include "ve/glfw/window.hpp"
#include "ve/running.hpp"

#include "ve/mouse_delta.hpp"

#include <iostream>


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {



	class control final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = glfw::control;


			// -- private members ---------------------------------------------

			/* floats */
			float _floats[4U];

			/* integers */
			int _integers[4U];

			/* booleans */
			bool _booleans[4U];


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self ___ins;
				return ___ins;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			control(void) noexcept
			: _floats{}, _integers{}, _booleans{} {
			}

			/* deleted copy constructor */
			control(const self&) = delete;

			/* deleted move constructor */
			control(self&&) = delete;

			/* destructor */
			~control(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* floats */
			static auto floats(void) -> float (&)[4] {
				return self::shared()._floats;
			}

			/* integers */
			static auto integers(void) -> int (&)[4] {
				return self::shared()._integers;
			}

			/* booleans */
			static auto booleans(void) -> bool (&)[4] {
				return self::shared()._booleans;
			}

	}; // class control

	static_assert(sizeof(control) < 128U, "control: size is too large.");



	// -- E V E N T S ---------------------------------------------------------

	class events final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = glfw::events;


			// -- private members ---------------------------------------------

			/* arrows */
			bool _arrows[4U];


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self ___ins;
				return ___ins;
			}

			/* mouse callback */
			static auto _mouse_callback(GLFWwindow* window, double x, double y) -> void {

				ve::mouse::delta::update(x, y);
				//std::cout << "x: " << x << "y: " << y << std::endl;
				//// get instance
				//auto instance = static_cast<glfw::window*>(::glfwGetWindowUserPointer(window));
				// set mouse position
				//instance->set_mouse_position(x, y);
				//std::cout << x << " " << y << std::endl;
			}

			/* handle key */
			template <bool action>
			auto _handle_key(const int key) noexcept -> void {

				switch (key) {

					// up
					case GLFW_KEY_E:
						_arrows[0U] = action;
						break;

					// down
					case GLFW_KEY_D:
						_arrows[1U] = action;
						break;

					// left
					case GLFW_KEY_S:
						_arrows[2U] = action;
						break;

					// right
					case GLFW_KEY_F:
						_arrows[3U] = action;
						break;

					// escape
					case GLFW_KEY_ESCAPE:
						ve::running::stop();
						break;

					// 1
					case GLFW_KEY_1:
						control::booleans()[0U] = action;
						break;
					// 2
					case GLFW_KEY_2:
						control::booleans()[1U] = action;
						break;
					// 3
					case GLFW_KEY_3:
						control::booleans()[2U] = action;
						break;
					// 4
					case GLFW_KEY_4:
						control::booleans()[3U] = action;
						break;

				}
			}

			/* key callback */
			static auto _key_callback(::glfw_window* const window,
										const int key,
										const int scancode,
										const int action,
										const int mods) -> void {

				switch (action) {

					case GLFW_PRESS:
						self::shared()._handle_key<true>(key);
						break;

					case GLFW_RELEASE:
						self::shared()._handle_key<false>(key);
						break;

					case GLFW_REPEAT:
						self::shared()._handle_key<true>(key);
						break;

					default:
						break;
				}
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			events(void) /* noexcept ? */
			: _arrows{false, false, false, false} {

				// get window
				auto& window = glfw::window::shared();

				// set key callback
				::glfw_set_key_callback(&window,
						self::_key_callback);

				// get mouse callback
				::glfw_set_cursor_pos_callback(&window,
						self::_mouse_callback);


				double cx, cy;

				// retrieve position
				::glfw_get_cursor_pos(&glfw::window::shared(),
						&cx, &cy);
				// init mouse delta
				ve::mouse::delta::update(cx, cy);



				// set mouse callback
				//::glfwSetCursorPosCallback(&window, &self::mouse_callback);

				glfwSetInputMode(&window,
						GLFW_CURSOR, GLFW_CURSOR_DISABLED);


				if (glfwRawMouseMotionSupported() == GLFW_TRUE) {
					glfwSetInputMode(&window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
					std::cout << "\x1b[33mRaw mouse motion enabled\x1b[0m" << std::endl;
				}
			}

			/* deleted copy constructor */
			events(const self&) = delete;

			/* deleted move constructor */
			events(self&&) = delete;

			/* destructor */
			~events(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* poll */
			static auto poll(void) noexcept -> void {
				::glfw_poll_events();
			}

			/* wait */
			static auto wait(void) noexcept -> void {
				::glfw_wait_events();
			}

			/* arrows */
			static auto arrows(void) -> const bool (&)[4] {
				return self::shared()._arrows;
			}

	}; // class events

} // namespace glfw

#endif // ___RENDERX_GLFW_EVENTS___
