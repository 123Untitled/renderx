
// tesselation control shader (hull shader) (hlsl)


namespace ve {

	// input from vertex shader
	struct vertex_out {
		float3 position : POSITION;
		float3 normal   : NORMAL;
		float distance_to_camera : DISTANCE_TO_CAMERA;
	};

	// output to domain shader
	struct hull_out {
		float3 position : POSITION;
		float3 normal   : NORMAL;
	};

	// hull patch constants
	struct constant_hull_patch_out {
		float edge_factors[3] : SV_TessFactor;
		float inside_factor : SV_InsideTessFactor;
	};
}

ve::constant_hull_patch_out constants(InputPatch<ve::vertex_out, 3> patch,
														uint patch_index : SV_PrimitiveID) {
	ve::constant_hull_patch_out output;

	// Paramètres de distance pour ajuster la tessellation
    const float near = 0.01f;  // Distance minimale pour une tessellation élevée
    const float far = 1.5f;  // Distance maximale au-delà de laquelle la tessellation diminue

	const float factor = 15.0f;

	// Moyenne des distances des trois points de contrôle pour la tessellation
    const float average_distance = (patch[0].distance_to_camera + patch[1].distance_to_camera + patch[2].distance_to_camera) / 3.0f;

    // Calculer le facteur de tessellation basé sur la distance (plus près = tessellation plus élevée)
    //float tess_factor = saturate(1.0f / average_distance) * 4.0f; // Ajuster le facteur ici

	float tess_factor = saturate((far - average_distance) / (far - near)) * factor;


	tess_factor = tess_factor ? tess_factor : 1.0f;

	/*
	output.edge_factors[0] = tess_factor;
	output.edge_factors[1] = tess_factor;
	output.edge_factors[2] = tess_factor;
	output.inside_factor = tess_factor;
	*/
	output.edge_factors[0] = 1;
	output.edge_factors[1] = 1;
	output.edge_factors[2] = 1;
	output.inside_factor = 1;

	return output;
}


// hull shader entry point
[domain("tri")]
[partitioning("fractional_odd")] // fractional avoids popping
[outputtopology("triangle_cw")]
[outputcontrolpoints(3U)]
//[maxtessfactor(64.0f)] // hint to the driver (lower is better)
[patchconstantfunc("constants")]
[shader("hull")]
ve::hull_out main(InputPatch<ve::vertex_out, 3> input,
							uint patch_index : SV_OutputControlPointID) {

	ve::hull_out output;

	output.position = input[patch_index].position;
	output.normal = input[patch_index].normal;

	return output;
}
