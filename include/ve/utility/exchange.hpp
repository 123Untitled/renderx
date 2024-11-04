#ifndef ___ve_utility_exchange___
#define ___ve_utility_exchange___

#include <utility>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {

	template <typename T, typename U = T>
	constexpr auto exchange(T& obj, U&& new_value) noexcept(std::is_nothrow_move_constructible<T>::value
														 && std::is_nothrow_assignable<T&, U>::value) -> T {
		T old_value = std::move(obj);
		obj = std::forward<U>(new_value);
		return old_value;
	}

} // namespace ve

#endif // ___ve_utility_exchange___
