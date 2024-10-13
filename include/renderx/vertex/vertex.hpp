#ifndef ENGINE_VERTEX_HEADER
#define ENGINE_VERTEX_HEADER

#include "renderx/os.hpp"

#include "renderx/vk/typedefs.hpp"

#include "renderx/meta/integer_sequence.hpp"
#include <iostream>
#include "renderx/meta/type_at.hpp"


// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// implementation:
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

	}; // class vertex


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___types>
	vertex(___types...) -> vertex<___types...>;


} // namespace engine

#endif // ENGINE_VERTEX_HEADER
