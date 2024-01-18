#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include "vulkan_instance.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::physical_device;


			// -- public lifecycle --------------------------------------------

			/* copy constructor */
			physical_device(const self&) noexcept;

			/* move constructor */
			physical_device(self&&) noexcept;

			/* destructor */
			~physical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;



			// -- public static methods ---------------------------------------

			/* pick physical device */
			static auto pick(const vulkan::instance&) -> self;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) noexcept -> ::VkPhysicalDevice&;

			/* const underlying */
			auto underlying(void) const noexcept -> const ::VkPhysicalDevice&;



		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			physical_device(void) noexcept;

			/* ::VkPhysicalDevice constructor */
			physical_device(const ::VkPhysicalDevice&) noexcept;


			// -- private static methods --------------------------------------

			/* enumerate physical devices */
			static auto enumerate(const vulkan::instance&) -> std::vector<::VkPhysicalDevice>;

			/* is device suitable */
			static auto is_suitable(const ::VkPhysicalDevice&) noexcept -> bool;

			/* device type */
			static auto type(const ::VkPhysicalDeviceProperties&) noexcept -> void;

			/* device features */
			static auto features(const ::VkPhysicalDeviceFeatures&) noexcept -> void;


			// -- private members ---------------------------------------------

			/* device */
			::VkPhysicalDevice _device;

	};

}

#endif // ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
