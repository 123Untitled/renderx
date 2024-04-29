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

#ifndef ENGINE_VULKAN_VERTEX_BUFFER_HPP
#define ENGINE_VULKAN_VERTEX_BUFFER_HPP


#include <vulkan/vulkan.h>

#include "engine/vulkan/device.hpp"
#include "engine/vertex/basic_vertex.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- V E R T E X  B U F F E R --------------------------------------------

	class vertex_buffer final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::vertex_buffer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vertex_buffer(const vulkan::device&);

			/* deleted copy constructor */
			vertex_buffer(const self&) = delete;

			/* move constructor */
			vertex_buffer(self&&) noexcept;

			/* destructor */
			~vertex_buffer(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* render */
			auto render(const ::VkCommandBuffer&) const noexcept -> void;


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* vertex buffer */
			VkBuffer _buffer;

			/* vertex buffer memory */
			VkDeviceMemory _memory;

	}; // class vertex_buffer

} // namespace vulkan

#endif // ENGINE_VULKAN_VERTEX_BUFFER_HPP
