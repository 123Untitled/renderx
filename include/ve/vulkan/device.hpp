/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_DEVICE___
#define ___ENGINE_VULKAN_DEVICE___

#include "ve/vk/typedefs.hpp"
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

			/* physical device */
			vulkan::physical_device _pdevice;

			/* queue family */
			vk::u32 _family;

			/* queue priority */
			float _priority;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;

			/* pick physical device */
			static auto _pick_physical_device(const vk::surface&) -> vulkan::physical_device;


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
			static auto logical(void) noexcept -> const vk::device&;

			/* physical */
			static auto physical(void) noexcept -> const vulkan::physical_device&;

			/* queue family */
			static auto family(void) noexcept -> const vk::u32&;


			// -- public static methods ---------------------------------------

			/* wait idle */
			static auto wait_idle(void) -> void;

	}; // class device

} // namespace vulkan

#endif // ___ENGINE_VULKAN_DEVICE___
