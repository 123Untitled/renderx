#ifndef ENGINE_VULKAN_QUEUE_HPP
#define ENGINE_VULKAN_QUEUE_HPP


#include <vulkan/vulkan.h>
#include "vulkan_logical_device.hpp"
#include "vulkan_semaphore.hpp"
#include "vulkan_command_buffer.hpp"
#include "vulkan_swapchain.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- Q U E U E -----------------------------------------------------------

	class queue final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::queue;

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			queue(void) noexcept = default;

			/* device and queue family index constructor */
			queue(const vulkan::logical_device&, const vk::u32) noexcept;


			// -- public static methods ---------------------------------------

			/* create queue info */
			static auto create_queue_info(const vk::u32, const float&) noexcept -> vk::device_queue_info;


			// -- public methods ----------------------------------------------

			/* submit */
			auto submit(const vulkan::semaphore* wait,
						::uint32_t wait_count,
						const vulkan::semaphore* signal,
						::uint32_t signal_count,
						const vulkan::command_buffer* buffers,
						::uint32_t buffer_count) const -> void;

			/* present */
			auto present(const vulkan::swapchain&,
						 ::uint32_t,
						const vulkan::semaphore* wait,
						 ::uint32_t wait_count) const -> bool;


		private:

			// -- private members ---------------------------------------------

			/* underlying */
			vk::queue _queue;

	}; // class queue

} // namespace vulkan

#endif // ENGINE_VULKAN_QUEUE_HPP
