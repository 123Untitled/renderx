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


	// -- V U L K A N  I N S T A N C E ----------------------------------------

	class instance final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::instance;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			instance(void);

			/* deleted copy constructor */
			instance(const self&) = delete;

			/* move constructor */
			instance(self&&) noexcept;

			/* destructor */
			~instance(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkInstance&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkInstance&;

			/* physical devices */
			auto physical_devices(void) const -> xns::vector<vulkan::physical_device>;

			/* physical devices count */
			auto physical_devices_count(void) const -> ::uint32_t;

		private:

			// -- private static methods --------------------------------------

			/* enumerate extensions */
			static auto extensions(void) -> std::vector<::VkExtensionProperties>;

			/* create application info */
			static auto create_application_info(void) noexcept -> ::VkApplicationInfo;

			/* create instance info */
			static auto create_instance_info(const ::VkApplicationInfo&,
											 const std::vector<const char*>&) noexcept -> ::VkInstanceCreateInfo;

			/* create instance */
			static auto create_instance(const ::VkInstanceCreateInfo&) -> ::VkInstance;


			// -- private methods ---------------------------------------------






			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* instance */
			::VkInstance _instance;

	};

}

#endif // ENGINE_VULKAN_INSTANCE_HPP
