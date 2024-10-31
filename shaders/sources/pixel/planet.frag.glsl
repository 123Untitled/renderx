#version 450

layout(location = 0) in vec3 in_normal;
layout(location = 1) in vec3 in_view_direction;
layout(location = 2) in vec3 in_view_position;

layout(location = 0) out vec4 out_color;


void main(void) {

	out_color = vec4(1.0, 1.0, 1.0, 1.0);
	return;

	// Calcul des dérivées en espace écran
	vec3 dFdxPos = dFdx(in_view_position);
	vec3 dFdyPos = dFdy(in_view_position);

	// Calcul de la normale
	vec3 normal = normalize(-cross(dFdxPos, dFdyPos));


	// Ajustement de la normale pour l'affichage
	vec3 out_normal = (normal + 1.0) * 0.5;


	//out_color = vec4(1.0, 1.0, 0.0, 1.0);
	//return;

	// light direction
	vec3 light_direction = normalize(vec3(-1.0, -1.0, -1.0));

	// material properties
	vec3 material_diffuse = vec3(0.8, 0.8, 0.8);
	vec3 material_ambient = material_diffuse * 0.1;
		//vec3(0.10) * material_diffuse;
	vec3 material_specular = vec3(1.0);
	float material_shininess = 64.0;

	// lambertian shading
	vec3 diffuse = max(dot(normal, light_direction), 0.0) * material_diffuse;

	// phong shading
	vec3 reflection = reflect(-light_direction, normal);
	vec3 specular = pow(max(dot(reflection, in_view_direction), 0.0), material_shininess) * material_specular;

	// output color
	out_color = vec4((material_ambient + diffuse + specular), 1.0);
}
