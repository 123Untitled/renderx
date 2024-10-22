#ifndef ___RENDERX_TRANSFORM_HPP___
#define ___RENDERX_TRANSFORM_HPP___

#include "ve/types.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- T R A N S F O R M ---------------------------------------------------

	template <typename ___type, rx::u32 ___dims>
	class transform {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::transform<___type, ___dims>;

			/* glm type */
			using ___glm = glm::vec<___dims, ___type>;


			// -- private members ---------------------------------------------

			/* position */
			___glm _position;

			/* rotation */
			___glm _rotation;

			/* scale */
			___glm _scale;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			transform(void) noexcept
			: _position{static_cast<___type>(0)},
			  _rotation{static_cast<___type>(0)},
				 _scale{static_cast<___type>(1)} {
			}

			/* copy constructor */
			transform(const ___self&) noexcept = default;

			/* move constructor */
			transform(___self&&) noexcept = default;

			/* destructor */
			~transform(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* position */
			auto position(void) noexcept -> ___glm& {
				return _position;
			}

			/* const position */
			auto position(void) const noexcept -> const ___glm& {
				return _position;
			}

			/* rotation */
			auto rotation(void) noexcept -> ___glm& {
				return _rotation;
			}

			/* const rotation */
			auto rotation(void) const noexcept -> const ___glm& {
				return _rotation;
			}

			/* scale */
			auto scale(void) noexcept -> ___glm& {
				return _scale;
			}

			/* const scale */
			auto scale(void) const noexcept -> const ___glm& {
				return _scale;
			}


			/* model */
			auto model(void) const noexcept -> glm::mat4 {

				// translate
				auto model = glm::translate(glm::mat4(1.0f), _position);

				// rotate
				model = glm::rotate(model, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

				// scale
				model = glm::scale(model, _scale);

				// done
				return model;
			}

	}; // class transform

} // namespace rx

#endif // ___RENDERX_TRANSFORM___
