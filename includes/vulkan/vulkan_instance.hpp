#ifndef ENGINE_VULKAN_INSTANCE_HPP
#define ENGINE_VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>


#include "glfw_system.hpp"
#include "exceptions.hpp"


#include <xns>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* physical device */
	class physical_device;

	/* surface */
	class surface;


	// -- V U L K A N  I N S T A N C E ----------------------------------------

	class instance final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::instance;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			instance(const self&) = delete;

			/* deleted move constructor */
			instance(self&&) noexcept = delete;

			/* destructor */
			~instance(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public conversion operators ---------------------------------

			/* VkInstance conversion operator */
			operator const ::VkInstance&(void) const noexcept;


			// -- public accessors --------------------------------------------



			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> self&;

			/* physical devices */
			static auto physical_devices(void) -> xns::vector<vulkan::physical_device>;

			/* pick physical device */
			static auto pick_physical_device(const vulkan::surface&) -> vulkan::physical_device;


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			instance(void);


			// -- private static methods --------------------------------------

			/* extension properties */
			static auto extension_properties(void) -> std::vector<::VkExtensionProperties>;

			/* layer properties */
			static auto layer_properties(void) -> xns::vector<::VkLayerProperties>;


			/* callback */
			#if defined(ENGINE_VL_DEBUG)

			using message_severity = ::VkDebugUtilsMessageSeverityFlagBitsEXT;
			using message_type     = ::VkDebugUtilsMessageTypeFlagsEXT;
			using callback_data    = ::VkDebugUtilsMessengerCallbackDataEXT;

			/* callback */
			static VKAPI_ATTR VkBool32 VKAPI_CALL callback(const message_severity,
														   const message_type,
														   const callback_data*, void*);
			#endif


			// -- private members ---------------------------------------------

			/* instance */
			::VkInstance _instance;

			/* debug messenger */
			#if defined(ENGINE_VL_DEBUG)
			::VkDebugUtilsMessengerEXT _messenger;
			#endif

	};

}

#endif // ENGINE_VULKAN_INSTANCE_HPP
