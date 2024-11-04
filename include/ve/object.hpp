#ifndef ___ve_object___
#define ___ve_object___

#include "ve/mesh.hpp"
#include "ve/transform.hpp"
#include "ve/uniform_buffer.hpp"
#include "ve/vulkan/descriptor/set.hpp"
#include "ve/vulkan/descriptor/descriptor_set_layout_library.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- O B J E C T ---------------------------------------------------------

	class object final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::object;


			// -- private members ---------------------------------------------

			/* mesh */
			const ve::mesh* _mesh;

			/* transform */
			rx::transform<float, 3U> _transform;

			/* model */
			glm::mat4 _model;

			/* uniform buffer */
			ve::uniform_buffer _ubo;

			/* descriptor set */
			vk::descriptor::set _set;



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			object(void) noexcept
			: _mesh{nullptr}, _transform{}, _model{glm::mat4{1.0f}},
			  _ubo{_model},
			  _set{ve::descriptor_set_layout_library::get<"planet">()} {

				// write descriptor set
				_set.write(_ubo.descriptor_buffer_info(),
							VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
			}

			/* mesh constructor */
			object(const ve::mesh& ___mesh) noexcept
			: _mesh{&___mesh}, _transform{}, _model{glm::mat4{1.0f}},
			  _ubo{_model},
			  _set{ve::descriptor_set_layout_library::get<"planet">()} {

				// write descriptor set
				_set.write(_ubo.descriptor_buffer_info(),
							VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
			}


			// -- public methods ----------------------------------------------

			/* update */
			inline auto update(void) noexcept -> void {

				_model = _transform.model();
				_ubo.update(_model);
			}


			/* render */
			auto render(const vulkan::command_buffer& encoder,
						const ::vk_pipeline_layout& layout) const noexcept -> void {

				// bind descriptor sets
				_set.bind(encoder, layout, 1U); // set 1

				encoder.bind_vertex_buffer(_mesh->vertices());
				encoder.bind_index_buffer(_mesh->indices());
				encoder.draw_indexed(_mesh->indices().count());
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

			/* scale */
			inline auto scale(void) noexcept -> glm::vec3& {
				return _transform.scale();
			}

			/* uniform buffer */
			//inline auto uniform_buffer(void) noexcept -> ve::uniform_buffer& {
			//	return _uniform_buffer;
			//}

	}; // class object


} // namespace ve

#endif // ___ve_object___
