/*****************************************************************************/
/*                                                                           */
/*      dMP dMP .aMMMb  dMP dMMMMb                                           */
/*     dMP dMP dMP"dMP amr dMP VMP                                           */
/*    dMP dMP dMP dMP dMP dMP dMP                                            */
/*    YMvAP  dMP aMP dMP dMP.aMP                                             */
/*     VP    VMMMP  dMP dMMMMP                                               */
/*                                                                           */
/*       dMMMMMP dMMMMb   aMMMMP dMP dMMMMb  dMMMMMP                         */
/*      dMP     dMP dMP dMP     amr dMP dMP dMP                              */
/*     dMMMP   dMP dMP dMP MMP dMP dMP dMP dMMMP                             */
/*    dMP     dMP dMP dMP.dMP dMP dMP dMP dMP                                */
/*   dMMMMMP dMP dMP  VMMMP" dMP dMP dMP dMMMMMP                             */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ve_geometry_icosphere___
#define ___ve_geometry_icosphere___

#include "ve/math/sqrt.hpp"
#include "ve/math/pow.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/mesh.hpp"


#include <unordered_map>
#include <map>

// Fonction de hash pour std::pair (déjà définie ci-dessus)
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- I C O S P H E R E ---------------------------------------------------

	class icosphere final {



		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::icosphere;


			// -- private members ---------------------------------------------

			/* vertices */
			std::vector<ve::vert3x> _vertices;

			/* indices */
			std::vector<::uint32_t> _indices;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			icosphere(void) {

				{
				// 1.618033988749895 (golden ratio)
				//constexpr float v = (1.0f + ve::sqrt_compile_time(5.0f)) / 2.0f;
				constexpr float v = 1.618033988749895f;

				// +1 for golden icosahedron

				constexpr float L = 1.0f;
				constexpr float l = L / v;



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


				// -- indices -------------------------------------------------

				// 20 triangles
				_indices = {

					// -------------------
					6,  9,  4,
					3,  9,  6,
					3, 11,  9,
					7, 11,  3,
					5, 11,  7,
					1, 11,  5,
					9, 11,  1,
					4,  9,  1,
					// -------------------
					2,  3,  6,
					2,  7,  3,
					// -------------------
					0,  1,  5,
					4,  1,  0,
					// -------------------
					8,  6,  4,
					8,  2,  6,
					10, 2,  8,
					10, 7,  2,
					10, 5,  7,
					10, 0,  5,
					10, 8,  0,
					8,  4,  0  
					// -------------------
				};
				}

				/*
				// 6 vertices
				_vertices = {
					{ 0,  0,  L},  // 0 - sommet supérieur
					{ 0,  0, -L},  // 1 - sommet inférieur
					{ L,  0,  0},  // 2 - à droite
					{-L,  0,  0},  // 3 - à gauche
					{ 0,  L,  0},  // 4 - en haut
					{ 0, -L,  0}   // 5 - en bas
				};

				// 8 triangles
				_indices = {
					// Triangles autour du sommet supérieur (0)
					0, 4, 2,  // 0
					0, 2, 5,  // 1
					0, 5, 3,  // 2
					0, 3, 4,  // 3

					// Triangles autour du sommet inférieur (1)
					1, 2, 4,  // 4
					1, 5, 2,  // 5
					1, 3, 5,  // 6
					1, 4, 3   // 7
				};
				*/





				___self::_subdivide(5);
				___self::_project_onto_sphere();
			}



			/* mesh */
			auto mesh(void) const noexcept -> ve::mesh {
				return ve::mesh{ _vertices, _indices };
			}


		private:

			// -- private types -----------------------------------------------

			/* cache type */
			using ___cache_type = std::unordered_map<std::pair<::uint32_t, ::uint32_t>, ::uint32_t, pair_hash>;



			// -- private methods ---------------------------------------------

			/* midpoint index */
			auto _midpoint_index(___cache_type& cache,
								const ::uint32_t v1,
								const ::uint32_t v2) -> ::uint32_t {

				const std::pair<::uint32_t, ::uint32_t> key = (v1 < v2)
					? std::make_pair(v1, v2)
					: std::make_pair(v2, v1);

				if (const auto it = cache.find(key); it != cache.end()) {
					return it->second;
				}

				const ve::vector3 midpoint = ve::midpoint(_vertices[v1].position,
														  _vertices[v2].position);

				const auto index = static_cast<::uint32_t>(_vertices.size());
				_vertices.emplace_back(midpoint);
				cache[key] = index;

				return index;
			};

			/* subdivide */
			auto _subdivide(const unsigned subdivisions) -> void {

				// compute final number of indices
				const ::size_t _final_indices = 60U * (1U << (subdivisions * 2U));
				// compute final number of vertices
				const ::size_t _final_vertices = 12U + (10U * (ve::pow(4U, subdivisions) - 1));

				// reserve memory
				_vertices.reserve(_final_vertices);
				 _indices.reserve(_final_indices);


				for (unsigned _ = 0U; _ < subdivisions; ++_) {

					std::vector<::uint32_t> new_indices;
					// reserve memory
					new_indices.reserve(_indices.size() * 4U);

					// midpoint cache (avoid creating duplicate vertices)
					___cache_type cache;


					for (::size_t i = 0U; i < _indices.size(); i += 3U) {

						const auto i1 = _indices[i    ];
						const auto i2 = _indices[i + 1];
						const auto i3 = _indices[i + 2];

						const auto m1 = _midpoint_index(cache, i1, i2);
						const auto m2 = _midpoint_index(cache, i2, i3);
						const auto m3 = _midpoint_index(cache, i3, i1);

						new_indices.insert(new_indices.end(), {
							i1, m1, m3,
							i2, m2, m1,
							i3, m3, m2,
							m1, m2, m3
						});
					}

					// assign new indices
					_indices = new_indices;
				}

				// compare final number of vertices
				std::cout << "   final number of vertices: " << _vertices.size() << std::endl;
				std::cout << "expected number of vertices: " << _final_vertices << std::endl;
				std::cout << "   final number of  indices: " << _indices.size() << std::endl;
				std::cout << "expected number of  indices: " << _final_indices << std::endl;
			}


			/* project onto sphere */
			auto _project_onto_sphere(void) noexcept -> void {

				// loop over vertices
				for (auto& vertex : _vertices) {

					// normalize
					vertex.position.normalize();

					// assign normal
					vertex.normal = vertex.position;
				}
			}

			/* recompute normals */
			auto _recompute_normals(void) noexcept -> void {

				// loop over indices
				for (::size_t i = 0U; i < _indices.size(); i += 3U) {

					// get indices
					const auto i1 = _indices[i    ];
					const auto i2 = _indices[i + 1];
					const auto i3 = _indices[i + 2];

					// get positions
					const auto& p1 = _vertices[i1].position;
					const auto& p2 = _vertices[i2].position;
					const auto& p3 = _vertices[i3].position;

					// compute edges
					const auto edge1 = p2 - p1;
					const auto edge2 = p3 - p1;

					// compute normal
					auto cross{ve::cross(edge1, edge2)};
					cross.normalize();

					// assign normals
					_vertices[i1].normal = cross;
					_vertices[i2].normal = cross;
					_vertices[i3].normal = cross;
				}
			}

	}; // class icosphere


	inline auto make_icosphere(void) -> ve::mesh {
		return ve::icosphere{}.mesh();
	}



	class fibonacci_sphere final {

		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::fibonacci_sphere;


			// -- private members ---------------------------------------------

			/* vertices */
			std::vector<ve::vert3x> _vertices;

			/* indices */
			std::vector<::uint32_t> _indices;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			fibonacci_sphere(void) {

				// golden angle (radians)
				constexpr float ga = 2.39996322972865332f;

				// golden angle (degrees)
				constexpr float ga_deg = 137.5077640500378546463487f;

				const ::uint32_t num_points = 10000U;

				// loop over points
				for (::uint32_t i = 0U; i < num_points; ++i) {

					// compute latitude
					//const float lat = 2.0f * (static_cast<float>(i) / static_cast<float>(num_points - 1U)) - 1.0f;
					//const float phi = std::asin(lat);
					//
					//// compute longitude
					//const float theta = ga * static_cast<float>(i);
					//
					//// compute position
					//const ve::vector3 position{
					//	std::cos(theta) * std::cos(phi),
					//	std::sin(theta) * std::cos(phi),
					//	std::sin(phi)
					//};
					//
					//// compute normal
					//const ve::vector3 normal = position;
					//
					//// add vertex
					//_vertices.emplace_back(position, normal);

					// add index
					//_indices.emplace_back(i);


						// Position y des points (de -1 à 1)
						float y = 1.0f - ((float)i / float(num_points - 1)) * 2.0f;
						float radius_circle = std::sqrt(1.0f - y * y);

						// Angle pour la distribution uniforme des points
						float theta = ga * (float)i;

						float x = std::cos(theta) * radius_circle;
						float z = std::sin(theta) * radius_circle;

						_vertices.push_back({x, y, z});
				}

				// La surface est découpée en couches, on lie les points des couches adjacentes
				for (uint32_t i = 0; i < num_points - 1; ++i) {
					uint32_t next = i + 1;

					// On crée des triangles avec les voisins
					if (i < num_points - 2) {
						_indices.push_back(i);
						_indices.push_back(next);
						_indices.push_back((i + 2) % num_points); // Connecter les points proches
					}
				}


			}

			/* mesh */
			auto mesh(void) const noexcept -> ve::mesh {
				return ve::mesh{ _vertices, _indices };
			}


	}; // class fibonacci_sphere

	/* make fibonacci sphere */
	inline auto make_fibonacci_sphere(void) -> ve::mesh {
		return ve::fibonacci_sphere{}.mesh();
	}




} // namespace ve





#endif // ___ve_geometry_icosphere___
