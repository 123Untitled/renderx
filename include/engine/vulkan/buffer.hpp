/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ENGINE_VULKAN_BUFFER_HPP
#define ENGINE_VULKAN_BUFFER_HPP

#include "engine/vk/shared.hpp"
#include "engine/vertex/vertex.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- V E R T E X  B U F F E R --------------------------------------------

	class buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::shared<vk::buffer> _buffer;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			template <typename... ___params>
			buffer(const vk::shared<vk::device>& ___dv,
				   const vk::vector<engine::vertex<___params...>>& ___vtx)
			: _buffer{___dv,
				vk::buffer_info{
					// structure type
					VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
					// next structure
					nullptr,
					// flags
					0U,
					// size of buffer
					sizeof(engine::vertex<___params...>) * ___vtx.size(),
					// usage flags
					VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
					// sharing mode (exclusive or concurrent)
					VK_SHARING_MODE_EXCLUSIVE,
					// queue family index count
					0U, // not implemented yet...
						// queue family indices
					nullptr // not implemented yet...
				}} {
			}

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
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public methods ----------------------------------------------

			/* render */
			auto render(const vk::command_buffer&) const noexcept -> void;

	}; // class buffer

} // namespace vulkan

#endif // ENGINE_VULKAN_BUFFER_HPP
