/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_SEMAPHORE___
#define ___RENDERX_VULKAN_SEMAPHORE___

#include "renderx/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- S E M A P H O R E ----------------------------------------------------

	class semaphore final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::semaphore;


			// -- private members ---------------------------------------------

			/* semaphore */
			vk::semaphore _semaphore;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			semaphore(void);

			/* deleted copy constructor */
			semaphore(const ___self&) = delete;

			/* move constructor */
			semaphore(___self&&) noexcept;

			/* destructor */
			~semaphore(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::semaphore&;

	}; // class semaphore

} // namespace vulkan

#endif // ___RENDERX_VULKAN_SEMAPHORE___
