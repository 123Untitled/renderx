
// basic exemple of fragment shader (GLSL)

// fragment shader program

#version 450

layout(location = 0) in  vec3 frag_normal_surface;
layout(location = 1) in vec3 in_uv[];

layout(location = 0) out vec4 out_color;


void main(void) {

	//out_color = vec4(0.8, 0.9, 0.3, 1.0);
	//return;

	vec3 light_dir = normalize(vec3(0.1, 0.3, -1.0));
	vec3 light_color = vec3(0.5, 0.5, 0.5);
	vec3 ambient_color = vec3(0.1, 0.1, 0.1);
	vec3 diffuse_color = vec3(0.5, 0.5, 0.5);


	// normalisation de la normale
	vec3 normal = frag_normal_surface;

	// calcul de la lumière diffuse
	float NdotL = dot(light_dir, normal);
	float light_intensity = smoothstep(0.0, 1.0, NdotL);
	vec3 diffuse = light_intensity * light_color;

	// calcul de la lumière ambiante
	vec3 ambient = ambient_color;


	// calcul de la lumière totale
	vec3 total_light = ambient + diffuse;

	out_color = vec4(total_light, 1.0);




	/*
	// map the position to a color
	vec3 in_color = in_position * 0.5 + 0.5;
	out_color = vec4(in_color, 1.0);
	*/
}
