#ifndef ___ve_camera___
#define ___ve_camera___

//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES

#include "ve/camera/projection.hpp"

#include "ve/uniform_buffer.hpp"
#include "ve/vulkan/descriptor/set.hpp"
#include "ve/vulkan/descriptor/descriptor_set_layout_library.hpp"

#include "ve/structures/vec.hpp"

#include <glm/glm.hpp>
#include "ve/transform.hpp"

#include "ve/time/delta.hpp"
#include "ve/mouse_delta.hpp"
#include "ve/glfw/events.hpp"
#include "ve/glfw/window.hpp"

#include "ve/structures/matrix.hpp"
#include "ve/uniform_buffer.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- C A M E R A ---------------------------------------------------------

	class camera final : public ve::mouse::observer {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::camera;


			// -- private members ---------------------------------------------


			/* projection */
			ve::projection _projection;

			/* sensitivity */
			float _sensitivity;

			/* velocity */
			float _velocity;


			struct uniform {

				/* projection */
				glm::mat4 _projection;

				/* view */
				glm::mat4 _view;

				/* position */
				glm::vec3 _position;


			} _uniform;

			/* rotation */
			glm::vec3 _rotation;

			/* direction */
			glm::vec3 _direction;

			/* uniform buffer */
			ve::uniform_buffer _ubo;

			/* descriptor set */
			vk::descriptor::set _set;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			camera(void)
			: _projection{}, _sensitivity{0.24f}, _velocity{1.0f},
			  _uniform{
				  ._projection{_projection.matrix()},
				  ._view{1.0f},
				  ._position{0.0f},
			  },
			  _rotation{0.0f},
			  _direction{0.0f},
			  _ubo{_uniform},
			  _set{ve::descriptor_set_layout_library::get<"camera">()} {


				// write descriptor set
				_set.write(_ubo.descriptor_buffer_info(),
							VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);

				// subscribe to mouse events
				ve::mouse::delta::subscribe(this);
			}

			/* deleted copy constructor */
			camera(const ___self&) noexcept = delete;

			/* move constructor */
			camera(___self&&) noexcept = default;

			/* destructor */
			~camera(void) noexcept {

				// unsubscribe from mouse events
				ve::mouse::delta::unsubscribe(this);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* update projection */
			auto update_projection(void) noexcept -> void {

				// recalculate projection
				_uniform._projection = _projection.matrix();
			}


			/* projection */
			auto projection(void) const noexcept -> const glm::mat4& {
				return _uniform._projection;
			}

			/* view */
			auto view(void) const noexcept -> const glm::mat4& {
				return _uniform._view;
			}

			/* position */
			auto position(void) noexcept -> glm::vec3& {
				return _uniform._position;
			}

			/* position */
			auto position(void) const noexcept -> const glm::vec3& {
				return _uniform._position;
			}

			/* uniform */
			auto uniform(void) const noexcept -> const uniform& {
				return _uniform;
			}

			/* descriptor buffer info */
			//auto descriptor_buffer_info(void) const noexcept -> vk::descriptor_buffer_info {
			//	return vk::descriptor_buffer_info{
			//		.buffer = _uniform_buffer.get(),
			//		.offset = 0U,
			//		.range = sizeof(uniform)
			//	};
			//}


			// -- public overrides --------------------------------------------

			/* mouse moved */
			auto mouse_moved(const double& x, const double& y) noexcept -> void override {
				update_rotation(x, y);
			}


			// -- public methods ----------------------------------------------

			/* update */
			auto update(void) noexcept -> void {
				//update_rotation();
				update_direction();
				update_position();
				update_view();
				//update_projection();
				//_uniform_buffer.update(_uniform);

				// update uniform buffer
				_ubo.update(_uniform);
			}

			/* render */
			auto render(const vk::command_buffer& encoder,
						const ::vk_pipeline_layout& layout) const noexcept -> void {

				// bind descriptor sets
				_set.bind(encoder, layout, 0U);
			}


			/* update direction */
			auto update_direction(void) noexcept -> void {
				_direction.x = std::sin(_rotation.y);
				_direction.y = std::cos(_rotation.y);
				//_uniform._direction.z() = std::sin(_uniform._rotation.x);
			}


			/* update position */
			auto update_position(void) noexcept -> void {

				// get arrow keys
				const auto& arrows = glfw::events::arrows();


				const bool front = arrows[0];
				const bool back  = arrows[1];
				const bool left  = arrows[2];
				const bool right = arrows[3];


				glm::vec2 movement {0.0f, 0.0f};

				if (front) {
					movement.x -= _direction.x;
					movement.y += _direction.y;
				}
				if (back) {
					movement.x += _direction.x;
					movement.y -= _direction.y;
				}
				if (left) {
					movement.x -= _direction.y;
					movement.y -= _direction.x;
				}
				if (right) {
					movement.x += _direction.y;
					movement.y += _direction.x;
				}

				if ((right || left) && (front || back)) {

					// 1 / sqrt(2), normalize the movement
					movement *= 0.70710678118f;
					//movement.x() *= 0.70710678118f;
					//movement.y() *= 0.70710678118f;
					//movement.z() *= 0.70710678118f;
				}


				if (front || back || left || right) {

					const auto velo = _velocity * ve::delta::time();

					_uniform._position.x += movement.x * velo;
					_uniform._position.z += movement.y * velo;
				}

			}


			/* update view */
			auto update_view(void) noexcept -> void {

				_uniform._view = glm::mat4(1.0f);

				// rotate
				_uniform._view = glm::rotate(_uniform._view, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				_uniform._view = glm::rotate(_uniform._view, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				_uniform._view = glm::rotate(_uniform._view, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));


				// translate
				_uniform._view[3] = glm::vec4{
					(_uniform._view[0] * -_uniform._position.x) +
					(_uniform._view[1] * -_uniform._position.y) +
					(_uniform._view[2] * -_uniform._position.z) +
					_uniform._view[3]
				};
			}

			// 2 * pi
			static constexpr auto pi2 = static_cast<float>(2.0 * 3.14159265358979323846264338327950288);

			/* update rotation */
			auto update_rotation(const double x, const double y) noexcept -> void {

				const float multiplier = _sensitivity * ve::delta::time();

				_rotation.x += (static_cast<float>(y) * multiplier);
				_rotation.y -= (static_cast<float>(x) * multiplier);

				// get references
				auto& _x = _rotation.x;
				auto& _y = _rotation.y;

				// stay in radian range
				_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
				_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);
			}


			auto projection(void) noexcept -> ve::projection& {
				return _projection;
			}


	}; // class camera



} // namespace ve

#endif // ___ve_camera___
