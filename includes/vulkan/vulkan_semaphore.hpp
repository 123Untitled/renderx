#ifndef ENGINE_VULKAN_SEMAPHORE_HPP
#define ENGINE_VULKAN_SEMAPHORE_HPP


// vulkan headers
#include <vulkan/vulkan.h>

#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S E M A P H O R E ----------------------------------------------------

	class semaphore final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::semaphore;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			semaphore(void) noexcept;

			/* logical device constructor */
			semaphore(const vulkan::logical_device&);


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* VkSemaphore conversion operator */
			operator const ::VkSemaphore&(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* semaphore */
			::VkSemaphore _semaphore;

	}; // class semaphore


	/* assert semaphore size matches */
	static_assert(sizeof(vulkan::semaphore) == sizeof(::VkSemaphore),
			"): SEMAPHORE SIZE MISMATCH! :(");



} // namespace vulkan

#endif // ENGINE_VULKAN_SEMAPHORE_HPP
