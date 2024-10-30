#ifndef ___ve_vulkan_semaphore___
#define ___ve_vulkan_semaphore___

#include "ve/vk/unique.hpp"
#include "ve/vk/typedefs.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S E M A P H O R E ----------------------------------------------------

	class semaphore final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::semaphore;


			// -- private members ---------------------------------------------

			/* semaphore */
			vk::unique<vk::semaphore> _semaphore;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			semaphore(void);

			/* deleted copy constructor */
			semaphore(const ___self&) = delete;

			/* move constructor */
			semaphore(___self&&) noexcept = default;

			/* destructor */
			~semaphore(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::semaphore&;

	}; // class semaphore

} // namespace ve

#endif // ___ve_vulkan_semaphore___
