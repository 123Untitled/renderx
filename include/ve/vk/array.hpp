/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_ARRAY_HEADER___
#define ___ENGINE_VULKAN_ARRAY_HEADER___

#include "ve/vk/typedefs.hpp"
#include <type_traits>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- A R R A Y -----------------------------------------------------------

	template <typename ___type, vk::u32 ___size>
	class array final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::array<___type, ___size>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = ___type;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer         = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = decltype(___size);


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[___size];


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](size_type i) noexcept -> reference {
				return _data[i];
			}

			/* subscript operator */
			constexpr auto operator[](size_type i) const noexcept -> const_reference {
				return _data[i];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return ___size;
			}

			/* data */
			constexpr auto data(void) noexcept -> pointer {
				return _data;
			}

			/* data */
			constexpr auto data(void) const noexcept -> const_pointer {
				return _data;
			}

	}; // class array


	// -- deduction guides ----------------------------------------------------

	template <typename... ___types>
	array(___types&&...) -> array<std::common_type_t<___types...>, sizeof...(___types)>;

} // namespace vk

#endif // ___ENGINE_VULKAN_ARRAY_HEADER___
