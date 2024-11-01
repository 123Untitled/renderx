#ifndef ___ve_vulkan_ssbo_buffer___
#define ___ve_vulkan_ssbo_buffer___

#include "ve/vulkan/buffer.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S S B O  B U F F E R ------------------------------------------------

	class ssbo_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::ssbo_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			ssbo_buffer(void) noexcept = default;

			/* size constructor */
			ssbo_buffer(const vk::device_size& size)
			: _buffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT) {
			}


			/*
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
			| VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
			| VK_BUFFER_USAGE_TRANSFER_DST_BIT
			*/


	}; // class ssbo_buffer

} // namespace ve

#endif // ___ve_vulkan_ssbo_buffer___
