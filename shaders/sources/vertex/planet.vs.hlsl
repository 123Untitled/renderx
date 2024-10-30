
// hlsl vertex shader before tessellation (just pass through)

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

	struct vertex_in {
		[[vk::location(0)]] float3 position : POSITION;
		[[vk::location(1)]] float3 normal : NORMAL;
	};

	struct vertex_out {
		float3 position : POSITION;
		float3 normal : NORMAL;
		float distance_to_camera : DISTANCE_TO_CAMERA;
	};
}


// -- entrypoint --------------------------------------------------------------

[shader("vertex")]
ve::vertex_out main(const ve::vertex_in input) {

	// compute model position
	const float4 model_position = mul(model, float4(input.position, 1.0f));

	// compute distance to camera
	const float distance_to_camera = distance(cam_position, model_position.xyz);


	ve::vertex_out output;

	output.position = input.position;
	output.normal = input.normal;
	output.distance_to_camera = distance_to_camera;

	return output;
}

