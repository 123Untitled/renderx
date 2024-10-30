#ifndef ___ve_vulkan_command_pool___
#define ___ve_vulkan_command_pool___

#include "ve/vk/unique.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- C O M M A N D  P O O L ----------------------------------------------

	class command_pool final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::command_pool;


			// -- private members ---------------------------------------------

			/* pool */
			vk::unique<vk::command_pool> _pool;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_pool(void);

			/* flags constructor */
			command_pool(const vk::command_pool_create_flags&);

			/* deleted copy constructor */
			command_pool(const ___self&) = delete;

			/* move constructor */
			command_pool(___self&&) noexcept = default;

			/* destructor */
			~command_pool(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* const vk::command_pool& conversion operator */
			operator const vk::command_pool&(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* reset to system */
			auto reset_to_system(void) const -> void;

			/* reset to pool */
			auto reset_to_pool(void) const -> void;

			/* trim */
			auto trim(void) const noexcept -> void;

	}; // class command_pool

} // namespace ve

#endif // ___ve_vulkan_command_pool___
