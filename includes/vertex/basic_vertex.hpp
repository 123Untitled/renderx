/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_BASIC_VERTEX_HPP
#define ENGINE_BASIC_VERTEX_HPP

#include "os.hpp"

#if defined(ENGINE_OS_APPLE)
#include <simd/simd.h>
#endif

#include "vk_typedefs.hpp"
#include <vulkan/vulkan.h>
#include <array>
#include <xns>

// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {

	// -- B A S I C  V E R T E X ------------------------------------------------

	class basic_vertex final {

		private:

			/* position */
			xns::array<float, 3> _position;
			//simd::float3 _position;

			/* color */
			xns::array<float, 4> _color;
			//simd::float4 _color;


		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::basic_vertex;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			basic_vertex(void) noexcept
			: _position{0.0f, 0.0f, 0.0f}, _color{1.0f, 1.0f, 1.0f, 1.0f} {
			}

			/* position and color constructor */
			basic_vertex(const float x, const float y, const float z,
						 const float r, const float g, const float b, const float a) noexcept
			: _position{x, y, z}, _color{r, g, b, a} {
			}

			/* copy constructor */
			basic_vertex(const self& other) noexcept
			: _position{other._position}, _color{other._color} {
			}

			/* move constructor */
			basic_vertex(self&& other) noexcept
			: self{other} /* copy */ {}



			// -- public assignment operators --------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) noexcept -> self& {
				_position = other._position;
				_color    = other._color;
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				return operator=(other);
			}



			/* pipeline vertex input state info */
			static auto pipeline_vertex_input_state_info(void) noexcept -> const vk::pipeline_vertex_input_state_info& {
				// VK_VERTEX_INPUT_RATE_VERTEX:   Move to the next data entry after each vertex
				// VK_VERTEX_INPUT_RATE_INSTANCE: Move to the next data entry after each instance

				//  float: VK_FORMAT_R32_SFLOAT
				//   vec2: VK_FORMAT_R32G32_SFLOAT
				//   vec3: VK_FORMAT_R32G32B32_SFLOAT
				//   vec4: VK_FORMAT_R32G32B32A32_SFLOAT
				//  ivec2: VK_FORMAT_R32G32_SINT        (a 2-component vector of 32-bit signed integers)
				//  uvec4: VK_FORMAT_R32G32B32A32_UINT  (a 4-component vector of 32-bit unsigned integers)
				// double: VK_FORMAT_R64_SFLOAT         (a double-precision (64-bit) float)

				// create binding description
				static constexpr vk::vertex_input_binding_description binding{
					.binding   = 0, // index in binding array
					.stride    = sizeof(self),
					.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
				};

				// create attribute descriptions
				static constexpr xns::array attribute {
					vk::vertex_input_attribute_description{
						.location = 0, // shader location
						.binding  = 0, // binding index
						.format   = VK_FORMAT_R32G32B32_SFLOAT, // float3
						.offset   = offsetof(self, _position)
					},
					vk::vertex_input_attribute_description{
						.location = 1, // shader location
						.binding  = 0, // binding index
						.format   = VK_FORMAT_R32G32B32A32_SFLOAT, // float4
						.offset   = offsetof(self, _color)
					}
				};

				// create pipeline vertex input state info
				static constexpr vk::pipeline_vertex_input_state_info info{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0,
					.vertexBindingDescriptionCount   = 1,
					.pVertexBindingDescriptions      = &binding,
					.vertexAttributeDescriptionCount = attribute.size(),
					.pVertexAttributeDescriptions    = attribute.data()
				};

				// return info
				return info;
			}

	}; // class basic_vertex

} // namespace engine

#endif // ENGINE_BASIC_VERTEX_HPP
