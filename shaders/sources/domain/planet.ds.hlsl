
// tesselation evaluation shader (domain shader) (hlsl)

#include "simplex.hlsl"


namespace ve {

	[[vk::binding(0, 0)]]
	cbuffer cam : register(b0) {
		column_major float4x4 cam_projection;
		column_major float4x4 cam_view;
		float3   cam_position;
	};

	[[vk::binding(0, 1)]]
	cbuffer model : register(b1) {
		column_major float4x4 model;
	};

	// input control points
	struct hull_out {
		float3 position : POSITION;
		float3 normal   : NORMAL;
	};

	// output control points
	struct domain_out {
		float4 position : SV_Position;
		float3 normal : NORMAL;
		float3 view_direction : VIEW_DIRECTION;
	};

	// hull patch constants
	struct constant_hull_patch_out {
		float edge_factors[3] : SV_TessFactor;
		float inside_factor : SV_InsideTessFactor;
	};
}


float3 barycentric_interpolate(const float3 v0,
							   const float3 v1,
							   const float3 v2,
							   const float3 barycentric) {
    return (barycentric.x * v0) + (barycentric.y * v1) + (barycentric.z * v2);
}


[domain("tri")]
[shader("domain")]
ve::domain_out main(const ve::constant_hull_patch_out input,
					const float3 bary : SV_DomainLocation,
					const OutputPatch<ve::hull_out, 3> patch) {


	// -- position ------------------------------------------------------------

	// interpolate position with barycentric coordinates
	float3 interp_position = normalize(barycentric_interpolate(patch[0].position,
																	 patch[1].position,
																	 patch[2].position,
																	 bary));


	// compute model position
    const float4 model_position = mul(
			model,
			float4(interp_position, 1.0f)
			);

	// compute view position
    const float4 view_position = mul(
			cam_view,
			model_position
			);

	// compute view direction
	const float3 view_direction = normalize(
			cam_position
			-
			model_position.xyz
			);

	// compute projection
	const float4 projection = mul(
			cam_projection,
			view_position
			);



	// -- normal --------------------------------------------------------------

	// interpolate normal with barycentric coordinates
	float3 interp_normal = (barycentric_interpolate(patch[0].normal,
															 patch[1].normal,
															 patch[2].normal,
															 bary));

	// compute normal surface
	const float3 normal_surface = normalize(mul(
				model,
				float4(interp_normal, 0.0f)
				).xyz
			);


	// -- output --------------------------------------------------------------

	ve::domain_out output;

	output.position       = projection;
	output.normal         = normal_surface;
	output.view_direction = view_direction;

	return output;
}



	/*
	const uint octaves = 8U;
	const float amplitude = 0.80f;
	const float frequency = 2.0f;
	const float lacunarity = 3.0f;
	const float persistence = 0.8f;

	// generate simplex noise
	const float noise = fractal(octaves,
								lacunarity,
								persistence,
								amplitude,
								frequency,
								interp_position.x,
								interp_position.y,
								interp_position.z);

	// apply simplex noise
	interp_position *= (1.0f + noise);
	*/

