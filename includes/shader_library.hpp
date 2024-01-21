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

	template <xns::basic_string_literal... L>
	class shader_library final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::shader_library<L...>;


			// -- public lifecycle --------------------------------------------

			/* logical device constructor */
			shader_library(const vulkan::logical_device& device)
			:	_vmap{(load_vertex<L>(device))...},
				_fmap{(load_fragment<L>(device))...},
				_device{device} {
			}


			/* destructor */
			~shader_library(void) noexcept = default;



			// -- public modifiers --------------------------------------------

			/* destroy */
			auto destroy(const vulkan::logical_device& ldevice) noexcept -> void {
				// destroy all vertex shaders
				_vmap.for_each([](auto& shader, auto& device) {
					shader.destroy(device);
				}, ldevice);
				// destroy all fragment shaders
				_fmap.for_each([](auto& shader, auto& device) {
					shader.destroy(device);
				}, ldevice);
			}


		private:

			/* root path */
			static constexpr xns::string_view _root{"shaders/spirv/"};

			/* vertex extension */
			static constexpr xns::string_view _vext{".vert.spv"};

			/* fragment extension */
			static constexpr xns::string_view _fext{".frag.spv"};



			template <xns::basic_string_literal S>
			auto load_vertex(const vulkan::logical_device& device) -> vulkan::shader_module {
				std::string path;
				path.reserve(_root.size() + S.size() + _vext.size());
				path.append(_root.data(), _root.size());
				path.append(S.data(), S.size());
				path.append(_vext.data(), _vext.size());

				return vulkan::shader_module{device, path};
			}

			template <xns::basic_string_literal S>
			auto load_fragment(const vulkan::logical_device& device) -> vulkan::shader_module {

				std::string path;
				path.reserve(_root.size() + S.size() + _fext.size());
				path.append(_root.data(), _root.size());
				path.append(S.data(), S.size());
				path.append(_fext.data(), _fext.size());

				return vulkan::shader_module{device, path};
			}

			// -- private types -----------------------------------------------

			/* map type */
			using map_type = xns::literal_map<vulkan::shader_module, L...>;



			// -- private methods ---------------------------------------------



			// -- private members ---------------------------------------------

			/* vertex shaders */
			map_type _vmap;

			/* fragment shaders */
			map_type _fmap;

			/* logical device */
			const vulkan::logical_device& _device;


	}; // class shader_library

} // namespace engine

#endif // ENGINE_SHADER_LIBRARY_HPP
