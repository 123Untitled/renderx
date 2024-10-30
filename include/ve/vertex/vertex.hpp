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

#ifndef ___void_engine_vertex___
#define ___void_engine_vertex___

//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES

#include <glm/glm.hpp>

#include "ve/os.hpp"

#include "ve/vk/typedefs.hpp"

#include "ve/meta/index_sequence.hpp"
#include "ve/meta/type_at.hpp"

//#include "ve/structures/vector3.hpp"
//#include "ve/structures/vector2.hpp"
#include "ve/structures/vec.hpp"

#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- V E R T E X ---------------------------------------------------------

	template <typename... ___types>
	class vertex final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::vertex<___types...>;

			/* sequence type */
			template <size_type... ___idxs>
			using ___sequence = ve::index_sequence<___idxs...>;

			/* make sequence type */
			using ___make_sequence = ve::make_index_sequence<sizeof...(___types)>;

			/* type at */
			template <size_type ___idx>
			using ___type_at = ve::type_at<___idx, ___types...>;



			/* index of */
			template <typename ___type>
			static consteval auto index_of(void) noexcept -> size_type {

				size_type idx{0U};
				bool found{false};

				((std::same_as<___type, ___types> ? found = true : found ? true : ++idx), ...);
				return idx;
			}


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
				: ___wrapper<___idxs, ___types>{std::forward<___params>(___args)}... {
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
			static constexpr size_type ___offset_at = ___compute_offset<___idx, 0U, 0U>();


			/* forward declaration */
			template <typename>
			struct ___descriptions;

			/* descriptions */
			template <size_type... ___idxs>
			struct ___descriptions<___sequence<___idxs...>> final {


				// -- lifecycle -----------------------------------------------

				/* non-instantiable class */
				//___xns_not_instantiable(___descriptions);


				// -- static members ------------------------------------------

				/* descriptions */
				static constexpr vk::vertex_input_attribute_description _descriptions[sizeof...(___types)] {
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
				0U,
				// stride
				sizeof(___impl_type),
				// input rate
				VK_VERTEX_INPUT_RATE_VERTEX // pass data to shader for each vertex
			};

			/* vertex input state info */
			static constexpr vk::pipeline_vertex_input_state_info _info{
				// structure type
				VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
				// next structure
				nullptr,
				// flags
				0U,
				// binding description count
				1U,
				// vertex binding description
				&_binding,
				// vertex attribute description count
				sizeof...(___types),
				// vertex attribute description
				___descriptions_type::_descriptions
			};


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr vertex(void) noexcept = default;

			/* variadic constructor */
			template <typename... ___params>
			constexpr vertex(___params&&... ___args) noexcept
			: _impl{std::forward<___params>(___args)...} {
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


			// -- public accessors --------------------------------------------

			/* data */
			constexpr auto data(void) noexcept -> void* {
				return static_cast<void*>(&_impl);
			}

			/* const data */
			constexpr auto data(void) const noexcept -> const void* {
				return static_cast<const void*>(&_impl);
			}


			// -- public static methods ---------------------------------------

			/* pipeline vertex input state info */
			static constexpr auto info(void) noexcept -> const vk::pipeline_vertex_input_state_info& {
				return ___self::_info;
			}

			/* print info */
			auto print_info(void) -> void {

				std::cout << "vertex input state info:" << std::endl;

				std::cout << "sType: " << _info.sType << std::endl;
				std::cout << "pNext: " << _info.pNext << std::endl;
				std::cout << "flags: " << _info.flags << std::endl;
				std::cout << "  vertex binding description count: " << _info.vertexBindingDescriptionCount << std::endl;
				std::cout << "  vertex attribute description count: " << _info.vertexAttributeDescriptionCount << std::endl;

				std::cout << "  binding description:" << std::endl;
				std::cout << "    binding index: " << _binding.binding << std::endl;
				std::cout << "    stride: " << _binding.stride << std::endl;
				std::cout << "    input rate: " << _binding.inputRate << std::endl;
				std::cout << "  vertex attribute descriptions:" << std::endl;

				for (size_type i = 0; i < sizeof...(___types); ++i) {
					std::cout << "    attribute " << i << ":" << std::endl;
					std::cout << "      location: " << ___descriptions_type::_descriptions[i].location << std::endl;
					std::cout << "      binding: " << ___descriptions_type::_descriptions[i].binding << std::endl;
					std::cout << "      format: " << ___descriptions_type::_descriptions[i].format << std::endl;
					std::cout << "      offset: " << ___descriptions_type::_descriptions[i].offset << std::endl;
				}

				std::cout << std::endl;
			}



			template <typename ___type>
			auto get(void) -> ___type& {

				// get index
				constexpr size_type i = ___self::template index_of<___type>();

				return static_cast<___self::___wrapper_at<i>&>(_impl).value;
			}

			template <size_type i>
			auto get(void) -> typename ___self::___type_at<i>& {

				return static_cast<typename ___self::___wrapper_at<i>&>(_impl).value;
			}

	}; // class vertex


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___types>
	vertex(___types...) -> vertex<___types...>;



	// -- I S  V E R T E X ----------------------------------------------------

	namespace ___impl {


		/* false specialization */
		template <typename ___type>
		struct ___is_vertex final {
			static constexpr bool value = false;
		};

		/* true specialization */
		template <typename... ___types>
		struct ___is_vertex<ve::vertex<___types...>> final {
			static constexpr bool value = true;
		};

	}; // namespace ___impl


	/* is vertex */
	template <typename ___type>
	concept is_vertex = ve::___impl::___is_vertex<___type>::value;




	// packed
	class __attribute__((packed)) vert3x final {


		public:
		using vector3 = glm::vec3;
		using vector2 = glm::vec2;

			vector3 position;
			vector3 normal;
			//vector2 uv;
			//ve::vector3 position;
			//ve::vector3 normal;
			//ve::vector2 uv;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vert3x(void) noexcept = default;

			/* position constructor */
			vert3x(const float x, const float y, const float z) noexcept
			: position{x, y, z}, normal{0.0f, 0.0f, 0.0f} {//, uv{0.0f, 0.0f} {
			}

			/* position, normal constructor */
			vert3x(const float x, const float y, const float z, const float nx, const float ny, const float nz) noexcept
			: position{x, y, z}, normal{nx, ny, nz} {//, uv{0.0f, 0.0f} {
			}

			/* position, normal, uv constructor */
			//vert3x(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float u, const float v) noexcept
			//: position{x, y, z}, normal{nx, ny, nz}, uv{u, v} {
			//}

			/* position constructor */
			vert3x(const vector3& position) noexcept
			: position{position}, normal{0.0f, 0.0f, 0.0f} {//, uv{0.0f, 0.0f} {
			}

			/* position, normal constructor */
			vert3x(const vector3& position, const vector3& normal) noexcept
			: position{position}, normal{normal} {//, uv{0.0f, 0.0f} {
			}

			/* position, normal, uv constructor */
			vert3x(const vector3& position, const vector3& normal, const vector2& uv) noexcept
			: position{position}, normal{normal} {//, uv{uv} {
			}


			~vert3x(void) noexcept = default;


			/* pipeline vertex input state info */
			static auto info(void) noexcept -> const vk::pipeline_vertex_input_state_info& {

				/* vertex input binding description */
				static constexpr vk::vertex_input_binding_description _binding{
					// binding index
					0U,
					// stride
					sizeof(vert3x),
					// input rate
					VK_VERTEX_INPUT_RATE_VERTEX // pass data to shader for each vertex
				};

				static vk::vertex_input_attribute_description _descriptions[] {
					{
						// shader location
						.location = 0U,
						// binding index
						.binding  = 0U,
						// format
						.format   = VK_FORMAT_R32G32B32_SFLOAT,
						// offset
						.offset   = offsetof(vert3x, position)
					},
					{
						// shader location
						.location = 1U,
						// binding index
						.binding  = 0U,
						// format
						.format   = VK_FORMAT_R32G32B32_SFLOAT,
						// offset
						.offset   = offsetof(vert3x, normal)
					},
					/*
					{
						// shader location
						.location = 2U,
						// binding index
						.binding  = 0U,
						// format
						.format   = VK_FORMAT_R32G32_SFLOAT,
						// offset
						.offset   = offsetof(vert3x, uv)
					}
					*/
				};

				/* vertex input state info */
				static vk::pipeline_vertex_input_state_info info{
					// structure type
					VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
					// next structure
					nullptr,
					// flags
					0U,
					// binding description count
					1U,
					// vertex binding description
					&_binding,
					// vertex attribute description count
					2U,
					// vertex attribute description
					_descriptions
				};

				return info;
			}


	}; // class vert3x

} // namespace ve

#endif // ___void_engine_vertex___
