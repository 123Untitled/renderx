#pragma once

#ifndef ENGINE_VULKAN_INSTANCE_HEADER
#define ENGINE_VULKAN_INSTANCE_HEADER

#include "vulkan/vk_typedefs.hpp"

#include "vulkan/vk_shared.hpp" // vk::vector
#include "vulkan/vulkan_physical_device.hpp"
#include "vulkan/vulkan_surface.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- I N S T A N C E -----------------------------------------------------

	class instance final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::instance;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			instance(const self&) = delete;

			/* deleted move constructor */
			instance(self&&) = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public conversion operators ---------------------------------

			/* vk::instance conversion operator */
			operator const vk::instance&(void) const noexcept;


			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> self&;

			/* physical devices */
			static auto physical_devices(void) -> const vk::vector<vulkan::physical_device>&;

			/* pick physical device */
			static auto pick_physical_device(const vulkan::surface&) -> vulkan::physical_device;


		private:

			// -- private lifecycle ---------------------------------------

			/* default constructor */
			instance(void);

			/* destructor */
			~instance(void) noexcept;


			// -- private static methods ----------------------------------

			/* extension properties */
			static auto extension_properties(void) -> vk::vector<vk::extension_properties>;

			/* layer properties */
			static auto layer_properties(void) -> vk::vector<vk::layer_properties>;

			/* callback */
			#if defined(ENGINE_VL_DEBUG)

			using message_severity = ::VkDebugUtilsMessageSeverityFlagBitsEXT;
			using message_type     = ::VkDebugUtilsMessageTypeFlagsEXT;
			using callback_data    = ::VkDebugUtilsMessengerCallbackDataEXT;

			/* callback */
			static VKAPI_ATTR auto VKAPI_CALL
			callback(const message_severity,
						const message_type,
						const callback_data*, void*) -> vk::bool32;

			#endif


			// -- private members -----------------------------------------

			/* instance */
			vk::instance _instance;

			/* messenger */
			#if defined(ENGINE_VL_DEBUG)
			vk::debug_utils_messenger _messenger;
			#endif

	}; // class instance

} // namespace vulkan

#endif // ENGINE_VULKAN_INSTANCE_HEADER
