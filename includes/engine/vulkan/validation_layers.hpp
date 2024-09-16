#pragma once

#ifndef ENGINE_VULKAN_VALIDATION_LAYERS_HEADER
#define ENGINE_VULKAN_VALIDATION_LAYERS_HEADER

#if defined(ENGINE_VL_DEBUG)

#include "engine/vk/array.hpp"
#include "engine/vk/shared.hpp"
#include "engine/vk/typedefs.hpp"
#include "engine/vk/destroy.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- V A L I D A T I O N  L A Y E R S ------------------------------------

	class validation_layers final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::validation_layers;


		public:

			// -- public static methods ---------------------------------------

			/* layers */
			static constexpr auto layers(void) -> vk::array<const char*, 4U> {

				// return validation layers
				return vk::array<const char*, 4U> {
					"VK_LAYER_KHRONOS_validation",
					"VK_LAYER_KHRONOS_profiles",
					"VK_LAYER_KHRONOS_synchronization2",
					"VK_LAYER_KHRONOS_shader_object"
					/*
					"VK_LAYER_LUNARG_api_dump",
					*/
				};
			}

			/* properties */
			static auto properties(void) -> vk::vector<vk::layer_properties> {
				return vk::enumerate_instance_layer_properties();
			}

	}; // class validation_layers

} // namespace vulkan

#endif // ENGINE_VL_DEBUG

#endif // ENGINE_VULKAN_VALIDATION_LAYERS_HEADER
