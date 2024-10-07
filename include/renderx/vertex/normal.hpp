#ifndef ___RENDERX_VERTEX_NORMAL___
#define ___RENDERX_VERTEX_NORMAL___

#include "engine/vk/format.hpp"
#include <glm/glm.hpp>


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- N O R M A L ---------------------------------------------------------

	class normal final : public glm::vec<3U, float> {


		private:

			//// -- private types -----------------------------------------------
			//
			///* self type */
			//using ___self = rx::normal;
			//
			//
			//// -- private members ---------------------------------------------
			//
			///* normal */
			//glm::vec3 _normal;


			// -- public static methods ---------------------------------------

			/* format */
			static consteval auto format(void) noexcept -> vk::format {
				return vk::pixel_format<float, 3U>();
			}

	}; // class normal

} // namespace rx

#endif // ___RENDERX_VERTEX_NORMAL___
