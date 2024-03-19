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

#ifndef ENGINE_VULKAN_PIPELINE_HEADER
#define ENGINE_VULKAN_PIPELINE_HEADER

#include "vulkan/vk_typedefs.hpp"
#include "vulkan/vk_shared.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P I P E L I N E -----------------------------------------------------

	class pipeline final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::pipeline;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline(void) noexcept = default;

			/* infos constructor */
			template <decltype(sizeof(0)) S>
			pipeline(const vk::shared<vk::device>&,
					 const vk::pipeline_shader_stage_info(&)[S],
					 const vk::pipeline_vertex_input_state_info&,
					 const vk::pipeline_input_assembly_state_info&,
					 const vk::pipeline_tesselation_state_info&,
					 const vk::pipeline_viewport_state_info&,
					 const vk::pipeline_rasterization_state_info&,
					 const vk::pipeline_multisample_state_info&,
					 const vk::pipeline_depth_stencil_state_info&,
					 const vk::pipeline_color_blend_state_info&,
					 const vk::pipeline_dynamic_state_info&,
					 const vk::pipeline_layout&,
					 const vk::render_pass&);

			/* copy constructor */
			pipeline(const self&) noexcept = default;

			/* move constructor */
			pipeline(self&&) noexcept = default;

			/* destructor */
			~pipeline(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


		private:

			// -- private members ---------------------------------------------

			/* pipeline */
			vk::shared<vk::pipeline> _pipeline;

	}; // class pipeline

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_HEADER
