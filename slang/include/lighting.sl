
struct phong {

	/* specular */
	private float _value;


	property float specular {
		get {
			return _value;
		}
	}

	// constructor
	__init( const float3 normal,
			const float3 light_direction,
			const float3 view_direction,
			const float shininess) {

		// compute reflection direction
		float3 reflect_direction = reflect(-light_direction, normal);

		// compute specular angle
		float specular_angle = max(dot(reflect_direction, view_direction), 0.0);

		// compute specular value
		_value = pow(specular_angle, shininess);
	}
}

struct lambert {

	/* diffuse */
	float diffuse;

	__init(const float3 normal, const float3 light_direction) {
		diffuse = max(dot(normal, light_direction), 0.0);
	}
};


