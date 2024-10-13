#ifndef ___RENDERX_VK_UTILS___
#define ___RENDERX_VK_UTILS___

#include "renderx/meta/string_literal.hpp"
#include "renderx/vk/exception.hpp"

#include <__utility/forward.h>
#include <concepts>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {

	/* try execute */
	template <rx::string_literal ___msg, typename ___function, typename... ___params>
	inline auto try_execute(___function&& ___func, ___params&&... ___args) -> void {

		// assert return type is vk::result
		static_assert(std::same_as<decltype(___func(std::forward<___params>(___args)...)),
								   vk::result>, "invalid return type");

		// execute function
		if (auto ___result = ___func(std::forward<___params>(___args)...); ___result != VK_SUCCESS)
			throw vk::exception{___msg.data(), ___result};
	}

} // namespace vk

#endif // ___RENDERX_VK_UTILS___
