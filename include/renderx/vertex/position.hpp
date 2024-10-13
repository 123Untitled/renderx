/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_POSITION_HEADER___
#define ___ENGINE_POSITION_HEADER___

#include "renderx/vk/format.hpp"


// -- V X  N A M E S P A C E --------------------------------------------------

namespace vx {


	// -- P O S I T I O N -----------------------------------------------------

	template <vk::u32 ___size, typename ___type>
	class position final {


		// -- assertions ------------------------------------------------------

		/* check size */
		static_assert(___size == 2U || ___size == 3U,
			"vertex position size must be 2 or 3");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vx::position<___size, ___type>;


			// -- private members ---------------------------------------------

			/* data */
			___type _data[___size];


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr position(void) noexcept
			: _data{} {
			}

			/* member constructor */
			template <typename... ___params>
			constexpr position(const ___params&... ___args) noexcept
			: _data{static_cast<value_type>(___args)...} {
			}

			/* copy constructor */
			constexpr position(const ___self&) noexcept = default;

			/* move constructor */
			constexpr position(___self&&) noexcept = default;

			/* destructor */
			constexpr ~position(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* x */
			constexpr auto x(void) const noexcept -> value_type {
				return _data[0U];
			}

			/* y */
			constexpr auto y(void) const noexcept -> value_type {
				return _data[1U];
			}

			/* z */
			constexpr auto z(void) const noexcept -> value_type requires(___size == 3U) {
				return _data[2U];
			}


			// -- public modifiers --------------------------------------------

			/* x */
			constexpr auto x(const value_type& ___x) noexcept -> void {
				_data[0U] = ___x;
			}

			/* y */
			constexpr auto y(const value_type& ___y) noexcept -> void {
				_data[1U] = ___y;
			}

			/* z */
			constexpr auto z(const value_type& ___z) noexcept -> void  requires(___size == 3U) {
				_data[2U] = ___z;
			}


			// -- public static methods ---------------------------------------

			/* format */
			static consteval auto format(void) noexcept -> vk::format {
				return vk::pixel_format<value_type, ___size>();
			}

	}; // class position


	// -- aliases -------------------------------------------------------------

	/* position 2D */
	template <typename ___type>
	using position2D = vx::position<2U, ___type>;

	/* float2 */
	using float2 = vx::position<2U, float>;

	/* double2 */
	using double2 = vx::position<2U, double>;

	/* position 3D */
	template <typename ___type>
	using position3D = vx::position<3U, ___type>;

	/* float3 */
	using float3 = vx::position<3U, float>;

	/* double3 */
	using double3 = vx::position<3U, double>;

} // namespace vx

#endif // ___ENGINE_POSITION_HEADER___
