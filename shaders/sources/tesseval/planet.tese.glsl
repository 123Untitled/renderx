#version 450

#include "simplex.glsl"
#include "voronoise.glsl"
#include "worley.glsl"
#include "gerstner_wave.glsl"
#include "wavelet.glsl"
//#include "curl.glsl"

layout(set = 0, binding = 0) uniform cam_uniform {
	mat4 projection;
	mat4 view;
	vec3 position;
} cam;

layout(set = 1, binding = 0) uniform model_uniform {
	mat4 model;
} model;


layout(triangles,
	   //fractional_odd_spacing,
	   equal_spacing,
	   //fractional_even_spacing,
	   cw) in;


// -- I N P U T S -------------------------------------------------------------


layout(location = 0) in vec3 in_normal[gl_MaxPatchVertices];
layout(location = 1) in float in_distance_to_camera[gl_MaxPatchVertices];



// -- O U T P U T S -----------------------------------------------------------

layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec3 out_view_direction;
layout(location = 2) out vec3 out_view_position;
layout(location = 3) out float out_noise;


void main(void) {


	// retrieve control point position coordinates
	vec3 interpoled_position = (gl_TessCoord.x * gl_in[0].gl_Position.xyz)
							 + (gl_TessCoord.y * gl_in[1].gl_Position.xyz)
							 + (gl_TessCoord.z * gl_in[2].gl_Position.xyz);

	interpoled_position = normalize(interpoled_position);


	// Calculate distance between camera and interpolated position on the sphere surface
	//float camera_distance = length(cam.position - (model.model * vec4(interpoled_position, 1.0)).xyz);

	// Adjust amplitude based on the proximity of the camera
	//float amplitude = mix(0.16, 0.01, smoothstep(0.5, 0.01, camera_distance));


	const uint octaves = 1U;
	const float amplitude = 0.06f;
	const float frequency = 5.5f;
	const float lacunarity = 2.5f;
	const float persistence = 0.8f;


	// get noise
	float noise = 0.0f;
	//noise = fractal(octaves, amplitude * 0.1, frequency*0.1, lacunarity, persistence, interpoled_position);
	noise += simplex(interpoled_position * frequency) * amplitude;
	//noise += voronoise(interpoled_position * frequency, 1.15, 0.9) * (amplitude* 5.0f);
	//noise += worley(interpoled_position * (frequency*1)) * (amplitude * 0.1f);
	//noise += wavelet(interpoled_position * frequency, 1.5f) * (amplitude * 0.3f);

	//float attenuation = 1.0f / (1.0f + in_distance_to_camera * 0.1f);


	out_noise = noise;

	// interpolate position
	vec3 perturbed_position = interpoled_position * (1.0 + noise);


	// compute model position
	const vec4 model_position = model.model * vec4(perturbed_position, 1.0f);

	// compute view position
	const vec4 view_position = cam.view * model_position;

	// compute view direction
	const vec3 view_direction = normalize(cam.position - model_position.xyz);


    // ----------------------------------------------------------------------

	// compute space position
    gl_Position = cam.projection * view_position;


	// output view direction
	out_view_direction = view_direction;

	// output model position
	out_view_position = model_position.xyz;


	// compute height (distance between vertex and 0,0,0)
}



/*
							   */

