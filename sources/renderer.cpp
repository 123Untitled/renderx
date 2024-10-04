/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#include "engine/renderer.hpp"



// -- public lifecycle --------------------------------------------------------

/* default constructor */
engine::renderer::renderer(void)
:
	_window{800, 600},
	_events{},
	_surface{_window},
	_device{_surface},
	_queue{_device},
	_swapchain{_device, _surface},
	_pool{_device, _device.family()},
	_cmds{_pool, _swapchain.size()},
	_image_available{_device},
	_render_finished{_device},
	_shaders{_device},
	
	_pipeline{
		vulkan::pipeline_builder<vertex_type>::build(
				_device.shared(),
				_shaders,
				_swapchain.render_pass())
	},
	_buffer{},
	_memory{},

	_vertices{},
	_fence{_device} {

		_vertices.emplace_back(
				vx::float2{+0.0f, -0.5f}, vx::float3{+1.0f, +0.0f, +0.0f}
		);

		_vertices.emplace_back(
				vx::float2{+0.5f, +0.5f}, vx::float3{+0.0f, +1.0f, +0.0f}
		);

		_vertices.emplace_back(
				vx::float2{-0.5f, +0.5f}, vx::float3{+0.0f, +0.0f, +1.0f}
		);

		_buffer = vulkan::buffer{_device, _vertices};
		_memory = vulkan::device_memory{_buffer, _device};

		std::cout << "renderer created" << std::endl;

		_memory.bind_and_map(_buffer, _vertices);



}



// -- public methods ----------------------------------------------------------

/* launch */
auto engine::renderer::launch(void) -> void {

	return ;

	while (_window.should_close() == false) {

		_events.wait();

		//_events.poll();
		self::draw_frame();

		//sleep(1);
	}

	// wait for logical device to be idle
	_device.wait_idle();
}

/* draw frame */
auto engine::renderer::draw_frame(void) -> void {

	//vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
	//vkResetFences(device, 1, &inFlightFence);

	xns::u32 image_index = 0U;

	// here error not means program must stop
	if (_swapchain.acquire_next_image(_image_available, image_index) == false)
		return;


	auto& cmd = _cmds[image_index];

	// record command buffer (see flagbits)
	cmd.reset();


	cmd.record(_swapchain,
			   _swapchain.render_pass(),
			   _swapchain.frames()[image_index],
			   _pipeline);




	vk::buffer buffs[] = {
		static_cast<vk::shared<vk::buffer>>(_buffer)
	};


	/*
	cmd.cmd_bind_vertex_buffers(buffs);
	cmd.cmd_set_viewport(_swapchain);
	cmd.cmd_set_scissor(_swapchain);
	cmd.cmd_draw(3U);
	cmd.renderpass_end();
	cmd.end();
	*/


	// maybe send img_index to queue.submit
	/* command_buffers[image_index] */
	_queue.submit({_image_available}, {_render_finished}, _cmds);
	//_queue.submit(wait, signal, _cmds);

	// here error not means program must stop
	if (_queue.present(_swapchain, image_index, {_render_finished}) == false)
		return;
}


void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {

	//VkCommandBufferBeginInfo beginInfo{};
	//beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//
	//if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
	//	throw std::runtime_error("failed to begin recording command buffer!");
	//}

	//VkRenderPassBeginInfo renderPassInfo{};
	//renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//renderPassInfo.renderPass = renderPass;
	//renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
	//renderPassInfo.renderArea.offset = {0, 0};
	//renderPassInfo.renderArea.extent = swapChainExtent;
	//
	//VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	//renderPassInfo.clearValueCount = 1;
	//renderPassInfo.pClearValues = &clearColor;
	//
	//vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	//vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

	//VkViewport viewport{};
	//viewport.x = 0.0f;
	//viewport.y = 0.0f;
	//viewport.width = static_cast<float>(swapChainExtent.width);
	//viewport.height = static_cast<float>(swapChainExtent.height);
	//viewport.minDepth = 0.0f;
	//viewport.maxDepth = 1.0f;
	//vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	//VkRect2D scissor{};
	//scissor.offset = {0, 0};
	//scissor.extent = swapChainExtent;
	//vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	//vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	//vkCmdEndRenderPass(commandBuffer);

	//if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
	//	throw std::runtime_error("failed to record command buffer!");
	//}
}

/*
    void drawFrame() {
        vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(device, 1, &inFlightFence);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(commandBuffer, *//*VkCommandBufferResetFlagBits*//* 0);
        recordCommandBuffer(commandBuffer, imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(presentQueue, &presentInfo);
    }
	*/
