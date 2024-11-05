#include "ve/vulkan/pipeline/library.hpp"

#include "ve/vulkan/pipeline/vertex_input_state.hpp"
#include "ve/vulkan/pipeline/input_assembly_state.hpp"
#include "ve/vulkan/pipeline/tesselation_state.hpp"
#include "ve/vulkan/pipeline/viewport_state.hpp"
#include "ve/vulkan/pipeline/rasterization_state.hpp"
#include "ve/vulkan/pipeline/multisample_state.hpp"
#include "ve/vulkan/pipeline/depth_stencil_state.hpp"
#include "ve/vulkan/pipeline/color_blend_state.hpp"
#include "ve/vulkan/pipeline/dynamic_state.hpp"

#include "ve/vulkan/shader_module.hpp"
#include "ve/vulkan/multisampling.hpp"
#include "ve/vulkan/render_pass.hpp"

#include "ve/vk/array.hpp"

#include "ve/vertex/vertex.hpp"

#include "ve/vulkan/pipeline/pipeline_layout_library.hpp"


// -- L I B R A R Y -----------------------------------------------------------

// -- file private functions --------------------------------------------------

/* planet */
static auto _planet(void) -> vk::pipeline {

	// planet modules
	vk::vert_module vem{"shaders/spir-v/planet.vert.spv"};
	vk::frag_module frm{"shaders/spir-v/planet.frag.spv"};
	vk::tesc_module tcm{"shaders/spir-v/planet.tesc.spv"};
	vk::tese_module tem{"shaders/spir-v/planet.tese.spv"};

	// shader stages
	const vk::array stages {
		vem.stage_info(),
		frm.stage_info(),
		tcm.stage_info(),
		tem.stage_info()
	};


	vk::pipeline::vertex_input_state vertex_input;

	vertex_input.binding(0U, sizeof(ve::vert3x), VK_VERTEX_INPUT_RATE_VERTEX)
				.description(0U, 0U, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ve::vert3x, position))
				.description(1U, 0U, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ve::vert3x, normal));



	// input assembly
	constexpr auto input_assembly = vk::pipeline::input_assembly_state{}
									.topology(VK_PRIMITIVE_TOPOLOGY_PATCH_LIST)
									.restart(VK_FALSE);

	// tesselation
	constexpr auto tesselation = vk::pipeline::tesselation_state{}
									.patch_control_points(3U);


	// viewport
	constexpr vk::pipeline::viewport_state
		viewport{};

	// rasterization
	constexpr auto rasterization = vk::pipeline::rasterization_state{}
									.polygon_mode(VK_POLYGON_MODE_FILL)
									.cull_mode(VK_CULL_MODE_BACK_BIT)
									.front_face(VK_FRONT_FACE_CLOCKWISE);

	// multisample
	const vk::pipeline::multisample_state
		multisample{ve::multisampling::max()};


	// depth stencil
	constexpr auto depth_stencil = vk::pipeline::depth_stencil_state{}
									.depth_test_enable(VK_TRUE)
									.depth_write_enable(VK_TRUE)
									.depth_compare_op(VK_COMPARE_OP_LESS);


	// color blend
	vk::pipeline::color_blend_state color_blend;
	color_blend.attachment();


	// dynamic state
	vk::pipeline::dynamic_state dynamic {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	// create pipeline
	return vk::pipeline{
		stages,
		vertex_input.info,
		input_assembly.info,
		tesselation.info,
		viewport.info,
		rasterization.info,
		multisample.info,
		depth_stencil.info,
		color_blend.info,
		dynamic.info,
		vk::pipeline_layout_library::get<"main">(),
		vk::render_pass::library::get<"main">()
	};
}

/* skybox */
static auto _skybox(void) -> vk::pipeline {

	// planet modules
	vk::vert_module vem{"shaders/spir-v/skybox.vert.spv"};
	vk::frag_module frm{"shaders/spir-v/skybox.frag.spv"};

	// shader stages
	const vk::array stages {
		vem.stage_info(),
		frm.stage_info(),
	};


	vk::pipeline::vertex_input_state vertex_input;

	vertex_input.binding(0U, sizeof(ve::vert3x), VK_VERTEX_INPUT_RATE_VERTEX)
				.description(0U, 0U, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ve::vert3x, position))
				.description(1U, 0U, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ve::vert3x, normal));



	// input assembly
	constexpr auto input_assembly = vk::pipeline::input_assembly_state{}
									.topology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
									.restart(VK_FALSE);

	// tesselation
	constexpr auto tesselation = vk::pipeline::tesselation_state{};


	// viewport
	constexpr vk::pipeline::viewport_state
		viewport{};

	// rasterization
	constexpr auto rasterization = vk::pipeline::rasterization_state{}
									.polygon_mode(VK_POLYGON_MODE_FILL)
									.cull_mode(VK_CULL_MODE_FRONT_BIT) // invert culling
									.front_face(VK_FRONT_FACE_CLOCKWISE);

	// multisample
	const vk::pipeline::multisample_state
		multisample{ve::multisampling::max()};


	// depth stencil
	constexpr auto depth_stencil = vk::pipeline::depth_stencil_state{};



	// color blend
	vk::pipeline::color_blend_state color_blend;
	color_blend.attachment();


	// dynamic state
	vk::pipeline::dynamic_state dynamic {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	// create pipeline
	return vk::pipeline{
		stages,
		vertex_input.info,
		input_assembly.info,
		tesselation.info,
		viewport.info,
		rasterization.info,
		multisample.info,
		depth_stencil.info,
		color_blend.info,
		dynamic.info,
		vk::pipeline_layout_library::get<"main">(),
		vk::render_pass::library::get<"main">()
	};
}


/* skybox compute */
static auto _skybox_compute(void) -> vk::pipeline {

	const vk::comp_module m{"shaders/spir-v/skybox_heightmap.comp.spv"};

	return vk::pipeline{
		m.stage_info(),
		vk::pipeline_layout_library::get<"skybox_compute">()
	};
	return {};
}


// -- private static methods --------------------------------------------------

/* shared */
auto vk::pipeline::library::_shared(void) -> self& {
	static self instance;
	return instance;
}


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vk::pipeline::library::library(void)
: _pipelines{
	_planet(),
	_skybox(),
	_skybox_compute()} {
}
