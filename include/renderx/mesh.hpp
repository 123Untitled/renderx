#ifndef ___RENDERX_MESH___
#define ___RENDERX_MESH___

#include "renderx/vulkan/vertex_buffer.hpp"
#include "renderx/vulkan/index_buffer.hpp"
#include "renderx/shapes/cuboid.hpp"
#include "renderx/vertex/vertex.hpp"
#include "renderx/vulkan/command_buffer.hpp"

#include <map>
#include <string_view>


// -- R X ---------------------------------------------------------------------

namespace rx {


	// -- M E S H -------------------------------------------------------------

	class mesh final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::mesh;


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
			mesh(const vk::vector<engine::vertex<___params...>>& vertices, const vk::vector<___type>& indices)
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
			auto draw(const vulkan::command_buffer<___tb>& encoder, const ___constants& constants) const -> void {

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


	// -- M E S H  L I B R A R Y ----------------------------------------------

	class mesh_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::mesh_library;

			/* mesh map */
			using ___map = std::map<std::string_view, rx::mesh>;


			// -- private members ---------------------------------------------

			/* mesh map */
			___map _meshes;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			mesh_library(void)
			: _meshes{} {

				const auto cube = rx::cube();


			}

	}; // class mesh_library




} // namespace rx

#endif // ___RENDERX_MESH___
