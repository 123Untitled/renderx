#version 450

const uint _perms[256U] = {
	151, 160, 137, 91, 90, 15,
	131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
	190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
	77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
	102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
	135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
	5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
	223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
	129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
	251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
	49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
	138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};


// -- private static methods --------------------------------------

int _floor(const float fp) {
	const int i = int(fp);
	return (fp < i) ? (i - 1) : (i);
}


int _hash(const int i) {
	return int(_perms[i & 255U]);
}

float _gradient(const int hash,
					   const float x,
					   const float y,
					   const float z) {
	// convert low 4 bits of hash code into 12 simple
	const int h = hash & 15;
	// gradient directions, and compute dot product.
	const float u = h < 8 ? x : y;
	// fix repeats at h = 12 to 15
	const float v = (h < 4) ? y : ((h == 12 || h == 14) ? x : z);

	return (((h & 1) != 0) ? -u : u)
		+ (((h & 2) != 0) ? -v : v);
}


// -- public static methods ---------------------------------------

float simplex(const vec3 vec) {

	const float x = vec.x;
	const float y = vec.y;
	const float z = vec.z;


	// Noise contributions from the four corners
	float n0, n1, n2, n3;

	// skewing / unskewing factors for 3d
	float F3 = 1.0f / 3.0f;
	float G3 = 1.0f / 6.0f;

	// Skew the input space to determine which simplex cell we're in
	float s = (x + y + z) * F3; // Very nice and simple skew factor for 3D
	int i = _floor(x + s);
	int j = _floor(y + s);
	int k = _floor(z + s);
	float t = (i + j + k) * G3;
	float X0 = i - t; // Unskew the cell origin back to (x,y,z) space
	float Y0 = j - t;
	float Z0 = k - t;
	float x0 = x - X0; // The x,y,z distances from the cell origin
	float y0 = y - Y0;
	float z0 = z - Z0;

	// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
	// Determine which simplex we are in.
	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
	if (x0 >= y0) {
		if (y0 >= z0) {
			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0; // X Y Z order
		} else if (x0 >= z0) {
			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1; // X Z Y order
		} else {
			i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1; // Z X Y order
		}
	} else { // x0<y0
		if (y0 < z0) {
			i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1; // Z Y X order
		} else if (x0 < z0) {
			i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1; // Y Z X order
		} else {
			i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0; // Y X Z order
		}
	}

	// a step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
	// c = 1/6.
	float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
	float y1 = y0 - j1 + G3;
	float z1 = z0 - k1 + G3;
	float x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
	float y2 = y0 - j2 + 2.0f * G3;
	float z2 = z0 - k2 + 2.0f * G3;
	float x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
	float y3 = y0 - 1.0f + 3.0f * G3;
	float z3 = z0 - 1.0f + 3.0f * G3;

	// Work out the hashed gradient indices of the four simplex corners
	int gi0 = _hash(i + _hash(j + _hash(k)));
	int gi1 = _hash(i + i1 + _hash(j + j1 + _hash(k + k1)));
	int gi2 = _hash(i + i2 + _hash(j + j2 + _hash(k + k2)));
	int gi3 = _hash(i + 1 + _hash(j + 1 + _hash(k + 1)));

	// Calculate the contribution from the four corners
	float t0 = 0.6f - x0*x0 - y0*y0 - z0*z0;
	if (t0 < 0) {
		n0 = 0.0;
	} else {
		t0 *= t0;
		n0 = t0 * t0 * _gradient(gi0, x0, y0, z0);
	}
	float t1 = 0.6f - x1*x1 - y1*y1 - z1*z1;
	if (t1 < 0) {
		n1 = 0.0;
	} else {
		t1 *= t1;
		n1 = t1 * t1 * _gradient(gi1, x1, y1, z1);
	}
	float t2 = 0.6f - x2*x2 - y2*y2 - z2*z2;
	if (t2 < 0) {
		n2 = 0.0;
	} else {
		t2 *= t2;
		n2 = t2 * t2 * _gradient(gi2, x2, y2, z2);
	}
	float t3 = 0.6f - x3*x3 - y3*y3 - z3*z3;
	if (t3 < 0) {
		n3 = 0.0;
	} else {
		t3 *= t3;
		n3 = t3 * t3 * _gradient(gi3, x3, y3, z3);
	}
	// Add contributions from each corner to get the final noise value.
	// The result is scaled to stay just inside [-1,1]
	return 32.0f*(n0 + n1 + n2 + n3);
}

float hash(vec3 p) {
	return fract(sin(dot(p ,vec3(127.1,311.7, 74.7))) * 43758.5453123);
}

float simple_noise(vec3 p) {
	vec3 i = floor(p);
	vec3 f = fract(p);
	f = f * f * (3.0 - 2.0 * f);

	return mix(mix(mix(hash(i + vec3(0,0,0)), hash(i + vec3(1,0,0)), f.x),
				mix(hash(i + vec3(0,1,0)), hash(i + vec3(1,1,0)), f.x), f.y),
			mix(mix(hash(i + vec3(0,0,1)), hash(i + vec3(1,0,1)), f.x),
				mix(hash(i + vec3(0,1,1)), hash(i + vec3(1,1,1)), f.x), f.y), f.z);
}


float fractal(const uint octaves,
			  float amplitude,
			  float frequency,
			  const float lacunarity,
			  const float persistence,
			  const vec3 vec) {

	// lacunarity: the rate at which the frequency increases for each successive octave
	// persistence: the rate at which the amplitude changes for each successive octave

	float noise = 0.0f;
	float denom  = 0.0f;
	//float weight = 1.0f;

	// loop over octaves
	for (uint i = 0U; i < octaves; ++i) {

		noise += (simple_noise(vec * frequency) * amplitude /** weight*/);
		denom += amplitude;

		frequency *= lacunarity;
		amplitude *= persistence;
		//weight *= persistence;
	}

	return (noise / denom);
}




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



// -- O U T P U T S -----------------------------------------------------------

layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec3 out_view_direction;
layout(location = 2) out vec3 out_view_position;


void main(void) {


	// retrieve control point position coordinates
	vec3 interpoled_position = (gl_TessCoord.x * gl_in[0].gl_Position.xyz)
							 + (gl_TessCoord.y * gl_in[1].gl_Position.xyz)
							 + (gl_TessCoord.z * gl_in[2].gl_Position.xyz);

	interpoled_position = normalize(interpoled_position);

	const uint octaves = 1U;
	const float amplitude = 0.06f;
	const float frequency = 10.5f;
	const float lacunarity = 1.5f;
	const float persistence = 0.8f;


	// get noise
	//const float noise = fractal(octaves, amplitude, frequency, lacunarity, persistence, interpoled_position);
	const float noise = simplex(interpoled_position * frequency) * amplitude;

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
