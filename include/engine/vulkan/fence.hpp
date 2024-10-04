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
#include "engine/vk/shared.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- F E N C E -----------------------------------------------------------

	class fence final {

		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::fence;


			// -- private members ---------------------------------------------

			/* fence */
			vk::shared<vk::fence> _fence;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			fence(void) noexcept = default;

			/* device constructor */
			fence(const vk::shared<vk::device>& ___dev)
			: _fence{___dev, vk::fence_info{
					// structure type
					VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
					// next structure
					nullptr,
					// flag
					0U
				}} {

				//
			}

			// -- public methods ----------------------------------------------

			/* reset */
			auto reset(const vk::shared<vk::device>& ___dev) -> void {
				//::vkResetFences(___dev, 1U, _fence);
			}

			/* wait */
			auto wait(const vk::shared<vk::device>& ___dev) -> void {

				const vk::fence& ___fc = _fence;

				const vk::device& ___dv = ___dev;

				::vkWaitForFences(___dv,
						1U, &___fc, VK_TRUE, UINT64_MAX);
			}


	};

} // namespace vulkan

#endif // ENGINE_VULKAN_FENCE_HPP
