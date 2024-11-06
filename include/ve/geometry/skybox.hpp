#ifndef ___ve_mesh_skybox___
#define ___ve_mesh_skybox___

#include "ve/mesh.hpp"
#include "ve/vertex/vertex.hpp"
#include <vector>

#include <cmath>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {

	template <typename T>
	constexpr T pi = static_cast<T>(3.141592653589793238462643383279502884197169399375105820974944592307816406286);

	template <typename T>
	constexpr T pi2 = static_cast<T>(6.283185307179586476925286766559005768394338798750211641949889184615632812572);



	struct my_vec {

		union {

			struct {
				float x, y, z;
			};

			struct {
				float r, g, b;
			};

			struct {
				float u, v;
			};

			float data[3];
		};
	};

	inline void testunion() {

		my_vec v;

		v.x = 1.0f;

		v.r = 0.0f;

		v.u = 0.0f;
	}



	// -- S K Y B O X ---------------------------------------------------------

	class mesh::skybox final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::mesh::skybox;

			using vec3 = ve::vertex_with_uv::vector3;
			using vec2 = ve::vertex_with_uv::vector2;


			// -- private members ---------------------------------------------

			std::vector<ve::vertex_with_uv> _vertices;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			skybox(void) {

				constexpr float L = 1.0f;
				constexpr float l = L / 1.618033988749895f;

				// -- vertices ------------------------------------------------

				// 12 vertices
				_vertices = {
					// X y RECTANGLE
					{-L, -l,  0}, // 0
					{-L,  l,  0}, // 1
					{ L, -l,  0}, // 2
					{ L,  l,  0}, // 3
					// Z x RECTANGLE
					{-l,  0, -L}, // 4
					{-l,  0,  L}, // 5
					{ l,  0, -L}, // 6
					{ l,  0,  L}, // 7
					// Y z RECTANGLE
					{ 0, -L, -l}, // 8
					{ 0,  L, -l}, // 9
					{ 0, -L,  l}, // 10
					{ 0,  L,  l}  // 11
				};


				for (auto& vertex : _vertices) {
					vertex.uv = _compute_uv(vertex.position); }
			}


			static auto _compute_uv(const vec3& vec) noexcept -> vec2 {

				// normalize
				const auto n = ve::normalize(vec);

				// get longitude and latitude
				const auto lon = std::atan2(n.z(), n.x());
				const auto lat = std::asin(n.y());

				ve::vec2f uv;

				// convert to uv
				uv.u((lon / pi2<float>) + 0.5f);
				uv.v((lat / pi <float>) + 0.5f);

				return uv;
			}


			//auto to_vertex(void) const -> std::vector<ve::vertex<ve::vec3f, ve::vec2f>> {
			//	if (_vertices.size() != _uvs.size())
			//		throw;
			//
			//	std::vector<ve::vertex<ve::vec3f, ve::vec2f>> vec;
			//
			//	for (std::size_t i = 0U; i < _vertices.size(); ++i) {
			//
			//		vec.emplace_back(ve::vec3f{_vertices[i]},
			//						 ve::vec2f{_uvs[i]});
			//	}
			//
			//	return vec;
			//}

	}; // class skybox

} // namespace ve

#endif // ___ve_mesh_skybox___
