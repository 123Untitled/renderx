#ifndef ___RENDERX_OBJECT___
#define ___RENDERX_OBJECT___

#include "ve/mesh.hpp"
#include "ve/transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- O B J E C T ---------------------------------------------------------

	class object final : public rx::transform<float, 3U> {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::object;


			// -- private members ---------------------------------------------

			/* mesh */
			const ve::mesh* _mesh;

			/* model */
			glm::mat4 _model;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			object(void) noexcept
			: rx::transform<float, 3U>{}, _mesh{nullptr}, _model{glm::mat4{1.0f}} {
			}

			/* mesh constructor */
			object(const ve::mesh& ___mesh) noexcept
			: rx::transform<float, 3U>{}, _mesh{&___mesh}, _model{glm::mat4{1.0f}} {
			}


			// -- public methods ----------------------------------------------

			/* update */
			inline auto update(void) noexcept -> void {



				_model = model();
			}

			/* mesh */
			inline auto mesh(void) const noexcept -> const ve::mesh& {
				return *_mesh;
			}


	}; // class object


} // namespace rx

#endif // ___RENDERX_OBJECT___
