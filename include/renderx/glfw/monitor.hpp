#ifndef ___RENDERX_GLFW_MONITOR___
#define ___RENDERX_GLFW_MONITOR___

#include "renderx/glfw/typedefs.hpp"
#include "renderx/glfw/glfw.hpp"

#include <iostream>


// -- G L F W -----------------------------------------------------------------

namespace glfw {


	// -- M O N I T O R -------------------------------------------------------

	class monitor final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = glfw::monitor;


			// -- private members ---------------------------------------------

			/* monitor handle */
			::glfw_monitor* _monitor;

			/* mode */
			const ::glfw_video_mode* _mode;

			/* name */
			const char* _name;


			// -- private static methods --------------------------------------

			/* callback */
			static void _callback(::glfw_monitor* const monitor, const int event) {

				switch (event) {

					case GLFW_CONNECTED:
						// monitor connected
						break;

					case GLFW_DISCONNECTED:
						// monitor disconnected
						break;

					default:
						// unknown event
						break;
				}
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			monitor(void)
			: _monitor{nullptr}, _mode{nullptr}, _name{nullptr} {

				_monitor = ::glfw_get_primary_monitor();

				if (_monitor == nullptr)
					throw "no primary monitor found";

				_mode = ::glfw_get_video_mode(_monitor);

				if (_mode == nullptr)
					throw "no video mode found";

				int w, h;

				::glfw_get_monitor_physical_size(_monitor, &w, &h);

				float xscale, yscale;

				::glfw_get_monitor_content_scale(_monitor, &xscale, &yscale);

				const char* name = ::glfw_get_monitor_name(_monitor);

				std::cout << "monitor: " << name << std::endl;
				std::cout << "physical size: " << w << "x" << h << std::endl;
				std::cout << "content scale: " << xscale << "x" << yscale << std::endl;
				std::cout << "video mode: " << _mode->width << "x" << _mode->height << std::endl;
				std::cout << "refresh rate: " << _mode->refreshRate << std::endl;
				std::cout << "red bits: " << _mode->redBits << std::endl;
				std::cout << "green bits: " << _mode->greenBits << std::endl;
				std::cout << "blue bits: " << _mode->blueBits << std::endl;



				::glfw_set_monitor_callback(___self::_callback);
			}



	}; // class monitor

} // namespace glfw

#endif // ___RENDERX_GLFW_MONITOR___
