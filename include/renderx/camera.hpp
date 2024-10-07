#ifndef ___RENDERX_CAMERA___
#define ___RENDERX_CAMERA___

#include <glm/glm.hpp>
#include "renderx/transform.hpp"
#include "renderx/sdl/window.hpp"
#include "renderx/sdl/events.hpp"

#include "renderx/time/delta.hpp"


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- C A M E R A ---------------------------------------------------------

	class camera final : public rx::sdl::observer {


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

			/* transform */
			rx::transform<float, 3U> _transform;

			/* direction */
			glm::vec2 _direction;

			/* view */
			glm::mat4 _view;

			/* projection */
			glm::mat4 _projection;


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
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			camera(void) noexcept
			: _fov{90.0f}, _ratio{1.0f}, _near{0.1f}, _far{1000.0f}, _velocity{10.2f},
			  _projection{___self::_update_projection()} {
			}

			/* copy constructor */
			camera(const ___self&) noexcept = default;

			/* move constructor */
			camera(___self&&) noexcept = default;

			/* destructor */
			~camera(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* update projection */
			auto update_projection(void) noexcept -> void {

				// recalculate projection
				_projection = ___self::_update_projection();
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
				return _projection;
			}

			/* view */
			auto view(void) const noexcept -> const glm::mat4& {
				return _view;
			}


			// -- public methods ----------------------------------------------

			/* update */
			auto update(void) noexcept -> void {
				update_rotation();
				update_direction();
				update_position();
				update_view();
				//update_projection();
			}



			/* update rotation */
			auto update_rotation(void) noexcept -> void {

				float sens = 1.24f;

				float x, y;
				::sdl_get_relative_mouse_state(&x, &y);

				auto& _x = _transform.rotation().x;
				auto& _y = _transform.rotation().y;

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
				_direction.x = std::sin(_transform.rotation().y);
				_direction.y = std::cos(_transform.rotation().y);
			}


			/* update position */
			auto update_position(void) noexcept -> void {

				const bool front = rx::sdl::events::is_up();
				const bool back  = rx::sdl::events::is_down();
				const bool left  = rx::sdl::events::is_left();
				const bool right = rx::sdl::events::is_right();

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
					movement.x *= 0.70710678118f;
					movement.y *= 0.70710678118f;
				}


				if (front || back || left || right) {

					const auto velo = _velocity * rx::delta::time<float>();

					_transform.position().x += movement.x * velo;
					_transform.position().z += movement.y * velo;
				}
			}


			/* update view */
			auto update_view(void) noexcept -> void {

				_view = glm::mat4(1.0f);

				// rotate
				_view = glm::rotate(_view, _transform.rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
				_view = glm::rotate(_view, _transform.rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
				_view = glm::rotate(_view, _transform.rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));


				// translate
				_view = glm::translate(_view, /* maybe */ -_transform.position());
			}


			auto mouse_motion(const ::sdl_mouse_motion_event& event) noexcept -> void override {

				std::cout << "mouse motion: " << event.xrel << ", " << event.yrel << std::endl;
				float sens = 0.24f;

				_transform.rotation().x += (event.yrel * sens) * rx::delta::time<float>();
				_transform.rotation().y -= (event.xrel * sens) * rx::delta::time<float>();

				constexpr float pi2 = (float)(2.0 * 3.14159265358979323846264338327950288);

				auto& _x = _transform.rotation().x;
				auto& _y = _transform.rotation().y;

				// stay in radian range
				_x = ((_x > pi2) ? (_x - pi2) : (_x < 0.0f) ? (_x + pi2) : _x);
				_y = ((_y > pi2) ? (_y - pi2) : (_y < 0.0f) ? (_y + pi2) : _y);

				// update direction
				update_direction();
				update_view();

			}

			auto key_down(const ::sdl_keyboard_event& event) noexcept -> void override {



				glm::vec2 movement {0.0f, 0.0f};

				if (event.key == SDLK_E) {
					movement.x -= _direction.x;
					movement.y += _direction.y;
				}
				if (event.key == SDLK_D) {
					movement.x += _direction.x;
					movement.y -= _direction.y;
				}
				if (event.key == SDLK_S) {
					movement.x -= _direction.y;
					movement.y -= _direction.x;
				}
				if (event.key == SDLK_F) {
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



	}; // class camera

} // namespace rx

#endif // ___RENDERX_CAMERA___
