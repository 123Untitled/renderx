/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_INSTANCE___
#define ___RENDERX_VULKAN_INSTANCE___

#include "ve/vk/unique.hpp"
#include "ve/vulkan/physical_device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/array.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- I N S T A N C E -----------------------------------------------------

	class instance final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::instance;


			// -- private members ---------------------------------------------

			/* instance */
			vk::unique<vk::instance> _instance;

			/* messenger */
			#if defined(ENGINE_VL_DEBUG)
			vk::debug_utils_messenger _messenger;
			#endif


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self&;

			/* extension properties */
			static auto extension_properties(void) -> std::vector<vk::extension_properties>;

			/* layer properties */
			static auto layer_properties(void) -> std::vector<vk::layer_properties>;

			/* messenger info */
			#if defined(ENGINE_VL_DEBUG)
			static constexpr auto _messenger_info(void) noexcept -> vk::debug_utils_messenger_info {

				// create info
				return vk::debug_utils_messenger_info {

					// structure type
					.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,

					// next structure
					.pNext           = nullptr,

					// flags
					.flags           = 0U,

					// message severity
					.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,

					// message type
					.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,

					// callback
					.pfnUserCallback = ___self::_callback,

					// user data (optional)
					.pUserData       = nullptr
				};
			}

			/* callback */
			static VKAPI_ATTR auto VKAPI_CALL
			_callback(const vk::debug_utils_message_severity_flag_bit,
					  const vk::debug_utils_message_type_flags,
					  const vk::debug_utils_messenger_callback_data*,
					  void*) -> vk::bool32;

			#endif // ENGINE_VL_DEBUG


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			instance(void);

			/* deleted copy constructor */
			instance(const ___self&) = delete;

			/* deleted move constructor */
			instance(___self&&) = delete;

			/* destructor */
			~instance(void) noexcept;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> const vk::instance&;

			/* physical devices */
			static auto physical_devices(void) -> const std::vector<vulkan::physical_device>&;

	}; // class instance

} // namespace vulkan

#endif // ___RENDERX_VULKAN_INSTANCE___
