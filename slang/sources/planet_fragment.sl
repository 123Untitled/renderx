#include "../include/lighting.sl"

namespace ve {

	struct domain_out {
		float4 position : SV_Position;
		float3 normal : NORMAL;
		float2 texcoord : TEXCOORD;
		//float3 view_direction;
	};

	struct pixel_out {
		float4 color : SV_Target;
	};
}



[shader("pixel")]
ve::pixel_out main(ve::domain_out input) {

	// interpolate position + normal to create a color
	float3 color = input.normal;
	
	return ve::pixel_out(float4(color, 1.0));
}
