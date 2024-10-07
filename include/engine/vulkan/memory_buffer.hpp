#ifndef ___RENDERX_VULKAN_MEMORY_BUFFER___
#define ___RENDERX_VULKAN_MEMORY_BUFFER___

#include "engine/vulkan/buffer.hpp"
#include "engine/vulkan/device_memory.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- M E M O R Y  B U F F E R --------------------------------------------

	class memory_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::memory_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;

			/* device memory */
			vulkan::device_memory _memory;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			memory_buffer(void) noexcept = default;

			/* deleted copy constructor */
			memory_buffer(const ___self&) = delete;

			/* move constructor */
			memory_buffer(___self&&) noexcept = default;

			/* destructor */
			~memory_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* buffer */
			auto buffer(void) noexcept -> vulkan::buffer&;

			/* device memory */
			auto memory(void) noexcept -> vulkan::device_memory&;


			// -- public methods ----------------------------------------------

			/* bind */
			auto bind(const vk::device_size& ___offset = 0U) const -> void  {
				_memory.bind(_buffer.underlying(), ___offset);
			}


	}; // class memory_buffer

} // namespace vulkan


#endif // ___RENDERX_VULKAN_MEMORY_BUFFER___
