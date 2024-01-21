#ifndef ENGINE_VULKAN_EXTENSION_PROPERTIES_HPP
#define ENGINE_VULKAN_EXTENSION_PROPERTIES_HPP

// vulkan headers
#include <vulkan/vulkan.h>

#include "vulkan_physical_device.hpp"
#include <xns>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {

	// -- E X T E N S I O N  P R O P E R T I E S --------------------------------

	class extension_properties final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::extension_properties;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			extension_properties(void) noexcept;

			/* copy constructor */
			extension_properties(const self&) noexcept;

			/* move constructor */
			extension_properties(self&&) noexcept;

			/* destructor */
			~extension_properties(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* name */
			auto name(void) const noexcept -> xns::string_view;

			/* version */
			auto version(void) const noexcept -> xns::u32;

			/* support swapchain */
			auto supports_swapchain(void) const noexcept -> bool;


			// -- public static methods ---------------------------------------

			/* get all extension properties */
			static auto extensions(const vulkan::physical_device&) -> xns::vector<self>;


		private:

			// -- private members ---------------------------------------------

			/* properties */
			::VkExtensionProperties _properties;

	}; // class extension_properties


	/* assert extension properties size matches */
	static_assert(sizeof(vulkan::extension_properties) == sizeof(::VkExtensionProperties),
				"): EXTENSION_PROPERTIES SIZE MISMATCH! :(");


} // namespace vulkan

#endif // ENGINE_VULKAN_EXTENSION_PROPERTIES_HPP
