#ifndef wavelet_shader
#define wavelet_shader

#include "random.glsl"


mat2 rotate2d(const in float r){
	float c = cos(r);
	float s = sin(r);
	return mat2(c, s, -s, c);
}


float wavelet(vec2 p, float phase, float k) {
	float d = 0.0, s = 1.0, m=0.0, a = 0.0;
	for (float i = 0.0; i < 4.0; i++) {
		vec2 q = p*s;
		a = random(floor(q)) * 1e3;
#ifdef WAVELET_VORTICITY
		a += phase * random(floor(q)) * WAVELET_VORTICITY;
#endif
		q = (fract(q) - 0.5) * rotate2d(a);
		d += sin(q.x * 10.0 + phase) * smoothstep(.25, 0.0, dot(q,q)) / s;
		p = p * mat2(0.54,-0.84, 0.84, 0.54) + i;
		m += 1.0 / s;
		s *= k; 
	}
	return d / m;
}

float wavelet(vec3 p, float k) {
	return wavelet(p.xy, p.z, k);
}

float wavelet(vec3 p) {
	return wavelet(p, 1.24);
}

float wavelet(vec2 p, float phase) {
	return wavelet(p, phase, 1.24);
}

float wavelet(vec2 p) {
	return wavelet(p, 0.0, 1.24);
}

#endif // wavelet_shader
