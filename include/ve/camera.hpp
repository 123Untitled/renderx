#ifndef ___RENDERX_CAMERA___
#define ___RENDERX_CAMERA___

#include <glm/glm.hpp>
#include "ve/transform.hpp"

#include "ve/time/delta.hpp"
#include "ve/glfw/events.hpp"
#include "ve/glfw/window.hpp"

#include "ve/structures/matrix.hpp"
#include "ve/uniform_buffer.hpp"


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- C A M E R A ---------------------------------------------------------

	class camera final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::camera;


			// -- private members ---------------------------------------------


			/* fov */
			float _fov;

			/* ratio */
			float _ratio;

			/* near */
			float _near;

			/* far */
			float _far;

			/* velocity */
			float _velocity;


			struct uniform {

				/* projection */
				glm::mat4 _projection;

				/* view */
				glm::mat4 _view;

				/* position */
				glm::vec3 _position;

				/* rotation */
				glm::vec3 _rotation;

				/* direction */
				glm::vec2 _direction;

			} _uniform;


			/* uniform buffer */
			ve::uniform_buffer _uniform_buffer;


			// -- private methods ---------------------------------------------

			/* update projection */
			auto _update_projection(void) noexcept -> glm::mat4 {

				const float ys = 1.0f / std::tan(((_fov / 180.0f) * static_cast<float>(M_PI)) * 0.5f);
				const float xs =   ys /  _ratio;
				const float zs = _far / (_near - _far);
				const float zt =   zs * _near;

				return glm::mat4 {
					{+xs,   0,   0,   0},
					{  0, +ys,   0,   0},
					{  0,   0, -zs,   1},
					{  0,   0,  zt,   0}
				};


				//ve::matrix<float, 4U, 4U> mat {
				//	+xs,    0,    0,    0,
				//	  0,  +ys,    0,    0,
				//	  0,    0,  -zs,    1,
				//	  0,    0,   zt,    0
				//};

			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			camera(void) noexcept
			: _fov{90.0f}, _ratio{800.0f/600.0f}, _near{0.001f}, _far{1000.0f}, _velocity{5.0f},
			  _uniform{
				  ._projection{___self::_update_projection()},
				  ._view{1.0f},
				  ._position{0.0f},
				  ._rotation{0.0f},
				  ._direction{0.0f}
			  },
			  _uniform_buffer{_uniform} {
			}

			/* deleted copy constructor */
			camera(const ___self&) = delete;

			/* move constructor */
			camera(___self&&) noexcept = default;

			/* destructor */
			~camera(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* update projection */
			auto update_projection(void) noexcept -> void {

				// recalculate projection
				_uniform._projection = ___self::_update_projection();
			}

			/* fov */
			auto fov(const float& value) noexcept -> void {
				_fov = value;
			}

			/* ratio */
			auto ratio(const float& value) noexcept -> void {
				_ratio = value;
			}

			/* near */
			auto near(const float& value) noexcept -> void {
				_near = value;
			}

			/* far */
			auto far(const float& value) noexcept -> void {
				_far = value;
			}


			// -- public accessors --------------------------------------------

			/* fov */
			auto fov(void) const noexcept -> const float& {
				return _fov;
			}

			/* ratio */
			auto ratio(void) const noexcept -> const float& {
				return _ratio;
			}

			/* near */
			auto near(void) const noexcept -> const float& {
				return _near;
			}

			/* far */
			auto far(void) const noexcept -> const float& {
				return _far;
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

			/* descriptor buffer info */
			auto descriptor_buffer_info(void) const noexcept -> vk::descriptor_buffer_info {
				return vk::descriptor_buffer_info{
					.buffer = _uniform_buffer.get(),
					.offset = 0U,
					.range = sizeof(uniform)
				};
			}


			// -- public methods ----------------------------------------------

			/* update */
			auto update(void) noexcept -> void {
				//update_rotation();
				update_direction();
				update_position();
				update_view();
				//update_projection();
				_uniform_buffer.update(_uniform);
			}



			/* update rotation */
			auto update_rotation(void) noexcept -> void {

				return;
				float sens = 1.24f;

				float x, y;
				//::sdl_get_relative_mouse_state(&x, &y);

				auto& _x = _uniform._rotation.x;
				auto& _y = _uniform._rotation.y;

				_x += (y * sens) * rx::delta::time<float>();
				_y -= (x * sens) * rx::delta::time<float>();

				constexpr float pi2 = (float)(2.0 * 3.14159265358979323846264338327950288);
				// stay in radian range
				_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
				_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);


				/*
				_transform.rotation().x = rx::sdl::events::y();
				_transform.rotation().y = rx::sdl::events::x();
				*/
			}

			/* update direction */
			auto update_direction(void) noexcept -> void {
				_uniform._direction.x = std::sin(_uniform._rotation.y);
				_uniform._direction.y = std::cos(_uniform._rotation.y);
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
					movement.x -= _uniform._direction.x;
					movement.y += _uniform._direction.y;
				}
				if (back) {
					movement.x += _uniform._direction.x;
					movement.y -= _uniform._direction.y;
				}
				if (left) {
					movement.x -= _uniform._direction.y;
					movement.y -= _uniform._direction.x;
				}
				if (right) {
					movement.x += _uniform._direction.y;
					movement.y += _uniform._direction.x;
				}

				if ((right || left) && (front || back)) {

					// 1 / sqrt(2), normalize the movement
					movement.x *= 0.70710678118f;
					movement.y *= 0.70710678118f;
				}


				//if (front || back || left || right) {

					const auto velo = _velocity * rx::delta::time<float>();

					_uniform._position.x += movement.x * velo;
					_uniform._position.z += movement.y * velo;
				//}

				//std::cout << "position: " << _transform.position().x << " " << _transform.position().y << " " << _transform.position().z << std::endl;
			}


			/* update view */
			auto update_view(void) noexcept -> void {

				_uniform._view = glm::mat4(1.0f);

				// rotate
				_uniform._view = glm::rotate(_uniform._view, _uniform._rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				_uniform._view = glm::rotate(_uniform._view, _uniform._rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				_uniform._view = glm::rotate(_uniform._view, _uniform._rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));


				// translate
				_uniform._view = glm::translate(_uniform._view,
						/* maybe */ -_uniform._position);
			}

			auto from_tap_event(double x, double y) -> void {

				float sens = 0.24f;

				_uniform._rotation.x += ((float)y * sens) * rx::delta::time<float>();
				_uniform._rotation.y -= ((float)x * sens) * rx::delta::time<float>();


				auto& _x = _uniform._rotation.x;
				auto& _y = _uniform._rotation.y;

				constexpr float pi2 = (float)(2.0 * 3.14159265358979323846264338327950288);

				// stay in radian range
				_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
				_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);

				// update direction
				//update_direction();
				//update_view();


			}


			//auto mouse_motion(const ::sdl_mouse_motion_event& event) noexcept -> void override {
			//
			//	std::cout << "mouse motion: " << event.xrel << ", " << event.yrel << std::endl;
			//	float sens = 0.24f;
			//
			//	_transform.rotation().x += (event.yrel * sens) * rx::delta::time<float>();
			//	_transform.rotation().y -= (event.xrel * sens) * rx::delta::time<float>();
			//
			//	constexpr float pi2 = (float)(2.0 * 3.14159265358979323846264338327950288);
			//
			//	auto& _x = _transform.rotation().x;
			//	auto& _y = _transform.rotation().y;
			//
			//	// stay in radian range
			//	_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
			//	_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);
			//
			//	// update direction
			//	update_direction();
			//	update_view();
			//
			//}

			/*
			auto from_key_event(const int&key) noexcept -> void {



				glm::vec2 movement {0.0f, 0.0f};

				// up
				if (key == 69) {
					movement.x -= _direction.x;
					movement.y += _direction.y;
				}
				// down
				if (key == 68) {
					movement.x += _direction.x;
					movement.y -= _direction.y;
				}
				// left
				if (key == 83) {
					movement.x -= _direction.y;
					movement.y -= _direction.x;
				}
				// right
				if (key == 70) {
					movement.x += _direction.y;
					movement.y += _direction.x;
				}

				//if ((right || left) && (front || back)) {
				//
				//	// 1 / sqrt(2), normalize the movement
				//	movement.x *= 0.70710678118f;
				//	movement.y *= 0.70710678118f;
				//}

				//if (front || back || left || right) {


				_transform.position().x
					+= movement.x * _velocity * rx::delta::time<float>();

				_transform.position().z
					+= movement.y * _velocity * rx::delta::time<float>();
				//}

				update_view();


			}
			*/



	}; // class camera

} // namespace rx

#endif // ___RENDERX_CAMERA___
