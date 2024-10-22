#ifndef ___RENDERX_SHAPES_CUBOID___
#define ___RENDERX_SHAPES_CUBOID___

#include "ve/mesh.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vertex/position.hpp"

#include "ve/obj_parser.hpp"

#include <tiny_obj_loader.h>

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

		//return rx::obj_parser::parse("assets/models/icosasedron.obj");

		// exemple of using tinyobjloader
		std::vector<ve::vert3x> vertices;
		std::vector<rx::u32>     indices;


		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, "assets/models/sphere.obj")) {
			throw std::runtime_error(warn);
		}

		// loop over shapes
		for (const auto& shape : shapes) {

			// get indices
			for (const auto& index : shape.mesh.indices) {

				std::cout << "index: " << index.vertex_index << std::endl;
				indices.push_back((unsigned)index.vertex_index);
			}

			// get vertices
			for (size_t i = 0; i < attrib.vertices.size(); i += 3) {

				//vertices.push_back({
				//	// position
				//	attrib.vertices[i + 0],
				//	attrib.vertices[i + 1],
				//	attrib.vertices[i + 2],
				//	// normal
				//	attrib.normals[i + 0],
				//	attrib.normals[i + 1],
				//	attrib.normals[i + 2],
				//	// uv
				//	attrib.texcoords[i + 0],
				//	attrib.texcoords[i + 1]
				//});
			}

			// get normals


		}

		return ve::mesh{vertices, indices};


		//return rx::obj_parser::parse("assets/models/sphere.obj");
		//return rx::obj_parser::parse("assets/models/icosahedron.obj");


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
