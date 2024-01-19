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

			/* deleted copy constructor */
			extension_properties(const self&) = delete;

			/* move constructor */
			extension_properties(self&&) noexcept;

			/* destructor */
			~extension_properties(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* name */
			auto name(void) const noexcept -> const xns::string&;

			/* version */
			auto version(void) const noexcept -> xns::u32;


			// -- public static methods ---------------------------------------

			/* get all extension properties */
			static auto get(const vulkan::physical_device&) -> xns::vector<self>;


		private:

			// -- private members ---------------------------------------------

			/* name */
			xns::string _name;

			/* version */
			xns::u32 _version;

	}; // class extension_properties

} // namespace vulkan

#endif // ENGINE_VULKAN_EXTENSION_PROPERTIES_HPP
