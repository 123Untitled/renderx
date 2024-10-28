#version 450


// -- I N P U T S -------------------------------------------------------------

// -- push constant -----------------------------------------------------------

//layout(push_constant) uniform push_constant_object {
//	mat4 model;
//	mat4 view;
//	mat4 projection;
//	vec3 camera_position;
//} pco;


// -- user inputs from cpu ----------------------------------------------------

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_uv;


// -- O U T P U T S -----------------------------------------------------------

// -- user outputs to tessellation control shader -----------------------------

//layout(location = 0) out vec3 out_position;
layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec3 out_uv;


// -- reserved outputs to tessellation control shader -------------------------

//out gl_PerVertex {
//    vec4 gl_Position;
//};


void main(void) {

	// pass through vertex positions
	//out_position = in_position;

	// pass through normals
	out_normal = in_normal;

	// pass through uv
	out_uv = in_uv;


	gl_Position = vec4(in_position, 1.0);


	// compute model position
	//const vec4 model_position = pco.model * vec4(in_position, 1.0);

	// compute view position
	//const vec4 view_position = pco.view * model_position;

	// compute normal
	//out_normal_surface = normalize((pco.model * vec4(in_normal, 0.0)).xyz);

	// compute projected position
	//gl_Position = pco.projection * view_position;
}
