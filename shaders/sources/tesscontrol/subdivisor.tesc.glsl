#version 450


// -- P U S H   C O N S T A N T S ---------------------------------------------

layout(push_constant) uniform push_constant_object {
	mat4 model;
	mat4 view;
	mat4 projection;
	vec3 camera_position;
} pco;



// -- I N P U T S -------------------------------------------------------------

layout(location = 0) in vec3 in_normal[];
layout(location = 1) in vec3 in_uv[];



// -- O U T P U T S -----------------------------------------------------------

/* number of vertices */
layout(vertices = 3) out;

layout(location = 0) out vec3 out_normal[];
layout(location = 1) out vec3 out_uv[];



void main(void) {

	// get position
	//vec3 position = gl_in[gl_InvocationID].gl_Position.xyz;
	//
	//// get model position
	//vec3 model_position = (pco.model * vec4(position, 1.0)).xyz;
	//
	//// distance from the camera
	//float distance = distance(pco.camera_position, model_position);
	//
	//
	//float max_tess_level = 200.0;
	//float min_tess_level = 1.0;
	//float max_distance   = 0.5;
	//
	//float tess_level = max_tess_level - clamp(distance / max_distance, 0.0, 1.0)
	//	* (max_tess_level - min_tess_level);
	//
	//
	// if (gl_InvocationID == 0)
 //   {
	//// outer[0] // edge 0-1
	//gl_TessLevelOuter[0] = tess_level;
	//// outer[1] // edge 1-2
	//gl_TessLevelOuter[1] = tess_level;
	//// outer[2] // edge 2-0
	//gl_TessLevelOuter[2] = tess_level;
	//
	//// inner[0] // inside the triangle
	//// Subdivision à l'intérieur du triangle
	//gl_TessLevelInner[0] = tess_level;
	//}


	 // Only need to set tessellation levels once per patch
	 if (gl_InvocationID == 0) {
		 // Constants for tessellation levels
		 float max_tess_level = 200.0;
		 float min_tess_level = 1.0;
		 float max_distance   = 0.5;

		 // Get positions of the three vertices in model space
		 vec3 position0 = gl_in[0].gl_Position.xyz;
		 vec3 position1 = gl_in[1].gl_Position.xyz;
		 vec3 position2 = gl_in[2].gl_Position.xyz;

		 vec3 model_position0 = (pco.model * vec4(position0, 1.0)).xyz;
		 vec3 model_position1 = (pco.model * vec4(position1, 1.0)).xyz;
		 vec3 model_position2 = (pco.model * vec4(position2, 1.0)).xyz;

		 // Compute distances from the camera to each vertex
		 float distance0 = distance(pco.camera_position, model_position0);
		 float distance1 = distance(pco.camera_position, model_position1);
		 float distance2 = distance(pco.camera_position, model_position2);

		 // Compute average distances for each edge
		 float avg_distance0 = (distance1 + distance2) * 0.5; // Edge between vertices 1 and 2
		 float avg_distance1 = (distance2 + distance0) * 0.5; // Edge between vertices 2 and 0
		 float avg_distance2 = (distance0 + distance1) * 0.5; // Edge between vertices 0 and 1

		 // Compute tessellation levels based on average distances
		 float tess_level0 = max_tess_level - clamp(avg_distance0 / max_distance, 0.0, 1.0)
			 * (max_tess_level - min_tess_level);
		 float tess_level1 = max_tess_level - clamp(avg_distance1 / max_distance, 0.0, 1.0)
			 * (max_tess_level - min_tess_level);
		 float tess_level2 = max_tess_level - clamp(avg_distance2 / max_distance, 0.0, 1.0)
			 * (max_tess_level - min_tess_level);

		 // Assign tessellation levels to each edge
		 gl_TessLevelOuter[0] = tess_level0; // Edge between vertices 1 and 2
		 gl_TessLevelOuter[1] = tess_level1; // Edge between vertices 2 and 0
		 gl_TessLevelOuter[2] = tess_level2; // Edge between vertices 0 and 1

		 // Set inner tessellation level (average of outer levels)
		 gl_TessLevelInner[0] = (tess_level0 + tess_level1 + tess_level2) / 3.0;
	 }


	// pass through vertex positions
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	// pass through normals
	out_normal[gl_InvocationID] = in_normal[gl_InvocationID];

	// pass through uv
	out_uv[gl_InvocationID] = in_uv[gl_InvocationID];
}

