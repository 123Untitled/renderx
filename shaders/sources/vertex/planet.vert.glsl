#version 450


layout(set = 0, binding = 0) uniform cam_uniform {
	mat4 projection;
	mat4 view;
	vec3 position;
} cam;

layout(set = 1, binding = 0) uniform model_uniform {
	mat4 model;
} model;


// -- input from cpu ----------------------------------------------------------

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;


// -- output to hull shader ---------------------------------------------------

layout(location = 0) out vec3 out_normal;
layout(location = 1) out float out_distance_to_camera;


// -- entrypoint --------------------------------------------------------------

void main(void) {

	gl_Position = vec4(in_position, 1.0f);

	// compute model position
	const vec4 model_position = model.model * vec4(in_position, 1.0f);

	// forward normal
	out_normal = in_normal;

	// set distance to camera
	out_distance_to_camera = distance(cam.position, model_position.xyz);
}
