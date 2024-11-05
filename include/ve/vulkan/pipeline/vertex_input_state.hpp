#ifndef ___ve_vulkan_pipeline_vertex_input_state___
#define ___ve_vulkan_pipeline_vertex_input_state___

#include "ve/vulkan/pipeline/pipeline.hpp"
#include "ve/meta/index_sequence.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- V E R T E X  I N P U T  S T A T E -----------------------------------

	class pipeline::vertex_input_state final {


		private:

			// -- private members ---------------------------------------------

			/* bindings */
			std::vector<::vk_vertex_input_binding_description> bindings;

			/* descriptions */
			std::vector<::vk_vertex_input_attribute_description> descriptions;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::pipeline::vertex_input_state;


			// -- public members ----------------------------------------------

			/* create info */
			::vk_pipeline_vertex_input_state_create_info info;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vertex_input_state(void) noexcept
			: bindings{}, descriptions{}, info{
				// structure type
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// binding description count
				.vertexBindingDescriptionCount = 0U,
				// vertex binding description
				.pVertexBindingDescriptions = nullptr,
				// vertex attribute description count
				.vertexAttributeDescriptionCount = 0U,
				// vertex attribute description
				.pVertexAttributeDescriptions = nullptr} {
			}

			/* copy constructor */
			vertex_input_state(const self&) = default;

			/* move constructor */
			vertex_input_state(self&&) noexcept = default;

			/* destructor */
			~vertex_input_state(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* binding */
			auto binding(const vk::u32& binding,
							 const vk::u32& stride,
							 const ::vk_vertex_input_rate& rate) -> self& {

				// create binding
				bindings.emplace_back(::vk_vertex_input_binding_description{
					// binding index
					binding,
					// stride
					stride,
					// input rate
					rate});

				// update info
				info.vertexBindingDescriptionCount = static_cast<vk::u32>(bindings.size());
				info.pVertexBindingDescriptions = bindings.data();

				return *this;
			}

			/* description */
			auto description(const vk::u32& location,
								 const vk::u32& binding,
								 const ::vk_format& format,
								 const vk::u32& offset) -> self& {

				// create description
				descriptions.emplace_back(::vk_vertex_input_attribute_description{
					// shader location
					location,
					// binding index
					binding,
					// format
					format,
					// offset
					offset});

				// update info
				info.vertexAttributeDescriptionCount = static_cast<vk::u32>(descriptions.size());
				info.pVertexAttributeDescriptions = descriptions.data();

				return *this;
			}

	}; // class vertex_input_state

} // namespace vk

#endif // ___ve_vulkan_pipeline_vertex_input_state___
