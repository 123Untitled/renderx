#version 450

/* number of vertices */
layout(vertices = 3) out;

// -- I N P U T S -------------------------------------------------------------

layout(location = 0) in vec3 in_normal[gl_MaxPatchVertices];
layout(location = 1) in float in_distance_to_camera[gl_MaxPatchVertices];

layout(location = 0) out vec3 out_normal[];


void main(void) {

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	out_normal[gl_InvocationID] = in_normal[gl_InvocationID];

	// Only need to set tessellation levels once per patch
	if (gl_InvocationID != 0)
		return;

	// minimal distance for high tessellation
	const float near = 0.01f;
	// maximal distance for low tessellation
	const float far = 1.5f;

	float factor = 65.0f;

	// average distance to camera
	float average_distance = (in_distance_to_camera[0] + in_distance_to_camera[1] + in_distance_to_camera[2]) / 3.0f;

	float tess_factor = clamp((far - average_distance) / (far - near), 0.0, 1.0) * factor;

	if (tess_factor == 0.0f) {
		tess_factor = 1.0f;
	}

	// Assign tessellation levels to each edge
	gl_TessLevelOuter[0] = tess_factor;
	gl_TessLevelOuter[1] = tess_factor;
	gl_TessLevelOuter[2] = tess_factor;


	// Set inner tessellation level (average of outer levels)
	gl_TessLevelInner[0] = (gl_TessLevelOuter[0] + gl_TessLevelOuter[1] + gl_TessLevelOuter[2]) / 3.0f;


}

