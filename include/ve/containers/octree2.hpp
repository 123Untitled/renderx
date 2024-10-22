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

#ifndef ___void_engine_octree___
#define ___void_engine_octree___


#include <simd/simd.h>

namespace ve {
	using vec3f = simd::float3;
}




// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- O C T R E E ---------------------------------------------------------

	template <typename ___type>
	class octree final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::octree<___type>;


			// -- private constants -------------------------------------------



			// -- forward declarations ----------------------------------------

			/* octree node */
			class node;




			// -- private members ---------------------------------------------

			/* root */
			node* _root;


			// -- private classes ---------------------------------------------

			/* octree node */
			class node final {

				private:

					// -- private members -------------------------------------

					/* childs */
					node* _childs[8U];

					/* parent */
					node* _parent;

					/* data */
					___type data;


				public:

					// -- public lifecycle ------------------------------------

					/* default constructor */
					node(void) noexcept
					: _parent{nullptr} , _childs{}, data{} {
					}


					// -- public accessors ------------------------------------

					/* has childs */
					auto has_childs(void) const noexcept -> bool {

						// loop over childs
						for (auto i = 0U; i < 8U; ++i) {

							if (_childs[i] != nullptr)
								return true;
						}
						return false;
					}

					/* child */
					auto child(const unsigned i) -> node* {
						return _childs[i];
					}

			};
			
			auto get_node(node* n, int x, int y, int z, int e) -> node* {

				int e0=30;

				// while there are childs and depth is not reached
				while (n->has_childs() && e0 > e) {

					// go deeper
					--e0;

					// get child
					n = n->child(((x >> e0) & 1U)
								  + (((y >> e0) & 1U) << 1U)
								  + (((z >> e0) & 1U) << 2U)
							);
				}

				return n;
			}

			auto insert(const ve::vec3f& p, const ___type& data) -> void {

				// get cube
				auto n = get_cube(_root, p.x, p.y, p.z, 30);

				// set data
				n->data = data;
			}





			enum : unsigned {
				// 32 bits max exponent (31 is the sign bit, 32 is out of range)
				EMAX = 31U,
				OCT_MASQ = ((1U << EMAX) - 1U)
			};


			union uint_float {
				unsigned int i;
				float        f;
			};


			static auto find_exposant(const float valeur) noexcept -> unsigned {
				union uint_float un;

				// _scale is 1.0f / scale
				// scale is the size of the octree

				float _scale = 0.0f; // will be set to 1.0f / scale
				un.f = valeur * _scale;

				return (un.i >> 23U) - 126U;
			}


	}; // class octree

} // namespace ve


//enum class octant : unsigned {
//	O1 = 0b00000001,
//	O2 = 0b00000010,
//	O3 = 0b00000100,
//	O4 = 0b00001000,
//	O5 = 0b00010000,
//	O6 = 0b00100000,
//	O7 = 0b01000000,
//	O8 = 0b10000000,
//};

#endif // ___void_engine_octree___
