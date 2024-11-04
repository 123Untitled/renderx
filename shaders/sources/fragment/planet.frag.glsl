#version 450

#extension GL_EXT_debug_printf : enable
#extension GL_EXT_spirv_intrinsics : enable


layout(location = 0) in vec3 in_normal;
layout(location = 1) in vec3 in_view_direction;
layout(location = 2) in vec3 in_view_position;
layout(location = 3) in float in_noise;

layout(location = 0) out vec4 out_color;


/* ajust saturation */
vec3 adjust_saturation(const vec3 color, const float saturation) {

	// luminance coefficient
	const vec3 luminance = {0.299f, 0.587f, 0.114f};

	// convert to grayscale
	const float intensity = dot(color, luminance);

	// mix color with grayscale (1.0 = full color, 0.0 = full grayscale)
	return mix(vec3(intensity), color, saturation);
}

// Fonction pour générer un bruit pseudo-aléatoire basé sur les coordonnées du pixel
/*
float random(vec2 uv, float seed) {
	// Générer un nombre pseudo-aléatoire à partir des coordonnées UV
	return fract(sin(dot(uv.xy, vec2(12.9898, 78.233)) + seed) * 43758.5453);
}*/

float random(vec2 coord) {
    return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5453);
}


void main(void) {

	//out_color = vec4(1.0, 1.0, 1.0, 1.0);
	//return;

	// Calcul des dérivées en espace écran
	vec3 dFdxPos = dFdx(in_view_position);
	vec3 dFdyPos = dFdy(in_view_position);

	// Calcul de la normale
	vec3 normal = normalize(-cross(dFdxPos, dFdyPos));


	// Ajustement de la normale pour l'affichage
	vec3 out_normal = (-normal + 1.0) * 0.5;


	// light direction
	vec3 light_direction = normalize(vec3(-0.0, -0.0, -1.0));
	float light_intensity = 1.0;

	vec3 material_diffuse = vec3(0.8);
			//0.9 - (1.0 - (in_noise * 3.0)),
			//0.3 - (1.0 - (in_noise * 6.0)),
			//0.1 - (1.0 - (in_noise * 9.0))
			//) * 0.7;

	// material properties
	//vec3 material_diffuse = vec3(0.3 * (1.0 - in_noise * 9.0),
	//							 0.6 * (1.0 - in_noise * 6.0),
	//							 0.9 * (1.0 - in_noise * 3.0));
		//vec3(1.0, 1.0, 1.0) *
	vec3 material_ambient = vec3(0.002);


	// -- diffuse -------------------------------------------------------------

	// compute lambertian shading
	const float lamb = max(dot(normal, light_direction), 0.0f);

	// comput shadow factor
	const float shadow_factor = (1.0f - lamb);

	// compute diffuse color
	vec3 diffuse = material_diffuse * lamb * light_intensity;

	// Appliquer une saturation plus élevée dans les zones d'ombre
	float saturation_boost = 1.0 + (shadow_factor * 2.0);  // Par exemple, augmenter la saturation dans l'ombre

	vec3 shadow_color = adjust_saturation(
			//diffuse
			(out_normal*0.2) * diffuse
			, saturation_boost);

	diffuse = mix(diffuse, shadow_color, shadow_factor);


	// -- specular ------------------------------------------------------------

	// phong shading
	vec3 specular_color = vec3(1.0, 0.8, 1.0);
	float specular_intensity = 1.0;
	float specular_shininess = 64.0;
	vec3 reflection = reflect(-light_direction, normal);
	float specular_value = pow(max(dot(reflection, in_view_direction), 0.0), specular_shininess);
	vec3 specular = specular_value * specular_intensity * specular_color * light_intensity;


	// -- rim light -----------------------------------------------------------

	// rim light
	float rim_strength = 1.5;
	float rim_shininess = 4.0;
	vec3 rim_color = out_normal;
	float rim = smoothstep(0.0, 1.0, pow(
						 1.0 - max(
							dot(in_view_direction, normal), 0.0), rim_shininess)
	) * rim_strength;

	diffuse += vec3(rim) * rim_color;




	// luminance factor
	//float noise_factor = mix(0.15, 1.0, pow(lamb, 2.0)); // 0.3 pour un peu de bruit dans les zones sombres
	//
	//// accentuate dithering based on luminance
	//d *= noise_factor;

	// dithering pattern
	//vec4 dither = vec4(d, d, d, 1.0);

	// add dithering
	//diffuse += dither.xyz;


	// -- output --------------------------------------------------------------

	// output color
	out_color = vec4((diffuse + specular + material_ambient), 1.0);


}
