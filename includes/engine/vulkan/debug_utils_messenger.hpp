#pragma once

#ifndef ENGINE_VULKAN_DEBUG_UTILS_MESSENGER_HEADER
#define ENGINE_VULKAN_DEBUG_UTILS_MESSENGER_HEADER

#if defined(ENGINE_VL_DEBUG)

#include "engine/vk/array.hpp"
#include "engine/vk/shared.hpp"
#include "engine/vk/typedefs.hpp"
#include "engine/vk/destroy.hpp"

#include <vulkan/vulkan.hpp>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- D E B U G  U T I L S  M E S S E N G E R -----------------------------

	class debug_utils_messenger final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::debug_utils_messenger;


			// -- private members ---------------------------------------------

			/* messenger */
			vk::debug_utils_messenger _messenger;

			/* instance */
			vk::shared<vk::instance> _instance;


			// -- private static methods --------------------------------------

			/* callback */
			static VKAPI_ATTR auto VKAPI_CALL
			_callback(const vk::debug_utils_message_severity_flag_bit,
					  const vk::debug_utils_message_type_flags,
					  const vk::debug_utils_messenger_callback_data*,
					  void*) -> vk::bool32;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			debug_utils_messenger(void) = delete;

			/* default constructor */
			debug_utils_messenger(const vk::shared<vk::instance>& instance)
			: _messenger(vk::create(instance, debug_info())),
			  _instance(instance) {
			}

			/* deleted copy constructor */
			debug_utils_messenger(const ___self&) = delete;

			/* move constructor */
			debug_utils_messenger(___self&&) noexcept = default;

			/* destructor */
			~debug_utils_messenger(void) noexcept {

				// destroy messenger
				vk::destroy(_instance, _messenger);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public static methods ---------------------------------------

			/* debug info */
			static constexpr auto debug_info(void) noexcept -> vk::debug_utils_messenger_info {

				// return debug info
				return vk::debug_utils_messenger_info {
					.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
					.pNext           = nullptr,
					.flags           = 0U,
					.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
					.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
									 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
					.pfnUserCallback = ___self::_callback,
					.pUserData       = nullptr // optional (user data)
				};
			}

	}; // class debug_utils_messenger

} // namespace vulkan

#endif // ENGINE_VL_DEBUG

#endif // ENGINE_VULKAN_DEBUG_UTILS_MESSENGER_HEADER
