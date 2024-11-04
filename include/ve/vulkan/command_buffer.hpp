#ifndef ___ve_vulkan_command_buffer___
#define ___ve_vulkan_command_buffer___

#include "ve/vk/array.hpp"
#include "ve/vulkan/swapchain.hpp"
#include "ve/vulkan/render_pass.hpp"
#include "ve/vulkan/buffer.hpp"
#include "ve/vulkan/pipeline/pipeline.hpp"

#include "ve/vulkan/index_buffer.hpp"
#include "ve/vulkan/vertex_buffer.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- C O M M A N D  B U F F E R ------------------------------------------

	class command_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::command_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::command_buffer _buffer;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			command_buffer(void) noexcept = default;

			/* buffer constructor */
			command_buffer(const vk::command_buffer& buffer) noexcept
			: _buffer{buffer} {
			}

			/* deleted copy constructor */
			command_buffer(const ___self&) = delete;

			/* move constructor */
			command_buffer(___self&&) noexcept = default;

			/* destructor */
			~command_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


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
					_buffer, 0U);
			}

			/* execute secondary commands */
			//auto execute_secondary_commands(const vulkan::commands& cmds)
			//	const noexcept -> void {
			//
			//	/* If any element of pCommandBuffers was not recorded with the VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT flag,
			//	   and it was recorded into any other primary command buffer which is currently in the executable or recording state,
			//	   that primary command buffer becomes invalid.
			//	   */
			//
			//	// execute secondary command buffers
			//	::vk_cmd_execute_commands(
			//			// command buffer
			//			_buffer,
			//			// command buffer count
			//			cmds.size(),
			//			// command buffers
			//			cmds.data());
			//}


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
						_buffer, &info);
			}

			/* end */
			auto end(void) const -> void {

				// stop recording state, start executable state
				vk::try_execute<"failed to end command buffer">(
						::vk_end_command_buffer,
						_buffer);
			}

			/* begin render pass */
			auto begin_render_pass(const vk::extent2D& extent,
								   const ::vk_render_pass& render_pass,
								   const vk::framebuffer& framebuffer) const noexcept -> void {

				// clear color
				const vk::array clears {
					// color
					vk::clear_value{
						.color = vk::clear_color_value{
							.float32 = {0.02f, 0.02f, 0.03f, 1.0f}
						}
					},
					// depth
					vk::clear_value{
						.depthStencil = {
							.depth   = 1.0f,
							.stencil = 0U
						}
					}
				};

				// area
				const ::vk_rect2D area{
					.offset = vk::offset2D{0, 0},
					.extent = extent
				};

				const ::vk_render_pass_begin_info info {
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
					.clearValueCount = clears.size(),
					// clear values
					.pClearValues    = clears.data()
				};

				// begin render pass
				::vk_cmd_begin_render_pass(
						// command buffer
						_buffer,
						// render pass begin info
						&info,
						// subpass contents
						VK_SUBPASS_CONTENTS_INLINE);
			}

			/* end render pass */
			auto end_render_pass(void) const noexcept -> void {

				// terminate render pass
				::vk_cmd_end_render_pass(_buffer);
			}

			/* set viewport */
			auto set_viewport(const vk::extent2D&) const noexcept -> void;

			/* set scissor */
			auto set_scissor(const vk::extent2D&) const noexcept -> void;

			/* set viewport and scissor */
			auto set_viewport_and_scissor(const vk::extent2D&) const noexcept -> void;



			/* bind vertex buffers */
			template <vk::u32 ___size>
			auto bind_vertex_buffers(const vk::buffer (&___buffs)[___size]) const noexcept -> void {

				// offsets
				const vk::device_size ___ofs[___size]{}; // zero offsets

				// bind vertex buffers
				::vk_cmd_bind_vertex_buffers(
						// command buffer
						_buffer,
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
						_buffer,
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
						_buffer,
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
						_buffer,
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
						_buffer,
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

			/* bind graphics pipeline */
			auto bind_graphics_pipeline(const ::vk_pipeline&) const noexcept -> void;

			/* bind compute pipeline */
			auto bind_compute_pipeline(const ::vk_pipeline&) const noexcept -> void;

			/* dispatch */
			auto dispatch(const vk::u32, const vk::u32, const vk::u32) const noexcept -> void;

			/* pipeline barrier */
			auto pipeline_barrier(const vk::pipeline_stage_flags& src_stage,
								  const vk::pipeline_stage_flags& dst_stage,
								  const vk::dependency_flags& dependency,
								  const vk::u32& memory_barrier_count,
								  const vk::memory_barrier* memory_barriers,
								  const vk::u32& buffer_memory_barrier_count,
								  const vk::buffer_memory_barrier* buffer_memory_barriers,
								  const vk::u32& image_memory_barrier_count,
								  const vk::image_memory_barrier* image_memory_barriers) const noexcept -> void {

				// pipeline barrier
				::vk_cmd_pipeline_barrier(
						// command buffer
						_buffer,
						// source stage
						src_stage,
						// destination stage
						dst_stage,
						// dependency flags
						dependency,
						// memory barrier count
						memory_barrier_count,
						// memory barriers
						memory_barriers,
						// buffer memory barrier count
						buffer_memory_barrier_count,
						// buffer memory barriers
						buffer_memory_barriers,
						// image memory barrier count
						image_memory_barrier_count,
						// image memory barriers
						image_memory_barriers);
			}


			/* push constants */
			template <typename ___constants>
			auto push_constants(const ::vk_pipeline_layout& layout,
					            const ___constants& constants) const noexcept -> void {

				//static_assert(sizeof(___constants) <= 128U,
				//		"command_buffer: push constants size must be less than or equal to 128 bytes");

				// push constants
				::vk_cmd_push_constants(
						// command buffer
						_buffer,
						// pipeline layout
						layout,
						// stage flags
						//VK_SHADER_STAGE_VERTEX_BIT
						//|
						VK_SHADER_STAGE_FRAGMENT_BIT
						//| VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT
						//| VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT
						,
						// offset
						0U,
						// size
						sizeof(___constants),
						// data
						&constants);
			}

			/* bind descriptor sets */
			auto bind_descriptor_sets(const ::vk_pipeline_layout& layout,
									  const ::vk_descriptor_set& set) const noexcept -> void {

				// bind descriptor sets
				::vk_cmd_bind_descriptor_sets(
						// command buffer
						_buffer,
						// bind point
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						// pipeline layout
						layout,
						// first set
						0U,
						// descriptor set count
						1U,
						// descriptor sets
						&set,
						// dynamic offset count
						0U,
						// dynamic offsets
						nullptr);
			}

			auto bind_descriptor_sets(const ::vk_pipeline_layout& layout,
									  const ::vk_descriptor_set& set,
									  const vk::u32& dynamic_offsets) const noexcept -> void {

				// bind descriptor sets
				::vk_cmd_bind_descriptor_sets(
						// command buffer
						_buffer,
						// bind point
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						// pipeline layout
						layout,
						// first set
						0U,
						// descriptor set count
						1U,
						// descriptor sets
						&set,
						// dynamic offset count
						1U,
						// dynamic offsets
						&dynamic_offsets);
			}

			auto bind_descriptor_sets(const ::vk_pipeline_layout& layout,
									// first set
									const vk::u32& first_set,
									// descriptor set count
									const vk::u32& set_count,
									// descriptor sets
									const ::vk_descriptor_set* sets,
									// dynamic offset count
									const vk::u32& dynamic_offset_count,
									const vk::u32* dynamic_offsets) const noexcept -> void {

				// bind descriptor sets
				::vk_cmd_bind_descriptor_sets(
						// command buffer
						_buffer,
						// bind point
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						// pipeline layout
						layout,
						// first set
						first_set,
						// descriptor set count
						set_count,
						// descriptor sets
						sets,
						// dynamic offset count
						dynamic_offset_count,
						// dynamic offsets
						dynamic_offsets);
			}

			auto bind_compute_descriptor_sets(const ::vk_pipeline_layout& layout,
											  // first set
											  const vk::u32& first_set,
											  // descriptor set count
											  const vk::u32& set_count,
											  // descriptor sets
											  const ::vk_descriptor_set* sets,
											  // dynamic offset count
											  const vk::u32& dynamic_offset_count = 0U,
											  // dynamic offsets
											  const vk::u32* dynamic_offsets = nullptr
											  ) const noexcept -> void {

				// bind descriptor sets
				::vk_cmd_bind_descriptor_sets(
						// command buffer
						_buffer,
						// bind point
						VK_PIPELINE_BIND_POINT_COMPUTE,
						// pipeline layout
						layout,
						// first set
						first_set,
						// descriptor set count
						set_count,
						// descriptor sets
						sets,
						// dynamic offset count
						dynamic_offset_count,
						// dynamic offsets
						dynamic_offsets);
			}


			/*
			void vkCmdResolveImage(
					VkCommandBuffer                             commandBuffer,
					VkImage                                     srcImage,
					VkImageLayout                               srcImageLayout,
					VkImage                                     dstImage,
					VkImageLayout                               dstImageLayout,
					uint32_t                                    regionCount,
					const VkImageResolve*                       pRegions);
					*/


			/* resolve image */
			auto resolve_image(const vk::image& src,
							   const vk::image& dst,
							   const vk::extent3D& extent) const noexcept -> void {

				// region
				const vk::image_resolve region {
					// src subresource
					.srcSubresource = vk::image_subresource_layers{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.mipLevel       = 0U,
						.baseArrayLayer = 0U,
						.layerCount     = 1U
					},
					// src offset
					.srcOffset = vk::offset3D{0, 0, 0},
					// dst subresource
					.dstSubresource = vk::image_subresource_layers{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.mipLevel       = 0U,
						.baseArrayLayer = 0U,
						.layerCount     = 1U
					},
					// dst offset
					.dstOffset = vk::offset3D{0, 0, 0},
					// extent
					.extent = extent
				};

				// resolve image
				::vk_cmd_resolve_image(
						// command buffer
						_buffer,
						// src image
						src,
						// src image layout
						VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
						// dst image
						dst,
						// dst image layout
						VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						// region count
						1U,
						// regions
						&region);
			}


			// -- public conversion operators ---------------------------------

			/* const vk::command_buffer& conversion operator */
			operator const vk::command_buffer&(void) const noexcept;

	}; // class command_buffer

} // namespace vulkan

#endif // ___ve_vulkan_command_buffer___
