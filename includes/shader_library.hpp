#ifndef ENGINE_SHADER_LIBRARY_HPP
#define ENGINE_SHADER_LIBRARY_HPP


#include <vulkan/vulkan.h>

#include "vulkan_shader_module.hpp"
#include <xns>
#include <unordered_map>
#include <map>

//#include "vulkan_logical_device.hpp"

namespace vulkan {
	class logical_device;
}

// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- S H A D E R  L I B R A R Y ------------------------------------------

	class shader_library final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::shader_library;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shader_library(void) noexcept
			: _vmap{}, _fmap{} {}

			/* copy constructor */
			shader_library(const self&) noexcept = default;

			/* move constructor */
			shader_library(self&&) noexcept = default;

			/* destructor */
			~shader_library(void) noexcept = default;



			// -- public modifiers --------------------------------------------

			/* load vertex shader */
			template <xns::basic_string_literal S>
			auto load_vertex(const vk::shared<vk::device>& device) -> void {
				xns::string path;
				//path.append(_root.data(), S.data(), _vext.data());
				//std::cout << path << std::endl;

				//xns::get<S>(_vmap) = vulkan::shader_module{device, path, S};
			}

			/* load fragment shader */
			template <xns::basic_string_literal S>
			auto load_fragment(const vk::shared<vk::device>& device) -> void {

				//std::string path;
				//path.reserve(_root.size() + S.size() + _fext.size());
				//path.append(_root.data(), _root.size());
				//path.append(S.data(), S.size());
				//path.append(_fext.data(), _fext.size());

				//xns::get<S>(_fmap) = vulkan::shader_module{device, path};
			}


		private:

			/* root path */
			static constexpr xns::basic_string_literal _root{"shaders/spirv/"};

			/* vertex extension */
			static constexpr xns::string_view _vext{".vert.spv"};

			/* fragment extension */
			static constexpr xns::string_view _fext{".frag.spv"};




			// -- private types -----------------------------------------------

			/* vertex shader map type */
			using vertex_map_type = xns::literal_map<vulkan::shader_module, "basic">;

			/* fragment shader map type */
			using fragment_map_type = xns::literal_map<vulkan::shader_module, "basic">;


			// -- private members ---------------------------------------------

			/* vertex shaders */
			vertex_map_type _vmap;

			/* fragment shaders */
			fragment_map_type _fmap;


	}; // class shader_library

} // namespace engine

#endif // ENGINE_SHADER_LIBRARY_HPP
