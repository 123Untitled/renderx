
namespace test {
	float3 fresnel(float3 normal, float3 view, float3 color, float power) {
		return color + (1.0 - color) * pow(1.0 - dot(normal, view), power);
	}
}
// alias declarations
typedef float my_float;

struct my_type {
}

struct my_struct {

	my_type t;
	var i: int;

	__init(const int n) {
		i = n;
	}
}

[shader("vertex")]
void main(void) {

	my_struct s = my_struct(23);

	vector<float, 4> v4;
	test::fresnel(float3(0.0, 0.0, 0.0), float3(0.0, 0.0, 0.0), float3(0.0, 0.0, 0.0), 0.0);
}
