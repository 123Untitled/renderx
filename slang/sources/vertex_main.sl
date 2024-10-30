
// vertex shader main function (slang)

struct cam_uniform {
	float4x4 projection;
	float4x4 view;
	float3 position;
	float3 rotation;
	float3 direction;
};

struct vertex_uniform {
	float4x4 model;
};

struct vertex_in {
	[[vk::location(0)]] float3 position;
	[[vk::location(1)]] float3 normal;
	[[vk::location(2)]] float2 uv;
};

struct vertex_out {
	float4 position : SV_POSITION;
	float3 normal;
	float2 uv;
	float3 view_direction;
};


[shader("vertex")]
vertex_out main(vertex_in input,
		[[vk::binding(0, 0)]] ParameterBlock<cam_uniform> cam,
		[[vk::binding(0, 1)]] ParameterBlock<vertex_uniform> model) {


	// compute model position
	const float4 model_position = mul(model.model, float4(input.position, 1.0));

	// compute view position
	const float4 view_position = mul(cam.view, model_position);

	// compute normal
	const float3 normal = normalize(mul(model.model, float4(input.normal, 0.0)).xyz);

	// compute view direction
	const float3 view_direction = normalize(cam.position - model_position.xyz);

	// compute uv
	const float2 uv = input.uv;

	return vertex_out(
		mul(cam.projection, view_position),
		normal,
		uv,
		view_direction
	);
}
