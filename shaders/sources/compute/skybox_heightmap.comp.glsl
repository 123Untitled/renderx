#version 450

#include "voronoise.glsl"

layout(local_size_x = 16, local_size_y = 16) in; // Taille du groupe de travail

layout(binding = 0, rgba32f) uniform image2D heightmap_image;


void main(void) {

	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	// normalizing pixel coordinates
	vec2 uv = vec2(pixel_coords) / vec2(imageSize(heightmap_image));

	//// voronoise parameters
	const float u = 1.0; // scale
	const float v = 0.5; // k modulator

	// voronoise computation
	const float noise = voronoise(uv, u, v);
	//
	// storing the result in the image
	//imageStore(heightmap_image, pixel_coords, vec4(noise, noise, noise, 1.0));
}
