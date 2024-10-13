/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_VULKAN_COMMAND_BUFFER___
#define ___RENDERX_VULKAN_COMMAND_BUFFER___

#include "renderx/vulkan/swapchain.hpp"
#include "renderx/vulkan/render_pass.hpp"
#include "renderx/vulkan/buffer.hpp"
#include "renderx/vulkan/pipeline.hpp"

#include "renderx/vulkan/index_buffer.hpp"
#include "renderx/vulkan/vertex_buffer.hpp"

#include "renderx/vulkan/commands.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- C O M M A N D  B U F F E R ------------------------------------------

	template <typename ___type>
	class __attribute__((packed)) command_buffer final {


		// -- assertions ------------------------------------------------------

		/* check for valid level type */
		static_assert(vulkan::is_level<___type>,
				"command_buffer: invalid level type");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::command_buffer<___type>;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::command_buffer _cbuffer;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			command_buffer(void) = delete;

			/* deleted copy constructor */
			command_buffer(const ___self&) = delete;

			/* deleted move constructor */
			command_buffer(___self&&) = delete;

			/* deleted destructor */
			~command_buffer(void) = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


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

				// try to reset command buffer
				vk::try_execute<"failed to reset command buffer">(
					::vk_reset_command_buffer,
					_cbuffer, 0U);
			}

			/* execute secondary commands */
			auto execute_secondary_commands(const vulkan::commands<vulkan::secondary>& cmds)
				const noexcept -> void requires (std::same_as<___type, vulkan::primary>) {

				/* If any element of pCommandBuffers was not recorded with the VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT flag,
				   and it was recorded into any other primary command buffer which is currently in the executable or recording state,
				   that primary command buffer becomes invalid.
				   */

				// execute secondary command buffers
				::vk_cmd_execute_commands(
						// command buffer
						_cbuffer,
						// command buffer count
						cmds.size(),
						// command buffers
						cmds.data());
			}


			/* begin */
			auto begin(void) const -> void {

				// create info
				const vk::command_buffer_begin_info info {
					// type of structure
					.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
					// pointer to next structure
					.pNext            = nullptr,
					// flags
					.flags            = 0U,
					// pointer to inheritance info for secondary command buffers
					.pInheritanceInfo = nullptr
				};

				/* flags:
				 * VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT 
				 le command buffer sera ré-enregistré après son utilisation, donc invalidé une fois son exécution terminée
				 * VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
				 ce command buffer secondaire sera intégralement exécuté dans une unique render pass
				 * VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
				 le command buffer peut être ré-envoyé à la queue alors qu'il y est déjà et/ou est en cours d'exécution
				 */


				// actually not used !
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

				// try to begin command buffer
				vk::try_execute<"failed to begin command buffer">(
						::vk_begin_command_buffer,
						_cbuffer, &info);
			}

			/* end */
			auto end(void) const -> void {

				// stop recording state, start executable state
				vk::try_execute<"failed to end command buffer">(
						::vk_end_command_buffer,
						_cbuffer);
			}

			/* begin render pass */
			auto begin_render_pass(const vulkan::swapchain& swapchain,
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
					.renderPass      = render_pass.underlying(),
					// framebuffer from swapchain
					.framebuffer     = framebuffer,
					// render area
					.renderArea      = area,
					// clear value count
					.clearValueCount = 1U,
					// clear values
					.pClearValues    = &clear
				};

				// begin render pass
				::vk_cmd_begin_render_pass(
						// command buffer
						_cbuffer,
						// render pass begin info
						&info,
						// subpass contents
						VK_SUBPASS_CONTENTS_INLINE);
			}

			/* end render pass */
			auto end_render_pass(void) const noexcept -> void {

				// terminate render pass
				::vk_cmd_end_render_pass(_cbuffer);
			}

			/* set viewport */
			auto set_viewport(const vulkan::swapchain& swapchain) const noexcept -> void {

				// create viewport
				const vk::viewport viewport {
					.x        = 0.0f,
					.y        = 0.0f,
					.width    = static_cast<float>(swapchain.extent().width),
					.height   = static_cast<float>(swapchain.extent().height),
					.minDepth = 0.0f,
					.maxDepth = 1.0f
				};

				// set viewport
				::vk_cmd_set_viewport(
						// command buffer
						_cbuffer,
						// first viewport
						0U,
						// viewport count
						1U,
						// viewports
						&viewport);
			}

			/* set scissor */
			auto set_scissor(const vulkan::swapchain& swapchain) const noexcept -> void {

				const vk::rect2D scissor {
					// offset
					vk::offset2D{0, 0},
					// extent
					swapchain.extent()
				};

				// set scissor
				::vk_cmd_set_scissor(
						// command buffer
						_cbuffer,
						// first scissor
						0U,
						// scissor count
						1U,
						// scissors
						&scissor);
			}



			/* bind vertex buffers */
			template <vk::u32 ___size>
			auto bind_vertex_buffers(const vk::buffer (&___buffs)[___size]) const noexcept -> void {

				// offsets
				const vk::device_size ___ofs[___size]{}; // zero offsets

				// bind vertex buffers
				::vk_cmd_bind_vertex_buffers(
						// command buffer
						_cbuffer,
						// first binding
						0U,
						// binding count
						___size,
						// buffers
						___buffs,
						// offsets
						___ofs);
			}

			/* bind vertex buffer */
			auto bind_vertex_buffer(const vulkan::vertex_buffer& buffer) const noexcept -> void {

				// offsets
				const vk::device_size ___ofs{0U};

				// bind vertex buffers
				::vk_cmd_bind_vertex_buffers(
						// command buffer
						_cbuffer,
						// first binding
						0U,
						// binding count
						1U,
						// buffers
						&(buffer.underlying()),
						// offsets
						&___ofs);
			}

			/* bind index buffer */
			auto bind_index_buffer(const vulkan::index_buffer& ibuffer) const noexcept -> void {

				// bind index buffer
				::vk_cmd_bind_index_buffer(
						// command buffer
						_cbuffer,
						// buffer
						ibuffer.underlying(),
						// offset
						0U,
						// index type
						ibuffer.type());
			}


			/* draw */
			auto cmd_draw(const vk::u32 vertex_count) const noexcept -> void {

				// draw
				::vk_cmd_draw(
						// command buffer
						_cbuffer,
						// vertex count
						vertex_count,
						// instance count
						1U,
						// first vertex
						0U,
						// first instance
						0U
				);
			}

			/* draw indexed */
			auto draw_indexed(const vk::u32 index_count) const noexcept -> void {

				// draw indexed
				::vk_cmd_draw_indexed(
						// command buffer
						_cbuffer,
						// index count
						index_count,
						// instance count
						1U,
						// first index
						0U,
						// vertex offset
						0U,
						// first instance
						0U
				);
			}

			/* bind pipeline */
			auto bind_pipeline(const vk::pipeline& pipeline,
										const vk::pipeline_bind_point& point
										= VK_PIPELINE_BIND_POINT_GRAPHICS) const noexcept -> void {
				::vk_cmd_bind_pipeline(_cbuffer, point, pipeline);
			}

			/* push constants */
			template <typename ___constants>
			auto push_constants(const vulkan::pipeline& pipeline,
					            const ___constants& constants) const noexcept -> void {

				// push constants
				::vk_cmd_push_constants(
						// command buffer
						_cbuffer,
						// pipeline layout
						pipeline.layout(),
						// stage flags
						VK_SHADER_STAGE_VERTEX_BIT,
						// offset
						0U,
						// size
						sizeof(___constants),
						// data
						&constants);
			}



			/* record */
			template <typename ___pconst, typename ___t>
			auto record(const vulkan::swapchain& swapchain,
						const vulkan::render_pass& render_pass,
						const vk::framebuffer& framebuffer,
						const vulkan::pipeline& pipeline,
						const vulkan::vertex_buffer& vbuffer,
						const vulkan::index_buffer& ibuffer,
						const ___pconst& constants) const -> void {

				// begin recording
				___self::begin();

				// begin render pass
				___self::begin_render_pass(swapchain, render_pass, framebuffer);

				// set viewport
				___self::set_viewport(swapchain);

				// set scissor
				___self::set_scissor(swapchain);


				// for earch mesh
				{

					// bind graphics pipeline
					___self::bind_pipeline(pipeline);


					// bind vertex buffer
					___self::bind_vertex_buffer(vbuffer);

					// bind index buffer
					___self::bind_index_buffer(ibuffer);

					// push constants
					___self::push_constants(pipeline, constants);

					// indexed draw
					___self::draw_indexed(ibuffer.count());

					// draw
					//___self::cmd_draw(vbuffer.count());

				}

				// end render pass
				___self::end_render_pass();

				// end recording
				___self::end();
			}


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::command_buffer& {
				return _cbuffer;
			}

	}; // class command_buffer


} // namespace vulkan

#endif // ___RENDERX_VULKAN_COMMAND_BUFFER___
