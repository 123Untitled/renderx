#version 450

// -- uniform -----------------------------------------------------------------

//layout(binding = 0) uniform uniform_buffer_object {
//	mat4 model;
//	mat4 view;
//	mat4 proj;
//} ubo;


// -- push constant -----------------------------------------------------------

layout(push_constant) uniform push_constant_object {
	mat4 model;
} pco;


// -- input -------------------------------------------------------------------

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;


// -- output ------------------------------------------------------------------

layout(location = 0) out vec3 frag_color;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
	//gl_Position = vec4(in_position, 1.0);
	gl_Position = pco.model * vec4(in_position, 1.0);
    frag_color = in_color;
}
