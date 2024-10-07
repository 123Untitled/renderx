/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_FENCE___
#define ___RENDERX_VULKAN_FENCE___

#include "engine/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- F E N C E -----------------------------------------------------------

	class fence final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::fence;


			// -- private members ---------------------------------------------

			/* fence */
			vk::fence _fence;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			fence(void) = delete;

			/* flags constructor */
			fence(const vk::fence_create_flags& = VK_FENCE_CREATE_SIGNALED_BIT);

			/* deleted copy constructor */
			fence(const ___self&) = delete;

			/* move constructor */
			fence(___self&&) noexcept;

			/* destructor */
			~fence(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::fence&;


			// -- public methods ----------------------------------------------

			/* reset */
			auto reset(void) -> void;

			/* wait */
			auto wait(void) -> void;

	}; // class fence

} // namespace vulkan

#endif // ___RENDERX_VULKAN_FENCE___
