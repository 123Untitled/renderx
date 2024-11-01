#ifndef voronoise_shader
#define voronoise_shader


#include "random.glsl"


float voronoise( in vec2 p, in float u, float v) {
	float k = 1.0+63.0*pow(1.0-v,6.0);
	vec2 i = floor(p);
	vec2 f = fract(p);

	vec2 a = vec2(0.0, 0.0);

	vec2 g = vec2(-2.0);
	for ( g.y = -2.0; g.y <= 2.0; g.y++ ) {
		for ( g.x = -2.0; g.x <= 2.0; g.x++ ) {

			vec3  o = random3(i + g) * vec3(u, u, 1.0);
			vec2  d = g - f + o.xy;
			float w = pow(1.0-smoothstep(0.0,1.414, length(d)), k );
			a += vec2(o.z*w,w);
		}
	}

	return a.x/a.y;
}



float voronoise(const vec3 p, const float u, const float v)  {

	float k = 1.0 + 63.0 * pow(1.0 - v,6.0);
	vec3 i = floor(p);
	vec3 f = fract(p);

	float s = 1.0 + 31.0 * v;
	vec2 a = vec2(0.0, 0.0);


	vec3 g = vec3(-2.0);

	for (g.z = -2.0; g.z <= 2.0; ++g.z) {

		for (g.y = -2.0; g.y <= 2.0; ++g.y) {

			for (g.x = -2.0; g.x <= 2.0; ++g.x) {

				vec3 o = random3(i + g) * vec3(u, u, 1.);
				vec3 d = g - f + o + 0.5;
				float w = pow(1.0 - smoothstep(0.0, 1.414, length(d)), k);
				a += vec2(o.z*w, w);
			}
		}
	}

	return a.x / a.y;
}

#endif // voronoise_shader
