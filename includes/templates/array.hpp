#pragma once

#ifndef ENGINE_VULKAN_ARRAY_HEADER
#define ENGINE_VULKAN_ARRAY_HEADER


#include "vulkan/vk_typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- A R R A Y -----------------------------------------------------------

	template <typename T, vk::u32 N>
	class array final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::array<T, N>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref = T&;

			/* constant reference type */
			using const_ref = const T&;

			/* mutable pointer type */
			using mut_ptr = T*;

			/* constant pointer type */
			using const_ptr = const T*;

			/* size type */
			using size_type = decltype(N);


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[N];


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			inline constexpr auto operator[](size_type i) noexcept -> mut_ref {
				return _data[i];
			}

			/* subscript operator */
			inline constexpr auto operator[](size_type i) const noexcept -> const_ref {
				return _data[i];
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline constexpr auto size(void) const noexcept -> size_type {
				return N;
			}

			/* data */
			inline constexpr auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* data */
			inline constexpr auto data(void) const noexcept -> const_ptr {
				return _data;
			}

	}; // class array


	// -- deduction guides ----------------------------------------------------

	template <typename... T>
	array(T&&...) -> array<std::common_type_t<T...>, sizeof...(T)>;

} // namespace vk

#endif // ENGINE_VULKAN_ARRAY_HEADER