//	vec3 normal = perturbed_normal;



	// Obtenir les positions normalisées des sommets d'origine
	/*
	vec3 p1 = normalize(gl_in[0].gl_Position.xyz);
	vec3 p2 = normalize(gl_in[1].gl_Position.xyz);
	vec3 p3 = normalize(gl_in[2].gl_Position.xyz);

	// Paramètres du bruit
	const float amplitude = 2.40f;
	const float frequency = 2.0f;

	// Appliquer le bruit aux trois sommets
	vec3 p1_perturbed = p1 * (1.0 + simple_noise(p1 * frequency) * amplitude);
	vec3 p2_perturbed = p2 * (1.0 + simple_noise(p2 * frequency) * amplitude);
	vec3 p3_perturbed = p3 * (1.0 + simple_noise(p3 * frequency) * amplitude);

	// Interpoler la position en utilisant les sommets perturbés
	vec3 interpolated_position = gl_TessCoord.x * p1_perturbed +
								 gl_TessCoord.y * p2_perturbed +
								 gl_TessCoord.z * p3_perturbed;

	// Projeter sur la sphère en normalisant après l'interpolation
	interpolated_position = normalize(interpolated_position) * (1.0 + amplitude * 0.5);

	// Recalculer les vecteurs d'arête avec les positions perturbées
	vec3 edge1 = p2_perturbed - p1_perturbed;
	vec3 edge2 = p3_perturbed - p1_perturbed;

	// Calculer la normale perturbée avec les sommets bruités
	vec3 perturbed_normal = normalize(cross(edge2, edge1));

	// Calculer la normale perturbée
	vec3 normal = perturbed_normal;

	vec3 perturbed_position = interpolated_position;
	*/




    // Utiliser deux décalages pour calculer la normale avec le produit vectoriel
    //vec3 dp1 = normalize(interpoled_position + vec3(0.1, 0.0, 0.0)) * (1.0 + simplex((interpoled_position + vec3(0.1, 0.0, 0.0)) * frequency) * amplitude);
    //vec3 dp2 = normalize(interpoled_position + vec3(0.0, 0.1, 0.0)) * (1.0 + simplex((interpoled_position + vec3(0.0, 0.1, 0.0)) * frequency) * amplitude);
    //
    //// Calculer la normale perturbée en prenant le produit vectoriel
    //vec3 perturbed_normal = normalize(cross(dp1 - perturbed_position, dp2 - perturbed_position));
    //
    //// Transformation de la normale dans l’espace monde en utilisant la matrice normale
    //mat3 normal_matrix = transpose(inverse(mat3(model.model)));
    //vec3 world_normal = normalize(normal_matrix * perturbed_normal);



	// retrieve control point normal
	//vec3 normal = gl_TessCoord.x * in_normal[0]
	//		    + gl_TessCoord.y * in_normal[1]
	//			+ gl_TessCoord.z * in_normal[2];

	// normalize normal
	//normal = normalize(normal);
















////	Simplex 3D Noise 
////	by Ian McEwan, Stefan Gustavson (https://github.com/stegu/webgl-noise)
////
//vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
//vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}
//
//float simplex2(vec3 v){ 
//	const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
//	const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);
//
//	// First corner
//	vec3 i  = floor(v + dot(v, C.yyy) );
//	vec3 x0 =   v - i + dot(i, C.xxx) ;
//
//	// Other corners
//	vec3 g = step(x0.yzx, x0.xyz);
//	vec3 l = 1.0 - g;
//	vec3 i1 = min( g.xyz, l.zxy );
//	vec3 i2 = max( g.xyz, l.zxy );
//
//	//  x0 = x0 - 0. + 0.0 * C 
//	vec3 x1 = x0 - i1 + 1.0 * C.xxx;
//	vec3 x2 = x0 - i2 + 2.0 * C.xxx;
//	vec3 x3 = x0 - 1. + 3.0 * C.xxx;
//
//	// Permutations
//	i = mod(i, 289.0 ); 
//	vec4 p = permute( permute( permute( 
//					i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
//				+ i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
//			+ i.x + vec4(0.0, i1.x, i2.x, 1.0 ));
//
//	// Gradients
//	// ( N*N points uniformly over a square, mapped onto an octahedron.)
//	float n_ = 1.0/7.0; // N=7
//	vec3  ns = n_ * D.wyz - D.xzx;
//
//	vec4 j = p - 49.0 * floor(p * ns.z *ns.z);  //  mod(p,N*N)
//
//	vec4 x_ = floor(j * ns.z);
//	vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)
//
//	vec4 x = x_ *ns.x + ns.yyyy;
//	vec4 y = y_ *ns.x + ns.yyyy;
//	vec4 h = 1.0 - abs(x) - abs(y);
//
//	vec4 b0 = vec4( x.xy, y.xy );
//	vec4 b1 = vec4( x.zw, y.zw );
//
//	vec4 s0 = floor(b0)*2.0 + 1.0;
//	vec4 s1 = floor(b1)*2.0 + 1.0;
//	vec4 sh = -step(h, vec4(0.0));
//
//	vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
//	vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;
//
//	vec3 p0 = vec3(a0.xy,h.x);
//	vec3 p1 = vec3(a0.zw,h.y);
//	vec3 p2 = vec3(a1.xy,h.z);
//	vec3 p3 = vec3(a1.zw,h.w);
//
//	//Normalise gradients
//	vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
//	p0 *= norm.x;
//	p1 *= norm.y;
//	p2 *= norm.z;
//	p3 *= norm.w;
//
//	// Mix final noise value
//	vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
//	m = m * m;
//	return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
//				dot(p2,x2), dot(p3,x3) ) );
//}
//
