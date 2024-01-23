#ifndef ENGINE_VK_UTILS_HPP
#define ENGINE_VK_UTILS_HPP

#include <xns>
#include "vk_typedefs.hpp"
#include "vulkan_exception.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- types ---------------------------------------------------------------

	/* unsigned integer 32 type */
	using u32 = ::uint32_t;

	/* vector type */
	template <typename T>
	using vector = xns::vector<T>;



	/* try execute */
	template <decltype(sizeof(0)) N, typename F, typename... A>
	inline auto try_execute(F&& f, const char (&msg)[N], A&&... args) -> void {
		// get return type
		using ret_type = decltype(f(xns::forward<A>(args)...));
		// assert return type is vk::result
		static_assert(xns::is_same<ret_type, vk::result>, "invalid return type.");
		// execute function
		if (auto result = f(xns::forward<A>(args)...); result != VK_SUCCESS)
			throw vulkan::exception{msg, result};
	}


} // namespace vk

#endif // ENGINE_VK_UTILS_HPP
