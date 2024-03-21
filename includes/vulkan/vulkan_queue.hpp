/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_QUEUE_HPP
#define ENGINE_VULKAN_QUEUE_HPP


#include <vulkan/vulkan.h>
#include "vulkan_device.hpp"
#include "vulkan_semaphore.hpp"
#include "vulkan/command_buffer.hpp"
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

			/* device constructor */
			queue(const vulkan::device&) noexcept;


			// -- public static methods ---------------------------------------

			/* info */
			static auto info(const vk::u32, const float&) noexcept -> vk::device_queue_info;


			// -- public methods ----------------------------------------------

			/* submit */ // not thread safe
			template <decltype(sizeof(0)) W, decltype(sizeof(0)) S>
			auto submit(const vk::semaphore (&wait)[W],
						const vk::semaphore (&signal)[S],
						const vulkan::command_buffer<vulkan::primary>* buffers,
						vk::u32 buffer_count) const -> void {

				const ::VkPipelineStageFlags wait_stages[] = {
						VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
				};

				const vk::submit_info info{
					// structure type
					.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
					.pNext                = nullptr,

					// wait semaphores
					.waitSemaphoreCount   = W,
					.pWaitSemaphores      = wait,
						//reinterpret_cast<const ::VkSemaphore*>(wait),

					// wait stages
					.pWaitDstStageMask    = wait_stages,

					// command buffers
					.commandBufferCount   = buffer_count,
					/* command_buffers[image_index] */
					.pCommandBuffers      = reinterpret_cast<const ::VkCommandBuffer*>(buffers),

					// signal semaphores
					.signalSemaphoreCount = S,
					.pSignalSemaphores    = signal //
						//reinterpret_cast<const ::VkSemaphore*>(signal)
				};


				// see vkQueueSubmit2KHR
				if (::vkQueueSubmit(
						_queue,
						1, // submit count
						&info,
						nullptr // fence
						) != VK_SUCCESS)
					throw engine::exception{"failed to submit draw command buffer"};
			}



			/* present */
			template <decltype(sizeof(0)) W>
			auto present(const vulkan::swapchain& swapchain,
						 const vk::u32            image_index,
						 const vk::semaphore      (&wait)[W]) const -> bool {

				const vk::present_info info{
					.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
					.pNext              = nullptr,

					.waitSemaphoreCount = W,
					.pWaitSemaphores    = wait,

					.swapchainCount     = 1, // swapchain count ???
					.pSwapchains        = &(static_cast<const vk::swapchain&>(swapchain)),
					.pImageIndices      = &image_index,
					.pResults           = nullptr // VkResult array, optional
				};

				// here error not means program must stop
				if (::vkQueuePresentKHR(_queue, &info) != VK_SUCCESS) {
					std::cout << "failed to present swapchain image" << std::endl;
					return false;
				}

				return true;


			}


		private:

			// -- private members ---------------------------------------------

			/* underlying */
			vk::queue _queue;

	}; // class queue

} // namespace vulkan

#endif // ENGINE_VULKAN_QUEUE_HPP
