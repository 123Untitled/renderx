#ifndef ___RENDERX_OBJ_PARSER___
#define ___RENDERX_OBJ_PARSER___

#include "ve/mesh.hpp"
#include "ve/system/open.hpp"
#include "ve/vertex/position.hpp"

#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <map>


// -- R X  N A M E S P A C E --------------------------------------------------

namespace rx {


	// -- O B J  P A R S E R --------------------------------------------------

	//class obj_parser final {
	//
	//
	//	private:
	//
	//		// -- private types -----------------------------------------------
	//
	//		/* self type */
	//		using ___self = rx::obj_parser;
	//
	//
	//	public:
	//
	//
	//		// -- public static methods ---------------------------------------
	//
	//		/* parse */
	//		template <rx::size_t N>
	//		static auto parse(const char (&path)[N]) -> ve::mesh {
	//
	//
	//			std::vector<ve::vert3x> vertices;
	//			std::vector<rx::u32>     indices;
	//
	//			std::vector<vk::array<float, 3U>> positions;
	//			std::vector<vk::array<float, 3U>> normals;
	//			std::vector<vk::array<float, 3U>> uvs;
	//
	//
	//			std::unordered_map<std::string_view, rx::u32> map;
	//
	//			// open the file
	//			std::ifstream file{path};
	//
	//			if (!file.is_open()) {
	//				throw std::runtime_error("rx::obj_parser::parse() failed");
	//			}
	//
	//			std::string line;
	//
	//			// loop over lines
	//			while (std::getline(file, line)) {
	//
	//				std::cout << "line: " << line << std::endl;
	//
	//				// parse the line
	//				std::string_view view{line};
	//
	//				// vertex
	//				if (view.starts_with("v ")) {
	//
	//					// parse vertex
	//					view.remove_prefix(2U);
	//
	//					// parse vertex components
	//					float vx, vy, vz;
	//					std::sscanf(view.data(), "%f %f %f", &vx, &vy, &vz);
	//
	//					// add vertex
	//					positions.emplace_back(vk::array<float, 3U>{vx, vy, vz});
	//				}
	//
	//				// normal
	//				else if (view.starts_with("vn ")) {
	//
	//					// parse face
	//					view.remove_prefix(3U);
	//
	//					// parse face components
	//					float nx, ny, nz;
	//					std::sscanf(view.data(), "%f %f %f", &nx, &ny, &nz);
	//
	//					// add normal
	//					normals.emplace_back(vk::array<float, 3U>{nx, ny, nz});
	//				}
	//
	//				// uv
	//				else if (view.starts_with("vt ")) {
	//
	//					// parse uv
	//					view.remove_prefix(3U);
	//
	//					// parse uv components
	//					float u, v;
	//					std::sscanf(view.data(), "%f %f", &u, &v);
	//
	//					// add uv
	//					uvs.emplace_back(vk::array<float, 3U>{u, v, 0.0F});
	//				}
	//
	//				// face
	//				else if (view.starts_with("f ")) {
	//
	//					// parse face
	//					view.remove_prefix(2U);
	//
	//					// split face
	//					std::vector<std::string_view> tokens;
	//
	//					while (true) {
	//
	//						// find the next space
	//						auto pos = view.find_first_of(' ');
	//
	//						if (pos != std::string_view::npos) {
	//							// add token
	//							tokens.emplace_back(view.substr(0U, pos));
	//							// remove token
	//							view.remove_prefix(pos + 1U);
	//						}
	//						else {
	//							// add token
	//							tokens.emplace_back(view);
	//							break;
	//						}
	//					}
	//
	//					for (const auto& token : tokens) {
	//
	//						if (map.contains(token)) {
	//
	//							// add index
	//							indices.emplace_back(map[token]);
	//
	//						}
	//						else {
	//
	//							// parse face components
	//							rx::u32 vi, ni, ui;
	//							std::sscanf(token.data(), "%d/%d/%d", &vi, &ni, &ui);
	//
	//							// get position
	//							auto& position = positions[vi - 1U];
	//							// get normal
	//							auto& normal = normals[ni - 1U];
	//							// get uv
	//							auto& uv = uvs[ui - 1U];
	//
	//							// add vertex
	//							//vertices.emplace_back(
	//							//	position[0U], position[1U], position[2U],
	//							//	normal[0U], normal[1U], normal[2U],
	//							//	uv[0U], uv[1U]
	//							//);
	//
	//							// add index
	//							indices.emplace_back(static_cast<rx::u32>(vertices.size() - 1U));
	//
	//							// add to map
	//							map[token] = static_cast<rx::u32>(vertices.size() - 1U);
	//
	//						}
	//					}
	//				}
	//			}
	//
	//
	//			for (auto& vertex : vertices) {
	//				//std::cout << "x: " << vertex.x << " y: " << vertex.y << " z: " << vertex.z << std::endl;
	//			}
	//
	//			for (auto& index : indices) {
	//				std::cout << "index: " << index << std::endl;
	//			}
	//
	//
	//			//return rx::mesh{};
	//			return ve::mesh{vertices, indices};
	//		}
	//
	//
	//}; // class ObjParser

} // namespace rx

#endif // ___RENDERX_OBJ_PARSER___
