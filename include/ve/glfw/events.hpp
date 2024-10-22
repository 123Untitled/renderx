#ifndef ___RENDERX_GLFW_EVENTS___
#define ___RENDERX_GLFW_EVENTS___

#include "ve/glfw/typedefs.hpp"
#include "ve/glfw/window.hpp"
#include "ve/running.hpp"

#include <iostream>


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {


	// -- E V E N T S ---------------------------------------------------------

	class events final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = glfw::events;


			// -- private members ---------------------------------------------

			/* arrows */
			bool _arrows[4U];


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> ___self& {
				static ___self ___ins;
				return ___ins;
			}

			/* mouse callback */
			static auto mouse_callback(GLFWwindow* window, double x, double y) -> void {
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
						rx::running::stop();
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
						___self::shared()._handle_key<true>(key);
						break;

					case GLFW_RELEASE:
						___self::shared()._handle_key<false>(key);
						break;

					case GLFW_REPEAT:
						___self::shared()._handle_key<true>(key);
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
						___self::_key_callback);


				// set mouse callback
				//::glfwSetCursorPosCallback(&window, &___self::mouse_callback);

				//glfwSetInputMode(
				//		&glfw::window::shared(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				//glfwSetInputMode(&window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

				//if (glfwRawMouseMotionSupported() == GLFW_FALSE) {
				//	std::cout << "glfw: raw mouse motion is not supported." << std::endl;
				//	throw "glfw: raw mouse motion is not supported.";
				//}
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
			static auto arrows(void) noexcept -> const bool (&)[4] {
				return ___self::shared()._arrows;
			}

	}; // class events

} // namespace glfw

#endif // ___RENDERX_GLFW_EVENTS___
