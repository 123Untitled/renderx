#ifndef ___RENDERX_VK_UTILS___
#define ___RENDERX_VK_UTILS___

#include "ve/meta/string_literal.hpp"
#include "ve/vk/exception.hpp"

#include <utility>
#include <concepts>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	/* try execute */
	template <ve::literal ___msg, typename ___function, typename... ___params>
	inline auto try_execute(___function&& ___func, ___params&&... ___args) -> void {

		// assert return type is vk::result
		static_assert(std::same_as<decltype(___func(std::forward<___params>(___args)...)),
								   ::vk_result>, "invalid return type");

		// execute function
		if (auto ___result = ___func(std::forward<___params>(___args)...); ___result != VK_SUCCESS)
			throw vk::exception{___msg.data, ___result};
	}

} // namespace vk

#endif // ___RENDERX_VK_UTILS___
