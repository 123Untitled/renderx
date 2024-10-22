#ifndef ___RENDERX_SHAPES_CUBOID___
#define ___RENDERX_SHAPES_CUBOID___

#include "ve/mesh.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vertex/position.hpp"

#include "ve/obj_parser.hpp"

#include <vector>
#include <iostream>
#include <string>


// -- R X ---------------------------------------------------------------------

namespace rx {

	namespace impl {
		using vertex = ve::vertex<vx::float3, vx::float3>;
		using package = std::pair<vk::vector<vertex>, vk::vector<vk::u16>>;
	}

	inline auto cube(void) -> ve::mesh {


		std::vector<ve::vert3x> vtxs;
		std::vector<vk::u16> idxs;

		const float r = 0.0f;
		const float g = 1.0f;
		const float b = 0.0f;


		// -- vertices --------------------------------------------------------

		// front
		//vtxs.emplace_back(-1.0f, +1.0f, -1.0f);
		//vtxs.emplace_back(-1.0f, -1.0f, -1.0f);
		//vtxs.emplace_back(+1.0f, -1.0f, -1.0f);
		//vtxs.emplace_back(+1.0f, +1.0f, -1.0f);
		//vtxs.emplace_back(-1.0f, +1.0f, +1.0f);
		//vtxs.emplace_back(-1.0f, -1.0f, +1.0f);
		//vtxs.emplace_back(+1.0f, -1.0f, +1.0f);
		//vtxs.emplace_back(+1.0f, +1.0f, +1.0f);


		// -- indexes ---------------------------------------------------------

		// front
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(3);

		idxs.push_back(3);
		idxs.push_back(1);
		idxs.push_back(2);

		// back
		idxs.push_back(7);
		idxs.push_back(6);
		idxs.push_back(4);

		idxs.push_back(4);
		idxs.push_back(6);
		idxs.push_back(5);

		// left
		idxs.push_back(4);
		idxs.push_back(5);
		idxs.push_back(0);

		idxs.push_back(0);
		idxs.push_back(5);
		idxs.push_back(1);

		// right
		idxs.push_back(3);
		idxs.push_back(2);
		idxs.push_back(7);

		idxs.push_back(7);
		idxs.push_back(2);
		idxs.push_back(6);

		// top
		idxs.push_back(1);
		idxs.push_back(5);
		idxs.push_back(2);

		idxs.push_back(2);
		idxs.push_back(5);
		idxs.push_back(6);

		// bottom
		idxs.push_back(0);
		idxs.push_back(7);
		idxs.push_back(4);

		idxs.push_back(0);
		idxs.push_back(3);
		idxs.push_back(7);


		return ve::mesh{vtxs, idxs};
	}

} // namespace rx

#endif // ___RENDERX_SHAPES_CUBOID___
