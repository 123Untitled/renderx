
// tesselation control shader (hull shader) (slang)


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

	// input from vertex shader
	struct vertex_out {
		float3 position : POSITION;
		float3 normal   : NORMAL;
		float2 texcoord : TEXCOORD;
	};

	// output to domain shader
	struct hull_out {
		float4 sv_position : SV_Position;
		float3 position : POSITION;
		float3 normal   : NORMAL;
		float2 texcoord : TEXCOORD;
	};

	// hull patch constants
	struct constant_hull_patch_out {
		float edge_factors[3] : SV_TessFactor;
		float inside_factor : SV_InsideTessFactor;
	};
}

[patchconstantfunc("constants")]
ve::constant_hull_patch_out constants(InputPatch<ve::vertex_out, 3> patch,
														uint patch_index : SV_PrimitiveID) {
	ve::constant_hull_patch_out output = {};

	output.edge_factors[0] = 1.0;
	output.edge_factors[1] = 1.0;
	output.edge_factors[2] = 1.0;
	output.inside_factor = 1.0;

	return output;
}


// hull shader entry point
[domain("tri")]
[partitioning("fractional_even")] // fractional avoids popping
[outputtopology("triangle_cw")]
[outputcontrolpoints(3U)]
[maxtessfactor("64.0f")] // hint to the driver (lower is better)
[shader("hull")]
ve::hull_out main(InputPatch<ve::vertex_out, 3> input,
								uint patch_index : SV_OutputControlPointID,
				[[vk::binding(0, 0)]] ParameterBlock<ve::cam_uniform> cam,
				[[vk::binding(0, 1)]] ParameterBlock<ve::model_uniform> model
				) {

	ve::hull_out output = {};

	output.position = input[patch_index].position;
	output.normal = input[patch_index].normal;
	output.texcoord = input[patch_index].texcoord;
	output.sv_position = float4(output.position, 1.0);


	return output;
}

//[patchconstantfunc("patch_constants")]

// Fonction de constantes de patch pour définir les facteurs de tessellation
//[patchconstantfunc("constants")]
//float4 constants(const OutputPatch<ve::in, 3> input) {
//	return float4(3.0, 3.0, 3.0, 3.0); // Facteurs de tessellation
//}

//[patchconstantfunc("constants")]
//OutputPatch<ve::out, 3> 
			 //out float edge_factors[3] : SV_TessFactor,
			 //out float inside_factor : SV_InsideTessFactor,
