#include "engine/vulkan/debug_utils_messenger.hpp"
#include "engine/system/write.hpp"

/* callback */
VKAPI_ATTR auto VKAPI_CALL
vulkan::debug_utils_messenger::_callback(const vk::debug_utils_message_severity_flag_bit severity,
										 const vk::debug_utils_message_type_flags type,
										 const vk::debug_utils_messenger_callback_data* cdata,
										 void*) -> vk::bool32 {

	switch (severity) {

		// verbose
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			vk::write("\x1b[7;35m verbose: ");
			break;

		// info
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			vk::write("\x1b[7;36m info: ");
			break;

		// warning
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			vk::write("\x1b[7;32m warning: ");
			break;

		// error
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			vk::write("\x1b[7;31m error: ");
			break;

		default:
			break;
	}

	// general
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		vk::write("[general] \x1b[0m\r\n");

	// validation
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		vk::write("[validation] \x1b[0m\r\n");

	// performance
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		vk::write("[performance] \x1b[0m\r\n");


	std::cerr << cdata->pMessage << std::endl << std::endl;

	return VK_FALSE;
}
