#ifndef ENGINE_VULKAN_COMMANDBUFFER_HPP
#define ENGINE_VULKAN_COMMANDBUFFER_HPP


// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_logical_device.hpp"
#include "vulkan_command_pool.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- C O M M A N D  B U F F E R -------------------------------------------

	class command_buffer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::command_buffer;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			command_buffer(const self&) = delete;

			/* destructor */
			~command_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;


			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device&,
						 const vulkan::command_pool&) noexcept -> void;


			// -- public conversion operators ---------------------------------

			/* VkCommandBuffer conversion operator */
			operator ::VkCommandBuffer(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* begin */
			auto begin(void) const -> void;

			/* renderpass begin */
			auto renderpass_begin(void) const noexcept -> void;

			/* bind pipeline */
			auto bind_pipeline(const ::VkPipelineBindPoint,
							   const ::VkPipeline) const noexcept -> void;

			// bind vertex buffers (not implemented)

			/* draw */
			auto draw(const ::uint32_t,
					  const ::uint32_t,
					  const ::uint32_t,
					  const ::uint32_t) const noexcept -> void;

			/* renderpass end */
			auto renderpass_end(void) const noexcept -> void;

			/* end */
			auto end(void) const -> void;


		private:

			// -- friends -----------------------------------------------------

			/* command_pool::new_buffer as friend */
			friend auto vulkan::command_pool::new_buffer(const vulkan::logical_device&) const -> vulkan::command_buffer;

			/* command_pool::new_buffers as friend */
			friend auto vulkan::command_pool::new_buffers(const vulkan::logical_device&, const ::uint32_t) const -> xns::vector<vulkan::command_buffer>;

			/* vector<vulkan::command_buffer> as friend */
			friend typename xns::vector<vulkan::command_buffer>::allocator;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			command_buffer(void) noexcept;

			/* logical device and command pool constructor */
			command_buffer(const vulkan::logical_device&,
						   const vulkan::command_pool&);

			/* move constructor */
			command_buffer(self&&) noexcept;


			// -- private assignment operators --------------------------------

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- private static methods --------------------------------------

			/* create info */
			static auto create_info(const vulkan::command_pool&,
									const ::VkCommandBufferLevel,
									const ::uint32_t) noexcept -> ::VkCommandBufferAllocateInfo;

			/* create buffers */
			static auto create_buffers(const vulkan::logical_device&,
									   const vulkan::command_pool&,
									   const ::uint32_t) -> xns::vector<self>;


			// -- private members ---------------------------------------------

			/* buffer */
			::VkCommandBuffer _buffer;

	};

	/* assert command buffer size matches */
	static_assert(sizeof(::VkCommandBuffer) == sizeof(vulkan::command_buffer),
				"): COMMAND_BUFFER SIZE MISMATCH! :(");

} // namespace vulkan

#endif // ENGINE_VULKAN_COMMANDBUFFER_HPP
