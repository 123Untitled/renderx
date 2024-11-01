#ifndef worley_shader
#define worley_shader

#include "random.glsl"

#define WORLEY_JITTER 0.1

float dist_euclidean(vec2 a, vec2 b) { return distance(a, b); }
float dist_euclidean(vec3 a, vec3 b) { return distance(a, b); }
float dist_euclidean(vec4 a, vec4 b) { return distance(a, b); }


vec2 worley2(const vec3 p) {
	vec3 n = floor( p );
	vec3 f = fract( p );

	float distF1 = 1.0;
	float distF2 = 1.0;
	vec3 off1 = vec3(0.0);
	vec3 pos1 = vec3(0.0);
	vec3 off2 = vec3(0.0);
	vec3 pos2 = vec3(0.0);
	for( int k = -1; k <= 1; k++ ) {
		for( int j= -1; j <= 1; j++ ) {
			for( int i=-1; i <= 1; i++ ) {	
				vec3  g = vec3(i,j,k);
				vec3  o = random3( n + g ) * WORLEY_JITTER;
				vec3  p = g + o;
				float d = dist_euclidean(p, f);
				if (d < distF1) {
					distF2 = distF1;
					distF1 = d;
					off2 = off1;
					off1 = g;
					pos2 = pos1;
					pos1 = p;
				}
				else if (d < distF2) {
					distF2 = d;
					off2 = g;
					pos2 = p;
				}
			}
		}
	}

	return vec2(distF1, distF2);
}

float worley(const vec3 p){
	return 1.0 - worley2(p).x;
}

#endif // worley_shader
