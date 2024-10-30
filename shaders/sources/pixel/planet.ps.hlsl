namespace ve {

	struct domain_out {
		float4 position : SV_Position;
		float3 normal   : NORMAL;
		float3 view_direction : VIEW_DIRECTION;
	};

	struct pixel_out {
		float4 color : SV_Target;
	};
}



ve::pixel_out main(ve::domain_out input) {

	ve::pixel_out output;
	output.color = float4(input.normal, 1.0f);
	return output;

	/*
	// normalized light direction
	const float3 material_diffuse = { 0.3, 0.3, 0.3 };
	const float3 light_direction = normalize(float3( +0.0, -0.5, -1.0 ));
	//const float3 light_direction = normalize(float3( +0.0, 0.5, +1.0 ));
	const float3 light_color = { +0.7, +0.7, +0.7 };

	float ambient_strength = 0.2;
	float3 ambiant = material_diffuse * ambient_strength;
	float3 total_light = ambiant;


	// -- diffuse -------------------------------------------------------------

	float3 diffuse = max(dot(
				input.normal,
				light_direction
				), 0.0) * light_color * material_diffuse;

	total_light += diffuse;


	// -- specular ------------------------------------------------------------


	const float shininess = 8.0;

	float3 reflect_direction = reflect(-light_direction, input.normal);

	float specular = pow(max(dot(input.view_direction, reflect_direction), 0.0), shininess);

	total_light += specular * light_color;



	ve::pixel_out output;
	output.color = float4(total_light, 1.0);
	return output;
	*/


}
