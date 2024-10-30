
// tesselation evaluation shader (domain shader) (slang)


namespace ve {

	struct cam_uniform {
		float4x4 projection;
		float4x4 view;
		float3 position;
		float3 rotation;
		float3 direction;
	};

	struct model_uniform {
		float4x4 model;
	};

	// input control points
	struct hull_out {
		float3 sv_position : SV_Position;
		float3 position : POSITION;
		float3 normal   : NORMAL;
		float2 texcoord : TEXCOORD;
		/*
		[[vk::location(0)]] float3 position : POSITION;
		[[vk::location(1)]] float3 normal : NORMAL;
		[[vk::location(2)]] float2 texcoord : TEXCOORD;
		*/
	};

	// output control points
	struct domain_out {
		float4 position : SV_Position;
		float3 normal : NORMAL;
		float2 texcoord : TEXCOORD;
	};

	// hull patch constants
	struct constant_hull_patch_out {
		float edge_factors[3] : SV_TessFactor;
		float inside_factor : SV_InsideTessFactor;
	};
}


[domain("tri")]
[shader("domain")]
ve::domain_out main(ve::constant_hull_patch_out input, float3 bary : SV_DomainLocation,
				OutputPatch<ve::hull_out, 3> patch,
		[[vk::binding(0, 0)]] ParameterBlock<ve::cam_uniform> cam,
		[[vk::binding(0, 1)]] ParameterBlock<ve::model_uniform> model) {


	ve::domain_out output = {};

	return output;

    // Interpolation barycentrique de la position pour le patch
	/*
	float3 world_position =
		mul(bary.x, input[0].position) +
		mul(bary.y, input[1].position) +
		mul(bary.z, input[2].position);


	// compute model position
	const float4 model_position = mul(model.model, float4(world_position, 1.0));

	// compute view position
	const float4 view_position = mul(cam.view, model_position);


	output.position = mul(cam.projection, view_position);

	// Interpolation des normales et coordonnées UV
	output.normal =
		bary.x * input[0].normal + 
		bary.y * input[1].normal + 
		bary.z * input[2].normal;

	output.texcoord =
		bary.x * input[0].texcoord + 
		bary.y * input[1].texcoord + 
		bary.z * input[2].texcoord;

	return output;
	*/
}

			 //float3 uvwCoord : SV_DomainLocation,
			 //const OutputPatch<ve::out, 3> patch,
