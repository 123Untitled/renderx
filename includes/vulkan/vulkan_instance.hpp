#ifndef ENGINE_VULKAN_INSTANCE_HPP
#define ENGINE_VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

#include "glfw_system.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- V U L K A N  I N S T A N C E ----------------------------------------

	class instance final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::instance;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			instance(void) noexcept
			: _instance{nullptr} {

				::VkApplicationInfo info{};
				info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				info.pApplicationName   = "application";
				info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				info.pEngineName        = "engine";
				info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);

				::VkInstanceCreateInfo create{};
				create.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				create.pApplicationInfo = &info;

				//extension_properties();

				std::vector<const char*> extensions = glfw::system::vulkan_required_extensions();

// check macos system
#if defined(__APPLE__) && defined(__MACH__)
				extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
				create.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

				create.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size());
				create.ppEnabledExtensionNames = extensions.data();

				create.enabledLayerCount       = 0;

				::VkResult result = ::vkCreateInstance(&create, nullptr, &_instance);

				if (result != VK_SUCCESS)
					std::cerr << "error: failed to create vulkan instance ["
					          << result << "]" << std::endl;
			}


			/* deleted copy constructor */
			instance(const self&) = delete;

			/* move constructor */
			instance(self&& other) noexcept
			: _instance{other._instance} {
				other._instance = nullptr;
			}

			/* destructor */
			~instance(void) noexcept {
				free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				if (this == &other)
					return *this;
				free();
				_instance = other._instance;
				other._instance = nullptr;
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* VkInstance conversion operator */
			operator const ::VkInstance&(void) const noexcept {
				return _instance;
			}

			/* VkInstance conversion operator */
			operator ::VkInstance&(void) noexcept {
				return _instance;
			}



			/* extension properties */
			auto extension_properties(void) const noexcept -> std::vector<::VkExtensionProperties> {
				::uint32_t count = 0;
				::VkResult result = ::vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
				if (result != VK_SUCCESS)
					return {};
				std::vector<::VkExtensionProperties> properties;
				properties.resize(count);
				result = ::vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
				if (result != VK_SUCCESS)
					return {};

				for (const auto& property : properties)
					std::cout << property.extensionName << std::endl;
				return properties;

			}


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				if (_instance == nullptr)
					return;
				::vkDestroyInstance(_instance, nullptr);
			}

			/* init */
			auto init(void) noexcept -> void {
				_instance = nullptr;
			}




			// -- private members ---------------------------------------------

			/* instance */
			::VkInstance _instance;

	};

}

#endif // ENGINE_VULKAN_INSTANCE_HPP
