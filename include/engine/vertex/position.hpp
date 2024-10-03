/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_POSITION_HEADER
#define ENGINE_POSITION_HEADER

//#include <vulkan/vulkan.hpp>

#include "engine/vk/format.hpp"


// -- V X  N A M E S P A C E --------------------------------------------------

namespace vx {


	// -- P O S I T I O N ------------------------------------------------------

	template <typename ___type>
	class position final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vx::position<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr position(void) noexcept
			: _data{static_cast<value_type>(0),
					static_cast<value_type>(0),
					static_cast<value_type>(0)} {
			}

			/* member constructor */
			constexpr position(const value_type& ___x,
							   const value_type& ___y,
							   const value_type& ___z) noexcept
			: _data{___x, ___y, ___z} {
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
				return _data[0];
			}

			/* y */
			constexpr auto y(void) const noexcept -> value_type {
				return _data[1];
			}

			/* z */
			constexpr auto z(void) const noexcept -> value_type {
				return _data[2];
			}


			// -- public modifiers --------------------------------------------

			/* x */
			constexpr auto x(const value_type& ___x) noexcept -> void {
				_data[0] = ___x;
			}

			/* y */
			constexpr auto y(const value_type& ___y) noexcept -> void {
				_data[1] = ___y;
			}

			/* z */
			constexpr auto z(const value_type& ___z) noexcept -> void {
				_data[2] = ___z;
			}


			// -- public static methods ---------------------------------------

			/* format */
			static consteval auto format(void) noexcept -> vk::format {
				return vk::pixel_format<value_type, 3>();
			}


		private:

			// -- private members ---------------------------------------------

			/* data */
			value_type _data[3];

	}; // class position

} // namespace vx

#endif // ENGINE_POSITION_HEADER
