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

#ifndef ENGINE_VULKAN_COMMAND_BUFFER_HEADER
#define ENGINE_VULKAN_COMMAND_BUFFER_HEADER


// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_device.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_render_pass.hpp"


//namespace vulkan {
//
//	// -- forward declarations ------------------------------------------------
//
//	/* commands */
//	template <typename T>
//	class commands;
//
//}


#include "vulkan/commands.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {



	// -- C O M M A N D  B U F F E R -------------------------------------------

	template <typename T>
	class command_buffer final {


		// -- assertions ------------------------------------------------------

		/* check if T is a valid level type */
		static_assert(vulkan::is_level<T>, "command_buffer: invalid level type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_buffer<T>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			command_buffer(void) = delete;

			/* deleted copy constructor */
			command_buffer(const self&) = delete;

			/* deleted move constructor */
			command_buffer(self&&) = delete;

			/* deleted destructor */
			~command_buffer(void) = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------


			/* reset */
			auto reset(void) const noexcept -> void {

				/* flag:
				 *   VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT
				 *   not good idea because buffer is managed by 'commands' class
				 *   memory resources returned to the parent command pool
				 *   else keep memory resources and reuse them when recording commands
				 *   commandBuffer is moved to the initial state.
				 */

				vk::reset_command_buffer(_buffer, 0U);
			}

			/* cmd execute commands */
			auto cmd_execute_commands(const vulkan::commands<vulkan::secondary>& cmds) const noexcept -> void {

				/* If any element of pCommandBuffers was not recorded with the VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT flag,
				   and it was recorded into any other primary command buffer which is currently in the executable or recording state,
				   that primary command buffer becomes invalid.
				   */

				// execute secondary command buffers
				::vkCmdExecuteCommands(_buffer, cmds.size(), cmds.data());
			}


			/* begin */
			auto begin(void) const -> void {

				// start recording state


				vk::command_buffer_begin_info info {
					// type of structure
					.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
					// pointer to next structure
					.pNext            = nullptr,
					// flags
					.flags            = 0U,
					// pointer to inheritance info for secondary command buffers
					.pInheritanceInfo = nullptr
				};

				vk::command_buffer_inheritance_info inheritance {
					// type of structure
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO,
					// pointer to next structure
					.pNext              = nullptr,
					// render pass
					.renderPass         = nullptr,
					// subpass
					.subpass            = 0,
					// framebuffer
					.framebuffer        = nullptr,
					// occlusion query enable
					.occlusionQueryEnable = VK_FALSE,
					// query flags
					.queryFlags         = 0, /* VK_QUERY_CONTROL_PRECISE_BIT */
					// pipeline statistics
					.pipelineStatistics = 0U
				};

				/* flags:
				 * VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT 
				 le command buffer sera ré-enregistré après son utilisation, donc invalidé une fois son exécution terminée
				 * VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
				 ce command buffer secondaire sera intégralement exécuté dans une unique render pass
				 * VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
				 le command buffer peut être ré-envoyé à la queue alors qu'il y est déjà et/ou est en cours d'exécution
				 */

				// begin command buffer
				vk::begin_command_buffer(_buffer, info);

			}

			/* end */
			auto end(void) const -> void {

				// stop recording state, start executable state

				vk::end_command_buffer(_buffer);
			}

			/* renderpass begin */
			auto renderpass_begin(const vulkan::swapchain& swapchain,
								  const vulkan::render_pass& render_pass,
								  const vk::framebuffer& framebuffer) const noexcept -> void {

				// clear color
				const vk::clear_value clear{
					.color = vk::clear_color_value{
						.float32 = {0.2f, 0.2f, 0.2f, 1.0f}
					}
				};

				// area
				const vk::rect2D area{
					.offset = vk::offset2D{0, 0},
					.extent = swapchain.extent()
				};

				const vk::render_pass_begin_info info {
					// type of structure
					.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
					// pointer to next structure
					.pNext           = nullptr,
					// renderpass
					.renderPass      = render_pass,
					// framebuffer from swapchain
					.framebuffer     = framebuffer,
					// render area
					.renderArea      = area,
					// clear value count
					.clearValueCount = 1,
					// clear values
					.pClearValues    = &clear
				};

				// begin render pass
				vk::cmd_begin_render_pass(_buffer, info, VK_SUBPASS_CONTENTS_INLINE);

			}

			/* renderpass end */
			auto renderpass_end(void) const noexcept -> void {
				vk::cmd_end_render_pass(_buffer);
			}

			/* cmd set viewport */
			auto cmd_set_viewport(const vulkan::swapchain& swapchain) const noexcept -> void {

				vk::viewport viewport {
					.x        = 0.0f,
					.y        = 0.0f,
					.width    = static_cast<float>(swapchain.extent().width),
					.height   = static_cast<float>(swapchain.extent().height),
					.minDepth = 0.0f,
					.maxDepth = 1.0f
				};

				::vkCmdSetViewport(_buffer,
								   0, // first viewport
								   1, // viewport count
								   &viewport // viewports
				);

			}



			/* bind vertex buffers */
			// bind vertex buffers (not implemented)

			/* draw */
			auto cmd_draw(const vk::u32 vertex_count,
					  const vk::u32 instance_count,
					  const vk::u32 first_vertex,
					  const vk::u32 first_instance) const noexcept -> void {
				::vkCmdDraw(_buffer, vertex_count, instance_count, first_vertex, first_instance);
			}



			/* bind graphics pipeline */
			auto bind_graphics_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);
			}

			/* bind compute pipeline */
			auto bind_compute_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_COMPUTE);
			}

			/* bind amdx pipeline */
			#ifdef VK_ENABLE_BETA_EXTENSIONS
			auto bind_amdx_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX);
			}
			#endif

			/* bind ray tracing pipeline */
			auto bind_ray_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
			}

			/* bind subpass shading pipeline */
			auto bind_subpass_shading_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
			}

			/* bind ray tracing nv pipeline */
			auto bind_ray_nv_pipeline(const vk::pipeline& pipeline) const noexcept -> void {
				vk::cmd_bind_pipeline(_buffer, pipeline, VK_PIPELINE_BIND_POINT_RAY_TRACING_NV);
			}



		private:

			// -- private members ---------------------------------------------

			/* buffer */
			vk::command_buffer _buffer;

	}; // class command_buffer


	// -- assertions ----------------------------------------------------------

	/* sizeof assertion */
	static_assert(sizeof(vk::command_buffer) == sizeof(vulkan::command_buffer<vulkan::primary>),
				  "command_buffer: size mismatch");

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMAND_BUFFER_HEADER
