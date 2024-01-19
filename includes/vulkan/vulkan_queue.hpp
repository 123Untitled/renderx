#ifndef ENGINE_VULKAN_QUEUE_HPP
#define ENGINE_VULKAN_QUEUE_HPP


#include <vulkan/vulkan.h>
#include "vulkan_logical_device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- Q U E U E -----------------------------------------------------------

	class queue final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue;

			// -- public lifecycle --------------------------------------------

			/* device and queue family index constructor */
			queue(const vulkan::logical_device&, const ::uint32_t) noexcept;


			// -- public static methods ---------------------------------------

			/* create queue info */
			static auto create_queue_info(const ::uint32_t, const float&) noexcept -> ::VkDeviceQueueCreateInfo;


		private:

			// -- private members ---------------------------------------------

			/* underlying */
			::VkQueue _queue;

	}; // class queue

} // namespace vulkan

#endif // ENGINE_VULKAN_QUEUE_HPP
