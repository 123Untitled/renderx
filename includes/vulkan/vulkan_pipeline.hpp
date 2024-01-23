#ifndef ENGINE_VULKAN_PIPELINE_HPP
#define ENGINE_VULKAN_PIPELINE_HPP

#include "vk_typedefs.hpp"
#include "vulkan_resource.hpp"


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



		private:

			// -- private members ---------------------------------------------

			/* pipeline */
			vk::managed<vk::pipeline,
						vk::shared<vk::device>> _pipeline;



	}; // class pipeline

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_HPP
