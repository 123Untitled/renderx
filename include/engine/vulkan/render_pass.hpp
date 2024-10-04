/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ENGINE_VULKAN_RENDERPASS_HEADER
#define ENGINE_VULKAN_RENDERPASS_HEADER

// vulkan headers
#include <vulkan/vulkan.h>

#include "engine/vk/typedefs.hpp"
#include "engine/vk/shared.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* device */
	class device;


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::render_pass;


			// -- private members ---------------------------------------------

			/* render pass */
			vk::shared<vk::render_pass> _render_pass;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			render_pass(void) noexcept = default;

			/* logical device constructor */
			render_pass(const vulkan::device&);

			/* copy constructor */
			render_pass(const ___self&) noexcept = default;

			/* move constructor */
			render_pass(___self&&) noexcept = default;

			/* destructor */
			~render_pass(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* underlying conversion operator */
			operator const vk::render_pass&(void) const noexcept;

			/* shared conversion operator */
			operator const vk::shared<vk::render_pass>&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create render pass */
			static auto _create_render_pass(const vulkan::device&) -> vk::shared<vk::render_pass>;

	}; // class render_pass

} // namespace vulkan

#endif // ENGINE_VULKAN_RENDERPASS_HEADER
