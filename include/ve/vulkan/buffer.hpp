#ifndef ___void_engine_vulkan_buffer___
#define ___void_engine_vulkan_buffer___

#include "ve/vk/unique.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- B U F F E R ---------------------------------------------------------

	class buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::unique<vk::buffer> _buffer;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			buffer(void) noexcept = default;

			/* parameters constructor */
			buffer(const vk::device_size&, const vk::buffer_usage_flags&);

			/* deleted copy constructor */
			buffer(const ___self&) = delete;

			/* move constructor */
			buffer(___self&&) noexcept = default;

			/* destructor */
			~buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::buffer&;

	}; // class buffer

} // namespace vulkan

#endif // ___void_engine_vulkan_buffer___
