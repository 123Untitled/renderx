#ifndef ___ve_vulkan_pipeline___
#define ___ve_vulkan_pipeline___

#include "ve/vk/unique.hpp"
#include "ve/vk/array.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- P I P E L I N E -----------------------------------------------------

	class pipeline final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::pipeline;


			// -- private members ---------------------------------------------

			/* pipeline */
			vk::unique<::vk_pipeline> _pipeline;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline(void) noexcept = default;

			/* graphics pipeline constructor */
			pipeline(const ::vk_graphics_pipeline_create_info&);

			/* graphics pipeline constructor (parameters) */
			template <unsigned N>
			pipeline(const vk::array<::vk_pipeline_shader_stage_create_info, N>& stages,
					 const ::vk_pipeline_vertex_input_state_create_info& vertex_input,
					 const ::vk_pipeline_input_assembly_state_create_info& input_assembly,
					 const ::vk_pipeline_tesselation_state_create_info& tesselation,
					 const ::vk_pipeline_viewport_state_create_info& viewport,
					 const ::vk_pipeline_rasterization_state_create_info& rasterization,
					 const ::vk_pipeline_multisample_state_create_info& multisample,
					 const ::vk_pipeline_depth_stencil_state_create_info& depth_stencil,
					 const ::vk_pipeline_color_blend_state_create_info& color_blend,
					 const ::vk_pipeline_dynamic_state_create_info& dynamic,
					 const ::vk_pipeline_layout& layout,
					 const ::vk_render_pass& render_pass)
			: pipeline{
				::vk_graphics_pipeline_create_info{
					// structure type
					.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
					// next structure
					.pNext               = nullptr,
					// flags
					.flags               = 0U,
					// shader stage count
					.stageCount          = stages.size(),
					// shader stages
					.pStages             = stages.data(),
					// vertex input state
					.pVertexInputState   = &vertex_input,
					// input assembly state
					.pInputAssemblyState = &input_assembly,
					// tesselation state
					.pTessellationState  = &tesselation,
					// viewport state
					.pViewportState      = &viewport,
					// rasterization state
					.pRasterizationState = &rasterization,
					// multisample state
					.pMultisampleState   = &multisample,
					// depth stencil state
					.pDepthStencilState  = &depth_stencil,
					// color blend state
					.pColorBlendState    = &color_blend,
					// dynamic state
					.pDynamicState       = &dynamic,
					// pipeline layout
					.layout              = layout,
					// render pass
					.renderPass          = render_pass,
					// subpass
					.subpass             = 0U,
					// base pipeline handle
					.basePipelineHandle  = nullptr,
					// base pipeline index
					.basePipelineIndex   = -1}} {
			}




			/* compute pipeline constructor */
			pipeline(const ::vk_pipeline_shader_stage_create_info&,
					 const ::vk_pipeline_layout&);

			/* deleted copy constructor */
			pipeline(const self&) = delete;

			/* move constructor */
			pipeline(self&&) noexcept = default;

			/* destructor */
			~pipeline(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const vk_pipeline&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create compute pipeline */
			static auto _create_compute_pipeline(
					const ::vk_pipeline_shader_stage_create_info&,
					const ::vk_pipeline_layout&) -> vk::unique<::vk_pipeline>;


		public:

			// -- forward declarations ----------------------------------------

			/* library */
			class library;

			/* layout */
			class layout;

			/* vertex input state */
			class vertex_input_state;

			/* input assembly state */
			class input_assembly_state;

			/* tesselation state */
			class tesselation_state;

			/* viewport state */
			class viewport_state;

			/* rasterization state */
			class rasterization_state;

			/* multisample state */
			class multisample_state;

			/* depth stencil state */
			class depth_stencil_state;

			/* color blend state */
			class color_blend_state;

			/* dynamic state */
			template <unsigned>
			class dynamic_state;


			// -- deduction guides --------------------------------------------

			/* deduction guide */
			template <typename... Ts>
			dynamic_state(const Ts&...) -> dynamic_state<sizeof...(Ts)>;


			class builder;


	}; // class pipeline

} // namespace vk

#endif // ___ve_vulkan_pipeline___
