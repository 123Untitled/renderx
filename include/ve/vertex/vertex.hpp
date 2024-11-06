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

#include "ve/structures/vec.hpp"

#include <iostream>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- V E R T E X ---------------------------------------------------------

	template <typename... Ts>
	class vertex final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::vertex<Ts...>;

			/* sequence type */
			template <size_type... Is>
			using sequence = ve::index_sequence<Is...>;

			/* make sequence type */
			using make_sequence = ve::make_index_sequence<sizeof...(Ts)>;

			/* type at */
			template <size_type I>
			using type_at = ve::type_at<I, Ts...>;



			/* index of */
			template <typename T>
			static consteval auto index_of(void) noexcept -> size_type {

				size_type idx{0U};
				bool found{false};

				((std::same_as<T, Ts> ? found = true : found ? true : ++idx), ...);
				return idx;
			}


			// -- private structs ---------------------------------------------

			/* wrapper */
			template <size_type, typename T>
			struct wrapper {


				// -- members -------------------------------------------------

				/* value */
				T value;

			}; // struct __wrapper


			/* implementation */
			template <typename>
			struct impl;

			/* implementation */
			template <size_type... Is>
			struct impl<sequence<Is...>> final : public wrapper<Is, Ts>... {

				// -- types ---------------------------------------------------

				/* self type */
				using self = impl<sequence<Is...>>;


				// -- lifecycle -----------------------------------------------

				/* constructor */
				constexpr impl(void) noexcept = default;

				/* variadic constructor */
				template <typename... Params>
				constexpr impl(Params&&... ___args) noexcept
				: wrapper<Is, Ts>{std::forward<Params>(___args)}... {
				}

				/* copy constructor */
				constexpr impl(const impl&) noexcept = default;

				/* move constructor */
				constexpr impl(impl&&) noexcept = default;

				/* destructor */
				constexpr ~impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const self&) noexcept -> self& = default;

				/* move assignment operator */
				constexpr auto operator=(self&&) noexcept -> self& = default;

			}; // struct impl


			/* impl type */
			using impl_type = impl<make_sequence>;


			// -- private members ---------------------------------------------

			/* impl */
			impl_type _impl;


			/* wrapper at */
			template <size_type I>
			using wrapper_at = wrapper<I, type_at<I>>;


			/* compute offset */
			template <size_type ___idx, size_type ___ite, size_type ___off>
			static consteval auto _compute_offset(void) noexcept -> size_type {
				// end of recursion
				if constexpr (___ite == ___idx)
					return ___off;
				// recursive call
				else return ___compute_offset<___idx, ___ite + 1, ___off + sizeof(wrapper_at<___ite>)>();
			}

			/* offset at */
			template <size_type ___idx>
			static constexpr size_type ___offset_at = ___compute_offset<___idx, 0U, 0U>();


			/* forward declaration */
			template <typename>
			struct ___descriptions;

			/* descriptions */
			template <size_type... Is>
			struct ___descriptions<sequence<Is...>> final {


				// -- lifecycle -----------------------------------------------

				/* non-instantiable class */
				//___xns_not_instantiable(___descriptions);


				// -- static members ------------------------------------------

				/* descriptions */
				static constexpr vk::vertex_input_attribute_description _descriptions[sizeof...(Ts)] {
					{
						// shader location
						.location = Is,
						// binding index
						.binding  = 0U,
						// format
						.format   = type_at<Is>::format(),
						// offset
						.offset   = ___offset_at<Is>
					}...
				};

			}; // struct ___descriptions


			/* description type */
			using ___descriptions_type = ___descriptions<make_sequence>;


			// -- private static members --------------------------------------

			/* vertex input binding description */
			static constexpr vk::vertex_input_binding_description _binding{
				// binding index
				0U,
				// stride
				sizeof(impl_type),
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
				sizeof...(Ts),
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
			constexpr vertex(const self&) noexcept = default;

			/* move constructor */
			constexpr vertex(self&&) noexcept = default;

			/* destructor */
			constexpr ~vertex(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


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
				return self::_info;
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

				for (size_type i = 0; i < sizeof...(Ts); ++i) {
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
				constexpr size_type i = self::template index_of<___type>();

				return static_cast<self::wrapper_at<i>&>(_impl).value;
			}

			template <size_type i>
			auto get(void) -> typename self::type_at<i>& {

				return static_cast<typename self::wrapper_at<i>&>(_impl).value;
			}

	}; // class vertex


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___types>
	vertex(___types...) -> vertex<___types...>;


	inline void test() {

		ve::vertex<ve::vec3<float>,
				   ve::vec2<float>> v{};
	}


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



	// packed
	class __attribute__((packed)) vertex_with_uv final {

		public:

			using vector3 = ve::vec3f;
			using vector2 = ve::vec2f;

			vector3 position;
			vector2 uv;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vertex_with_uv(void) noexcept = default;

			/* position constructor */
			vertex_with_uv(const float x, const float y, const float z) noexcept
			: position{x, y, z}, uv{0.0f, 0.0f} {
			}

			/* position, uv constructor */
			vertex_with_uv(const float x, const float y, const float z,
						   const float u, const float v) noexcept
			: position{x, y, z}, uv{u, v} {
			}

			/* position constructor */
			vertex_with_uv(const vector3& position) noexcept
			: position{position}, uv{0.0f, 0.0f} {
			}

			/* position, uv constructor */
			vertex_with_uv(const vector3& position, const vector2& uv) noexcept
			: position{position}, uv{uv} {
			}

			~vertex_with_uv(void) noexcept = default;


			/* pipeline vertex input state info */
			static auto info(void) noexcept -> const vk::pipeline_vertex_input_state_info& {

				/* vertex input binding description */
				static constexpr vk::vertex_input_binding_description _binding{
					// binding index
					0U,
					// stride
					sizeof(vertex_with_uv),
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
						.offset   = offsetof(vertex_with_uv, position)
					},
					{
						// shader location
						.location = 1U,
						// binding index
						.binding  = 0U,
						// format
						.format   = VK_FORMAT_R32G32_SFLOAT,
						// offset
						.offset   = offsetof(vertex_with_uv, uv)
					},
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


	}; // class vertex_with_uv


} // namespace ve

#endif // ___void_engine_vertex___
