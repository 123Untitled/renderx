/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ENGINE_VULKAN_FENCE_HPP
#define ENGINE_VULKAN_FENCE_HPP

#include "engine/vk/typedefs.hpp"

namespace vulkan {


	class fence final {

		public:

			fence(void) {

				vk::fence_info info {
					// structure type
					VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
					// next structure
					nullptr,
					// flag
					0U
				};

				vk::fence _fence;

				::vkCreateFence(nullptr/*device*/, &info, nullptr, &_fence);

				::vkWaitForFences(nullptr/*device*/, 1U, &_fence, VK_TRUE, UINT64_MAX);

				::vkResetFences(nullptr/*device*/, 1U, &_fence);

				::vkDestroyFence(nullptr/*device*/, _fence, nullptr);
			}

		private:

	};

} // namespace vulkan

#endif // ENGINE_VULKAN_FENCE_HPP
