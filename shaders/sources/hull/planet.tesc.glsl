#version 450

// number of vertices
layout(vertices = 3) out;


// -- input from vertex shader ------------------------------------------------

layout(location = 0) in vec3 in_normal[gl_MaxPatchVertices];
layout(location = 1) in float in_distance_to_camera[gl_MaxPatchVertices];

layout(location = 0) out vec3 out_normal[];


// gl_PatchVerticesIn:
// the number of vertices in the input patch

// gl_PrimitiveID:
// the index of the current patch within this rendering command

// gl_InvocationID:
// the index of the TCS invocation within this patch. A TCS invocation writes to per-vertex output variables by using this to index them.


void main(void) {

	// forward position
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	// forward normal
	out_normal[gl_InvocationID] = in_normal[gl_InvocationID];

	// only need to set tessellation levels once per patch
	if (gl_InvocationID != 0)
		return;


	// minimal distance for high tessellation
	const float near = 0.301f;
	// maximal distance for low tessellation
	const float far = 1.0f;

	float factor = 35.0f;


	float avg_0 = (in_distance_to_camera[1] + in_distance_to_camera[2]) * 0.5;
	float avg_1 = (in_distance_to_camera[2] + in_distance_to_camera[0]) * 0.5;
	float avg_2 = (in_distance_to_camera[0] + in_distance_to_camera[1]) * 0.5;

	float tess_0 = clamp((far - avg_0) / (far - near), 0.0, 1.0) * factor;
	float tess_1 = clamp((far - avg_1) / (far - near), 0.0, 1.0) * factor;
	float tess_2 = clamp((far - avg_2) / (far - near), 0.0, 1.0) * factor;

	tess_0 = (tess_0 < 1.0f) ? 1.0f : tess_0;
	tess_1 = (tess_1 < 1.0f) ? 1.0f : tess_1;
	tess_2 = (tess_2 < 1.0f) ? 1.0f : tess_2;

	// outer tessellation levels
	gl_TessLevelOuter[0] = tess_0;
	gl_TessLevelOuter[1] = tess_1;
	gl_TessLevelOuter[2] = tess_2;

	// inner tessellation level
	gl_TessLevelInner[0] = (tess_0 + tess_1 + tess_2) / 3.0f;
}

