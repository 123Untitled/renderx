
// slang vertex shader before tessellation (just pass through)

namespace ve {

	struct vertex_in {
		[[vk::location(0)]] float3 position : POSITION;
		[[vk::location(1)]] float3 normal : NORMAL;
		[[vk::location(2)]] float2 uv : TEXCOORD;
	};

	struct vertex_out {
		float3 position : POSITION;
		float3 normal : NORMAL;
		float2 uv : TEXCOORD;
	};
}


// -- entrypoint --------------------------------------------------------------

[shader("vertex")]
ve::vertex_out main(const ve::vertex_in input) {

	// pass through data
	return ve::vertex_out(input.position, input.normal, input.uv);
}
