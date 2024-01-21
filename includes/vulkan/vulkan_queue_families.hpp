#ifndef ENGINE_VULKAN_QUEUE_FAMILIES_HPP
#define ENGINE_VULKAN_QUEUE_FAMILIES_HPP

#include <vulkan/vulkan.h>
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"

#include "vk_functions.hpp"

// V U L K A N  N A M E S P A C E ---------------------------------------------

namespace vulkan {

	// -- Q U E U E  F A M I L I E S ------------------------------------------

	class queue_families final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue_families;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			queue_families(void) = delete;

			/* deleted copy constructor */
			queue_families(const self&) = delete;

			/* deleted move constructor */
			queue_families(self&&) = delete;

			/* destructor */
			~queue_families(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public static methods ---------------------------------------

			/* find */
			static auto find(const vulkan::physical_device&,
							 const vulkan::surface&) -> vk::u32;


		private:


	}; // class queue_families

} // namespace vulkan

#endif // ENGINE_VULKAN_QUEUE_FAMILIES_HPP





