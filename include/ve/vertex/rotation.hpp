/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_ROTATION_HEADER___
#define ___ENGINE_ROTATION_HEADER___

#include "ve/vk/format.hpp"


// -- V X  N A M E S P A C E --------------------------------------------------

namespace vx {


	// -- P O S I T I O N -----------------------------------------------------

	template <typename ___type = vk::f32>
	class rotation final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vx::rotation<___type>;


			// -- private members ---------------------------------------------

			/* x, y, z */
			___type _x, _y, _z;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr rotation(void) noexcept
			: _x{static_cast<value_type>(0)},
			  _y{static_cast<value_type>(0)},
			  _z{static_cast<value_type>(0)} {
			}

			/* member constructor */
			constexpr rotation(const value_type& ___x,
							   const value_type& ___y,
							   const value_type& ___z) noexcept
			: _x{___x},
			  _y{___y},
			  _z{___z} {
			}

			/* copy constructor */
			constexpr rotation(const ___self&) noexcept = default;

			/* move constructor */
			constexpr rotation(___self&&) noexcept = default;

			/* destructor */
			constexpr ~rotation(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public methods ----------------------------------------------

			/* rotate */
			template <typename ___matrix>
			constexpr auto rotate(const ___matrix& ___m) noexcept -> void {
				___m.translate(_x, _y, _z);
			}


			// -- public accessors --------------------------------------------

			/* x */
			constexpr auto x(void) const noexcept -> value_type {
				return _x;
			}

			/* y */
			constexpr auto y(void) const noexcept -> value_type {
				return _y;
			}

			/* z */
			constexpr auto z(void) const noexcept -> value_type {
				return _z;
			}


			// -- public modifiers --------------------------------------------

			/* x */
			constexpr auto x(const value_type& ___x) noexcept -> void {
				_x = ___x;
			}

			/* y */
			constexpr auto y(const value_type& ___y) noexcept -> void {
				_y = ___y;
			}

			/* z */
			constexpr auto z(const value_type& ___z) noexcept -> void {
				_z = ___z;
			}


			// -- public static methods ---------------------------------------

			/* format */
			static consteval auto format(void) noexcept -> vk::format {
				return vk::pixel_format<value_type, 3U>();
			}

	}; // class position

} // namespace vx

#endif // ___ENGINE_ROTATION_HEADER___
