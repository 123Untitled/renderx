#version 450


layout(push_constant) uniform push_constants {
	float time;
} pc;

layout(location = 0) in vec3 in_normal;
layout(location = 1) in vec3 in_view_direction;
layout(location = 2) in vec3 in_view_position;

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
	vec3 light_direction = normalize(vec3(-0.0, -1.0, -1.0));

	// material properties
	vec3 material_diffuse = vec3(0.3, 0.3, 0.3);
	//vec3 material_diffuse = vec3(0.2, 0.22, 0.4);
	vec3 material_ambient = material_diffuse * 0.1;
		//vec3(0.10) * material_diffuse;
	vec3 material_specular = vec3(1.2);
	float material_shininess = 8.0;


	// -- diffuse -------------------------------------------------------------

	// compute lambertian shading
	const float lamb = max(dot(normal, light_direction), 0.0f);

	// comput shadow factor
	const float shadow_factor = (1.0f - lamb);

	// compute diffuse color
	vec3 diffuse = material_diffuse * lamb;

	// Appliquer une saturation plus élevée dans les zones d'ombre
	float saturation_boost = 1.0 + (shadow_factor * 7.0);  // Par exemple, augmenter la saturation dans l'ombre

	vec3 shadow_color = adjust_saturation(diffuse, saturation_boost);

	diffuse = mix(diffuse, shadow_color, shadow_factor);


	// -- specular ------------------------------------------------------------

	// phong shading
	vec3 reflection = reflect(-light_direction, normal);
	vec3 specular = pow(max(dot(reflection, in_view_direction), 0.0), material_shininess) * material_specular * out_normal;


	// -- rim light -----------------------------------------------------------

	// rim light
	float rim_strength = 1.8;
	float rim = smoothstep(0.0, 1.0, pow(
						 1.0 - max(
							dot(in_view_direction, normal), 0.0), material_shininess)
	) * rim_strength;

	diffuse += (rim*out_normal);




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
	out_color = vec4((material_ambient + diffuse + specular), 1.0);



	// -- dithering -----------------------------------------------------------

	// compute luminance
	const float luminance = dot(out_color.rgb, vec3(0.299, 0.587, 0.114));

	// generate dithering pattern
	float rand = random(gl_FragCoord.xy * pc.time);

	// noise factor
	const float noise_factor = mix(0.03, 1.0, pow(luminance, 2.0));

	rand *= noise_factor;

	vec3 dithering = vec3(rand);


	// -- output --------------------------------------------------------------

	// output color
	out_color = out_color + vec4(dithering, 0.0);
}
