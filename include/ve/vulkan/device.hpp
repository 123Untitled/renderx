#ifndef ___ve_vulkan_device___
#define ___ve_vulkan_device___

//#include "ve/vk/unique.hpp"
#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/surface.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E V I C E ---------------------------------------------------------

	class device final {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using ___self = vulkan::device;


			// -- private members ---------------------------------------------

			/* logical device */
			vk::device _ldevice;

			/* queue family */
			vk::u32 _family;

			/* queue priority */
			float _priority;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			device(void);

			/* deleted copy constructor */
			device(const ___self&) = delete;

			/* deleted move constructor */
			device(___self&&) = delete;

			/* destructor */
			~device(void) noexcept;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static accessors -------------------------------------

			/* logical */
			static auto logical(void) -> const vk::device&;

			/* physical */
			static auto physical(void) -> const ve::physical_device&;

			/* queue family */
			static auto family(void) -> const vk::u32&;


			// -- public static methods ---------------------------------------

			/* wait idle */
			static auto wait_idle(void) -> void;

	}; // class device

} // namespace vulkan

#endif // ___ENGINE_VULKAN_DEVICE___
