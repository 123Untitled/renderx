/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_RENDERPASS___
#define ___ENGINE_VULKAN_RENDERPASS___

#include "renderx/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- R E N D E R  P A S S ------------------------------------------------

	class render_pass final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::render_pass;


			// -- private members ---------------------------------------------

			/* render pass */
			vk::render_pass _render_pass;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			render_pass(void);

			/* deleted copy constructor */
			render_pass(const ___self&) = delete;

			/* move constructor */
			render_pass(___self&&) noexcept;

			/* destructor */
			~render_pass(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::render_pass&;


		private:

			// -- private static methods --------------------------------------

			/* create render pass */
			static auto _create_render_pass(void) -> vk::render_pass;

	}; // class render_pass

} // namespace vulkan

#endif // ___ENGINE_VULKAN_RENDERPASS___
