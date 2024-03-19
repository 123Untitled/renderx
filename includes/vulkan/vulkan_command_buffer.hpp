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

#ifndef ENGINE_VULKAN_COMMANDBUFFER_HPP
#define ENGINE_VULKAN_COMMANDBUFFER_HPP


// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"
#include "vulkan_command_pool.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_render_pass.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- C O M M A N D  B U F F E R -------------------------------------------

	class command_buffer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_buffer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_buffer(void) noexcept = default;

			/* logical device and command pool constructor */
			command_buffer(const vk::shared<vk::command_pool>&,
						   const vk::u32 size = 1);

			/* copy constructor */
			command_buffer(const self&) noexcept = default;

			/* move constructor */
			command_buffer(self&&) noexcept = default;

			/* destructor */
			~command_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> vk::u32;


			// -- public methods ----------------------------------------------

			/* begin */
			auto begin(void) const -> void;

			/* renderpass begin */
			auto renderpass_begin(const vulkan::swapchain&,
								  const vulkan::render_pass&) const noexcept -> void;



			// -- bind pipeline -----------------------------------------------

			/* bind pipeline */
			template <xns::basic_string_literal bp>
			auto bind_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				// graphics pipeline
				if      constexpr (bp == "graphics")
					vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);
				// compute pipeline
				else if constexpr (bp == "compute")
					vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_COMPUTE);
				// amdx pipeline
				#ifdef VK_ENABLE_BETA_EXTENSIONS
				else if constexpr (bp == "amdx")
					vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
				#endif
				// ray tracing pipeline
				else if constexpr (bp == "ray")
					vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
				// subpass shading pipeline
				else if constexpr (bp == "huawei")
					vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
			}



			/* bind vertex buffers */
			// bind vertex buffers (not implemented)

			/* draw */
			auto draw(const vk::u32,
					  const vk::u32,
					  const vk::u32,
					  const vk::u32) const noexcept -> void;

			/* renderpass end */
			auto renderpass_end(void) const noexcept -> void;

			/* end */
			auto end(void) const -> void;



		private:

			// -- friends -----------------------------------------------------

			/* command_pool::new_command_buffer as friend */
			//friend auto vulkan::command_pool::new_command_buffer(const vulkan::logical_device&) const -> vulkan::command_buffer;
			friend auto vulkan::command_pool::new_secondary_command_buffer(const vk::u32 size) -> vulkan::command_buffer;
			friend auto vulkan::command_pool::new_primary_command_buffer(const vk::u32 size) -> vulkan::command_buffer;

			/* command_pool::new_buffers as friend */
			//friend auto vulkan::command_pool::new_buffers(const vulkan::logical_device&, const ::uint32_t) const -> xns::vector<vulkan::command_buffer>;

			/* vector<vulkan::command_buffer> as friend */
			//friend typename vk::vector<self>::allocator;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::shared<vk::command_buffer> _buffer;


			vk::u32 _size;

	}; // class command_buffer

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMANDBUFFER_HPP
