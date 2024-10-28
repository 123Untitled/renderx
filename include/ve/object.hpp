#ifndef ___RENDERX_OBJECT___
#define ___RENDERX_OBJECT___

#include "ve/mesh.hpp"
#include "ve/transform.hpp"
#include "ve/uniform_buffer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- O B J E C T ---------------------------------------------------------

	class object final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::object;


			// -- private members ---------------------------------------------

			/* mesh */
			const ve::mesh* _mesh;

			/* transform */
			rx::transform<float, 3U> _transform;

			/* model */
			glm::mat4 _model;

			/* uniform buffer */
			ve::uniform_buffer _uniform_buffer;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			object(void) noexcept
			: _mesh{nullptr}, _transform{}, _model{glm::mat4{1.0f}}, _uniform_buffer{_model} {
			}

			/* mesh constructor */
			object(const ve::mesh& ___mesh) noexcept
			: _mesh{&___mesh}, _transform{}, _model{glm::mat4{1.0f}}, _uniform_buffer{_model} {
			}


			// -- public methods ----------------------------------------------

			/* update */
			inline auto update(void) noexcept -> void {

				_model = _transform.model();
				_uniform_buffer.update(_model);
			}

			/* mesh */
			inline auto mesh(void) const noexcept -> const ve::mesh& {
				return *_mesh;
			}

			/* model */
			inline auto model(void) const noexcept -> const glm::mat4& {
				return _model;
			}


			// -- public accessors --------------------------------------------

			/* position */
			inline auto position(void) noexcept -> glm::vec3& {
				return _transform.position();
			}

			/* rotation */
			inline auto rotation(void) noexcept -> glm::vec3& {
				return _transform.rotation();
			}

			/* uniform buffer */
			inline auto uniform_buffer(void) noexcept -> ve::uniform_buffer& {
				return _uniform_buffer;
			}

	}; // class object


} // namespace rx

#endif // ___RENDERX_OBJECT___
