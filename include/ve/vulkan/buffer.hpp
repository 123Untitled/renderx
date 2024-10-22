/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_BUFFER___
#define ___RENDERX_VULKAN_BUFFER___

#include "ve/vertex/vertex.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vk/utils.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- V E R T E X  B U F F E R --------------------------------------------

	class buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::buffer _buffer;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			buffer(void) noexcept;

			/* parameters constructor */
			buffer(const vk::device_size&, const vk::buffer_usage_flags&);

			/* deleted copy constructor */
			buffer(const ___self&) = delete;

			/* move constructor */
			buffer(___self&&) noexcept;

			/* destructor */
			~buffer(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::buffer&;

	}; // class buffer

} // namespace vulkan

#endif // ___RENDERX_VULKAN_BUFFER___
