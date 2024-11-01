#ifndef ___RENDERX_MESH___
#define ___RENDERX_MESH___

#include "ve/vulkan/vertex_buffer.hpp"
#include "ve/vulkan/index_buffer.hpp"

//#include "ve/shapes/cuboid.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vulkan/command_buffer.hpp"
#include "ve/vulkan/allocator.hpp"

#include <map>
#include <string_view>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- M E S H -------------------------------------------------------------

	class mesh final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::mesh;


			// -- private members ---------------------------------------------

			/* vertex buffer */
			vulkan::vertex_buffer _vertices;

			/* index buffer */
			vulkan::index_buffer _indices;



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			mesh(void) noexcept = default;

			/* vertices / indices constructor */
			template <typename ___type, typename... ___params>
			mesh(const std::vector<ve::vert3x>& vertices, const std::vector<___type>& indices)
			//mesh(const std::vector<ve::vertex<___params...>>& vertices, const std::vector<___type>& indices)
			: _vertices{vertices}, _indices{indices} {
			}

			/* deleted copy constructor */
			mesh(const ___self&) = delete;

			/* move constructor */
			mesh(___self&&) noexcept = default;

			/* destructor */
			~mesh(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public methods ----------------------------------------------

			/* draw */
			template <typename ___tb, typename ___constants>
			auto draw(const vulkan::command_buffer& encoder, const ___constants& constants) const -> void {

				encoder.bind_vertex_buffer(_vertices);
				encoder.bind_index_buffer(_indices);
				encoder.push_constants(constants);
				encoder.draw_indexed(_indices.count());
			}


			// -- public accessors --------------------------------------------

			/* vertices */
			auto vertices(void) const noexcept -> const vulkan::vertex_buffer& {
				return _vertices;
			}

			/* indices */
			auto indices(void) const noexcept -> const vulkan::index_buffer& {
				return _indices;
			}


	}; // class mesh

} // namespace rx

#endif // ___RENDERX_MESH___
