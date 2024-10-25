#ifndef ___RENDERX_GEOMETRY_MESH_LIBRARY___
#define ___RENDERX_GEOMETRY_MESH_LIBRARY___

#include "ve/containers/static_map.hpp"
#include "ve/mesh.hpp"
#include "ve/shapes/cuboid.hpp"
#include "ve/geometry/icosphere.hpp"


// -- R E N D E R X  N A M E S P A C E ----------------------------------------

namespace rx {


	// -- M E S H  L I B R A R Y ----------------------------------------------

	class mesh_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::mesh_library;

			/* mesh map */
			using ___map = ve::static_map<ve::mesh, "icosphere", "fibonacci_sphere">;


			// -- private members ---------------------------------------------

			/* mesh map */
			___map _meshes;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> ___self& {
				static ___self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			mesh_library(void)
			: _meshes{ve::make_icosphere(), ve::make_fibonacci_sphere()} {
			}

			/* deleted copy constructor */
			mesh_library(const ___self&) = delete;

			/* deleted move constructor */
			mesh_library(___self&&) = delete;

			/* destructor */
			~mesh_library(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* get */
			template <ve::literal key>
			static auto get(void) -> const ve::mesh& {
				return ___self::_shared()._meshes.template get<key>();
			}


	}; // class mesh_library

} // namespace rx

#endif // ___RENDERX_GEOMETRY_MESH_LIBRARY___
