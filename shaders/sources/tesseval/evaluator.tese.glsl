#version 450


// Push constants ou uniformes contenant les matrices de transformation
layout(binding = 0) uniform cam_uniform {
	mat4 projection;
	mat4 view;
	vec3 position;
	vec3 rotation;
	vec2 direction;
} cam;

layout(binding = 1) uniform model_uniform {
	mat4 model;
} model;



// -- I N P U T S -------------------------------------------------------------

layout(triangles,
	   fractional_odd_spacing,
	   //fractional_even_spacing,
	   //equal_spacing,
	   cw) in;

layout(location = 0) in vec3 in_normal[];
layout(location = 1) in vec3 in_uv[];



// -- O U T P U T S -----------------------------------------------------------

layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec3 out_uv;


void main(void) {

	vec4 interpoled_position = gl_TessCoord.x * gl_in[0].gl_Position +
							   gl_TessCoord.y * gl_in[1].gl_Position +
							   gl_TessCoord.z * gl_in[2].gl_Position;

	vec3 normalized_position = normalize(interpoled_position.xyz);

	gl_Position = cam.projection * cam.view * model.model * vec4(normalized_position, 1.0);

	out_normal = gl_TessCoord.x * in_normal[0]
			   + gl_TessCoord.y * in_normal[1]
			   + gl_TessCoord.z * in_normal[2];

	out_uv = gl_TessCoord.x * in_uv[0]
		   + gl_TessCoord.y * in_uv[1]
		   + gl_TessCoord.z * in_uv[2];
}
