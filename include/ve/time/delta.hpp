#ifndef ___RENDERX_TIME_DELTA___
#define ___RENDERX_TIME_DELTA___

#include "ve/time/now.hpp"


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- D E L T A -----------------------------------------------------------

	class delta final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::delta;


			// -- private members ---------------------------------------------

			/* delta */
			double _delta;

			/* previous */
			rx::umax _previous;



			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self ___ins;
				return ___ins;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			delta(void) noexcept
			: _delta{0.0},
			  _previous{rx::now()} {
			}

			/* deleted copy constructor */
			delta(___self const&) = delete;

			/* deleted move constructor */
			delta(___self&&) noexcept = delete;

			/* destructor */
			~delta(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* copy assignment */
			auto operator=(___self const&) -> ___self& = delete;

			/* move assignment */
			auto operator=(___self&&) noexcept -> ___self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* update */
			static auto update(void) noexcept -> void {


				auto& ins = ___self::_shared();

				//std::cout << ins._delta << std::endl;

				// get current time in nanoseconds
				auto current = rx::now();

				// update delta
				ins._delta = static_cast<double>(current - ins._previous);

				// delta time is generally in seconds or milliseconds ?
				// answer: seconds

				ins._delta /= 1'000'000'000.0;

				// update previous
				ins._previous = current;
			}

			/* time */
			template <typename ___type = double>
			static auto time(void) noexcept -> ___type {
				return static_cast<___type>(___self::_shared()._delta);
			}

	}; // class delta

} // namespace rx

#endif // ___RENDERX_TIME_DELTA___
