#version 450

// -- uniform -----------------------------------------------------------------


// -- push constant -----------------------------------------------------------

layout(push_constant) uniform push_constant_object {
	mat4 model;
	mat4 view;
	mat4 projection;
} pco;


// -- input -------------------------------------------------------------------

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_uv;


// -- output ------------------------------------------------------------------

layout(location = 0) out vec3 frag_normal_surface;
//layout(location = 1) out vec3 frag_position;

out gl_PerVertex {
    vec4 gl_Position;
};

void main(void) {

	// compute model position
	vec4 model_position = pco.model * vec4(in_position, 1.0);

	// compute view position
	vec4 view_position = pco.view * model_position;

	// compute normal
	vec3 normal_surface = normalize((pco.model * vec4(in_normal, 0.0)).xyz);

	// compute projected position
	gl_Position = pco.projection * view_position;


	frag_normal_surface = normal_surface;
	//frag_position = model_position.xyz;
}
