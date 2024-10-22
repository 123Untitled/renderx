/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_VULKAN_QUEUE___
#define ___ENGINE_VULKAN_QUEUE___

#include <vulkan/vulkan.h>
#include "ve/vulkan/commands.hpp"
#include "ve/vulkan/swapchain.hpp"
#include "ve/vulkan/fence.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- Q U E U E -----------------------------------------------------------

	class queue final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::queue;


			// -- private members ---------------------------------------------

			/* queue */
			vk::queue _queue;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			queue(void) noexcept;


			// -- public static methods ---------------------------------------

			/* info */
			static auto info(const vk::u32, const float&) noexcept -> vk::device_queue_info;


			// -- public methods ----------------------------------------------

			auto submit(const vk::semaphore& wait,
						const vk::semaphore& signal,
						const vk::fence& fence,
						const vulkan::command_buffer<vulkan::primary>&) const -> void;

			/* present */
			auto present(const vulkan::swapchain&,
						 const vk::u32&,
						 const vk::semaphore&) const -> vk::result;


			/* wait idle */
			auto wait_idle(void) const -> void;

	}; // class queue

} // namespace vulkan

#endif // ___ENGINE_VULKAN_QUEUE___
