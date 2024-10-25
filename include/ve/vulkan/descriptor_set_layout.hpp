#ifndef ___void_engine_vulkan_descriptor_set_layout___
#define ___void_engine_vulkan_descriptor_set_layout___

#include "ve/vk/utils.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  S E T  L A Y O U T -----------------------------

	class descriptor_set_layout final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_set_layout;


			// -- private members ---------------------------------------------

			/* descriptor set layout */
			vk::descriptor_set_layout _layout;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			descriptor_set_layout(void)
			: _layout{nullptr} {
			}

			/* bindings constructor */
			template <typename... ___types> requires (std::same_as<___types, vk::descriptor_set_layout_binding> && ...)
			descriptor_set_layout(const ___types&... lbindings)
			/* uninitialized layout */ {

				// create binding array
				const vk::descriptor_set_layout_binding bindings[sizeof...(lbindings)]{
					{lbindings}...
				};

				const vk::descriptor_set_layout_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0U,
					.bindingCount = sizeof...(lbindings),
					.pBindings = bindings
				};

				// create layout
				vk::try_execute<"failed to create descriptor set layout">(
						::vkCreateDescriptorSetLayout,
						vulkan::device::logical(),
						&info, nullptr, &_layout);
			}

			/* deleted copy constructor */
			descriptor_set_layout(const ___self&) = delete;

			/* move constructor */
			descriptor_set_layout(___self&& ___ot) noexcept
			: _layout{___ot._layout} {

				// invalidate other
				___ot._layout = nullptr;
			}

			/* destructor */
			~descriptor_set_layout(void) noexcept {

				// check if layout is valid
				if (_layout == nullptr)
					return;

				// destroy layout
				::vkDestroyDescriptorSetLayout(
						vulkan::device::logical(), _layout, nullptr);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check if this is other
				if (this == &___ot)
					return *this;

				// destroy layout
				if (_layout != nullptr)
					::vkDestroyDescriptorSetLayout(
							vulkan::device::logical(), _layout, nullptr);

				// move layout
				_layout = ___ot._layout;

				// invalidate other
				___ot._layout = nullptr;

				// done
				return *this;
			}


		private:

			// -- private static methods --------------------------------------

			/* create descriptor set layout */
			/*
			static auto _create_descriptor_set_layout(void) -> vk::descriptor_set_layout {

				const vk::descriptor_set_layout_binding binding{
					// binding in shader
					.binding = 0U,
					// type of descriptor
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					// may be an array in shader, so descriptorCount define how many
					.descriptorCount = 1U,
					// stage where the descriptor is going to be used
					.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
					// used for texture sampling
					.pImmutableSamplers = nullptr
				};

				const vk::descriptor_set_layout_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0U,
					.bindingCount = 1U,
					.pBindings = &binding
				};

				vk::descriptor_set_layout layout;

				// create layout
				vk::try_execute<"failed to create descriptor set layout">(
						::vkCreateDescriptorSetLayout,
						vulkan::device::logical(),
						&info, nullptr, &layout);

				return layout;
			}
			*/

	}; // class descriptor_set_layout

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_set_layout___
