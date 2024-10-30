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

#ifndef ___ve_geometry_icotree___
#define ___ve_geometry_icotree___

#include "ve/math/sqrt.hpp"
#include "ve/math/pow.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/mesh.hpp"
//#include "ve/structures/vector3.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

//namespace ve {
//
//
//	class triangle final {
//
//
//		private:
//
//			// -- private types -----------------------------------------------
//
//			/* self type */
//			using ___self = ve::triangle;
//
//
//		public:
//
//			// -- public members ----------------------------------------------
//
//			/* indices */
//			::uint32_t i1, i2, i3;
//
//
//		public:
//
//			// -- public lifecycle --------------------------------------------
//
//			/* default constructor */
//			constexpr triangle(void) noexcept = default;
//
//			/* constructor */
//			constexpr triangle(const ::uint32_t I1,
//					 const ::uint32_t I2,
//					 const ::uint32_t I3)
//			: i1{I1}, i2{I2}, i3{I3} {
//			}
//
//
//			/* copy constructor */
//			constexpr triangle(const ___self&) noexcept = default;
//
//			/* move constructor */
//			constexpr triangle(___self&&) noexcept = default;
//
//			/* destructor */
//			~triangle(void) noexcept = default;
//
//
//			// -- public assignment operators ---------------------------------
//
//			/* copy assignment operator */
//			constexpr auto operator=(const ___self&) noexcept -> ___self& = default;
//
//			/* move assignment operator */
//			constexpr auto operator=(___self&&) noexcept -> ___self& = default;
//
//
//	}; // class triangle
//
//
//
//	class icotree final {
//
//		// implementation of octree for icosphere
//
//		private:
//
//			// -- private types -----------------------------------------------
//
//			/* self type */
//			using ___self = ve::icotree;
//
//
//			// -- forward declarations ----------------------------------------
//
//			struct ___node;
//
//
//			/* root node */
//			struct ___root final {
//
//
//				// -- members -------------------------------------------------
//
//				/* triangles */
//				std::array<ve::triangle, 20U> triangles;
//
//				/* children */
//				std::array<std::unique_ptr<___node>, 20U> children;
//
//
//				___root(void) noexcept
//				: triangles{ve::triangle{6,  9,  4},
//										{3,  9,  6},
//										{3, 11,  9},
//										{7, 11,  3},
//										{5, 11,  7},
//										{1, 11,  5},
//										{9, 11,  1},
//										{4,  9,  1},
//										{2,  3,  6},
//										{2,  7,  3},
//										{0,  1,  5},
//										{4,  1,  0},
//										{8,  6,  4},
//										{8,  2,  6},
//										{10, 2,  8},
//										{10, 7,  2},
//										{10, 5,  7},
//										{10, 0,  5},
//										{10, 8,  0},
//										{8,  4,  0}}, children{} {
//				}
//
//			};
//
//			/* node type */
//			struct ___node final {
//
//				// -- members -------------------------------------------------
//
//				/* children */
//				std::array<std::unique_ptr<___node>, 4U> children;
//
//				/* triangles */
//				ve::triangle triangles[4U];
//
//			};
//
//
//			/* root node */
//			___root _root;
//
//			/* vertices */
//			std::vector<ve::vert3x> _vertices;
//
//
//			// -- private constants -------------------------------------------
//
//			/* L */
//			static constexpr float L = 1.0f;
//
//			/* l */
//			static constexpr float l = L / 1.618033988749895f;
//
//
//		public:
//
//			// -- public lifecycle --------------------------------------------
//
//			/* default constructor */
//			icotree(void)
//			: _root{}, _vertices{{-L, -l,  0},
//								 {-L,  l,  0},
//								 { L, -l,  0},
//								 { L,  l,  0},
//								 {-l,  0, -L},
//								 {-l,  0,  L},
//								 { l,  0, -L},
//								 { l,  0,  L},
//								 { 0, -L, -l},
//								 { 0,  L, -l},
//								 { 0, -L,  l},
//								 { 0,  L,  l}} {
//			}
//
//
//			auto subdivide(const unsigned subdivisions) -> void {
//
//
//				// loop over triangles
//				for (::uint32_t i = 0U; i < 20U; ++i) {
//
//					//std::unique_ptr<___node>& node = _root.children[i];
//					//std::stack<___node*> stack;
//
//
//
//					// loop over subdivisions
//					for (unsigned _ = 0U; _ < subdivisions; ++_) {
//
//
//
//
//					}
//				}
//			}
//
//
//	}; // class icotree
//
//
//} // namespace ve

#endif // ___ve_geometry_icotree___
