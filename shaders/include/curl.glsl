#ifndef curl_shader
#define curl_shader

vec3 curl(vec3 p) {
	const float e = .1;
	vec3 dx = vec3( e   , 0.0 , 0.0 );
	vec3 dy = vec3( 0.0 , e   , 0.0 );
	vec3 dz = vec3( 0.0 , 0.0 , e   );

	vec3 p_x0 = snoise3( p - dx );
	vec3 p_x1 = snoise3( p + dx );
	vec3 p_y0 = snoise3( p - dy );
	vec3 p_y1 = snoise3( p + dy );
	vec3 p_z0 = snoise3( p - dz );
	vec3 p_z1 = snoise3( p + dz );

	float x = p_y1.z - p_y0.z - p_z1.y + p_z0.y;
	float y = p_z1.x - p_z0.x - p_x1.z + p_x0.z;
	float z = p_x1.y - p_x0.y - p_y1.x + p_y0.x;

	const float divisor = 1.0 / ( 2.0 * e );
#ifndef CURL_UNNORMALIZED
	return normalize( vec3( x , y , z ) * divisor );
#else
	return vec3( x , y , z ) * divisor;
#endif
}

#endif // curl_shader
