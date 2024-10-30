#ifndef ___ve_camera_projection___
#define ___ve_camera_projection___

#include <glm/glm.hpp>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- P R O J E C T I O N -------------------------------------------------

	class projection final {


		private:

			// -- private members ---------------------------------------------

			/* fov */
			float _fov;

			/* ratio */
			float _ratio;

			/* near */
			float _near;

			/* far */
			float _far;


			// -- private constants -------------------------------------------

			/* cinemascope ratio */
			static constexpr float _cinemascope = 2.39f;

			/* 16:9 ratio */
			static constexpr float _16_9 = 16.0f / 9.0f;

			/* 4:3 ratio */
			static constexpr float _4_3 = 4.0f / 3.0f;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			projection(void) noexcept;

			/* copy constructor */
			projection(const projection&) noexcept = default;

			/* move constructor */
			projection(projection&&) noexcept = default;

			/* destructor */
			~projection(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const projection&) noexcept -> projection& = default;

			/* move assignment operator */
			auto operator=(projection&&) noexcept -> projection& = default;


			// -- public accessors --------------------------------------------

			/* matrix */
			auto matrix(void) const noexcept -> glm::mat4;

			/* fov */
			auto    fov(void) const noexcept -> const float&;

			/* ratio */
			auto  ratio(void) const noexcept -> const float&;

			/* near */
			auto   near(void) const noexcept -> const float&;

			/* far */
			auto    far(void) const noexcept -> const float&;


			// -- public modifiers --------------------------------------------

			/* fov */
			auto    fov(const float&) noexcept -> void;

			/* ratio */
			auto  ratio(const float&) noexcept -> void;

			/* near */
			auto   near(const float&) noexcept -> void;

			/* far */
			auto    far(const float&) noexcept -> void;

	}; // class projection

} // namespace ve

#endif // ___ve_camera_projection___
