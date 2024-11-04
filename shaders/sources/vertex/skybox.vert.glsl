#version 450

// -- S K Y B O X  V E R T E X  S H A D E R -----------------------------------

/* uniform */
layout(set = 0, binding = 0) uniform cam_uniform {
	mat4 projection;
	mat4 view;
} cam;


// -- input from cpu ----------------------------------------------------------

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_texcoord;


// -- output to fragment shader -----------------------------------------------

layout(location = 0) out vec3 out_texcoord;


// -- entrypoint --------------------------------------------------------------

void main(void) {

	// compute the model position
	vec4 position = vec4(in_position, 1.0);

	// get view matrix
	mat4 view = cam.view;

	// ignore the translation part of the view matrix
	view[3U].xyz = vec3(0.0, 0.0, 0.0);

	// scale the position by x10
	position.xyz *= 100.0;

	// compute the final position
	gl_Position = cam.projection * view * position;

	// forward texcoord
	out_texcoord = in_texcoord;
}
