#ifndef ___ve_vulkan_fence___
#define ___ve_vulkan_fence___

#include "ve/vk/unique.hpp"
#include "ve/vk/typedefs.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- F E N C E -----------------------------------------------------------

	class fence final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::fence;


			// -- private members ---------------------------------------------

			/* fence */
			vk::unique<vk::fence> _fence;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			fence(void);

			/* flags constructor */
			fence(const vk::fence_create_flags&);

			/* deleted copy constructor */
			fence(const ___self&) = delete;

			/* move constructor */
			fence(___self&&) noexcept = default;

			/* destructor */
			~fence(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::fence&;


			// -- public methods ----------------------------------------------

			/* reset */
			auto reset(void) -> void;

			/* wait */
			auto wait(void) -> void;

	}; // class fence

} // namespace ve

#endif // ___ve_vulkan_fence___
