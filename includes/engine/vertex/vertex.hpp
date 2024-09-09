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

#ifndef ENGINE_VERTEX_HEADER
#define ENGINE_VERTEX_HEADER

#include "engine/os.hpp"

#if defined(ENGINE_OS_APPLE)
#include <simd/simd.h>
#endif

#include "engine/vk/typedefs.hpp"
#include <vulkan/vulkan.h>

#include <xns/array.hpp>

#include <xns/integer_sequence.hpp>
#include <xns/type_at.hpp>
#include <xns/is_trivially_copyable.hpp>
#include <xns/is_nothrow_default_constructible.hpp>
#include <xns/is_empty.hpp>
#include <xns/literal_map.hpp>


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
						.location = 0U, // shader location
						.binding  = 0U, // binding index
						.format   = VK_FORMAT_R32G32B32_SFLOAT, // float3
						.offset   = offsetof(self, _position)
					},
					vk::vertex_input_attribute_description{
						.location = 1U, // shader location
						.binding  = 0U, // binding index
						.format   = VK_FORMAT_R32G32B32A32_SFLOAT, // float4
						.offset   = offsetof(self, _color)
					}
				};

				// create pipeline vertex input state info
				static constexpr vk::pipeline_vertex_input_state_info info{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0U,
					.vertexBindingDescriptionCount   = 1,
					.pVertexBindingDescriptions      = &binding,
					.vertexAttributeDescriptionCount = attribute.size(),
					.pVertexAttributeDescriptions    = attribute.data()
				};

				// return info
				return info;
			}

	}; // class basic_vertex


	// new implementation
	/* vertex template class like tuple
	 * generate input state info automatically
	 */


	template <typename... ___types>
	class vertex final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = engine::vertex<___types...>;

			/* sequence type */
			template <size_type... ___idxs>
			using ___sequence = xns::integer_sequence<vk::u32, ___idxs...>;

			/* make sequence type */
			using ___make_sequence = xns::make_integer_sequence<vk::u32, sizeof...(___types)>;

			/* type at */
			template <size_type ___idx>
			using ___type_at = xns::type_at<___idx, ___types...>;


			// -- private structs ---------------------------------------------

			/* wrapper */
			template <size_type ___idx, typename ___type>
			struct ___wrapper {


				// -- members -------------------------------------------------

				/* value */
				___type value;

			}; // struct __wrapper


			/* implementation */
			template <typename>
			struct ___impl;

			/* implementation */
			template <size_type... ___idxs>
			struct ___impl<___sequence<___idxs...>> final : public ___wrapper<___idxs, ___types>... {

				// -- types ---------------------------------------------------

				/* self type */
				using ___self = ___impl<___sequence<___idxs...>>;


				// -- lifecycle -----------------------------------------------

				/* constructor */
				constexpr ___impl(void) noexcept = default;

				/* variadic constructor */
				template <typename... ___params>
				constexpr ___impl(___params&&... ___args) noexcept
				: ___wrapper<___idxs, ___types>{xns::forward<___params>(___args)}... {
				}

				/* copy constructor */
				constexpr ___impl(const ___impl&) noexcept = default;

				/* move constructor */
				constexpr ___impl(___impl&&) noexcept = default;

				/* destructor */
				constexpr ~___impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

				/* move assignment operator */
				constexpr auto operator=(___self&&) noexcept -> ___self& = default;

			}; // struct ___impl


			/* impl type */
			using ___impl_type = ___impl<___make_sequence>;


			// -- private members ---------------------------------------------

			/* impl */
			___impl_type _impl;


			/* wrapper at */
			template <size_type ___idx>
			using ___wrapper_at = ___wrapper<___idx, ___type_at<___idx>>;


			/* compute offset */
			template <size_type ___idx, size_type ___ite, size_type ___off>
			static consteval auto ___compute_offset(void) noexcept -> size_type {
				// end of recursion
				if constexpr (___ite == ___idx)
					return ___off;
				// recursive call
				else return ___compute_offset<___idx, ___ite + 1, ___off + sizeof(___wrapper_at<___ite>)>();
			}

			/* offset at */
			template <size_type ___idx>
			static constexpr auto ___offset_at = ___compute_offset<___idx, 0U, 0U>();


			/* forward declaration */
			template <typename>
			struct ___descriptions;

			/* descriptions */
			template <size_type... ___idxs>
			struct ___descriptions<___sequence<___idxs...>> final {


				// -- lifecycle -----------------------------------------------

				/* non-instantiable class */
				___xns_not_instantiable(___descriptions);


				// -- static members ------------------------------------------

				/* descriptions */
				static constexpr vk::vertex_input_attribute_description descriptions[sizeof...(___types)] {
					{
						// shader location
						.location = ___idxs,
						// binding index
						.binding  = 0U,
						// format
						.format   = ___type_at<___idxs>::format(),
						// offset
						.offset   = ___offset_at<___idxs>
					}...
				};

			}; // struct ___descriptions


			/* description type */
			using ___descriptions_type = ___descriptions<___make_sequence>;


			// -- private static members --------------------------------------

			/* vertex input binding description */
			static constexpr vk::vertex_input_binding_description _binding{
				// binding index
				.binding   = 0U,
				// stride
				.stride    = sizeof(___impl_type),
				// input rate
				.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
			};

			/* vertex input state info */
			static constexpr vk::pipeline_vertex_input_state_info _info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
				// next structure
				.pNext = VK_NULL_HANDLE,
				// flags
				.flags = 0U,
				// binding description count
				.vertexBindingDescriptionCount   = 1U,
				// binding description
				.pVertexBindingDescriptions      = &_binding,
				// attribute description count
				.vertexAttributeDescriptionCount = sizeof...(___types),
				// attribute description
				.pVertexAttributeDescriptions    = ___descriptions_type::descriptions
			};


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr vertex(void) noexcept = default;

			/* variadic constructor */
			template <typename... ___params>
			constexpr vertex(___params&&... ___args) noexcept
			: _impl{xns::forward<___params>(___args)...} {
			}

			/* copy constructor */
			constexpr vertex(const ___self&) noexcept = default;

			/* move constructor */
			constexpr vertex(___self&&) noexcept = default;

			/* destructor */
			constexpr ~vertex(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			constexpr auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public static methods ---------------------------------------

			/* pipeline vertex input state info */
			static constexpr auto info(void) noexcept -> const vk::pipeline_vertex_input_state_info& {
				return _info;
			}


	}; // class vertex


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___types>
	vertex(___types...) -> vertex<___types...>;


} // namespace engine

#endif // ENGINE_VERTEX_HEADER
