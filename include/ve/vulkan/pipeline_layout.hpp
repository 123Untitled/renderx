#ifndef ___void_engine_vulkan_pipeline_layout___
#define ___void_engine_vulkan_pipeline_layout___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- P I P E L I N E  L A Y O U T ----------------------------------------

	class pipeline_layout final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::pipeline_layout;


			// -- private members ---------------------------------------------

			/* pipeline layout */
			vk::pipeline_layout _layout;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline_layout(void)
			/* uninitialized layout */ {

				// create info
				const vk::pipeline_layout_info info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// set layout count
					.setLayoutCount = 0U,
					// set layouts
					.pSetLayouts = nullptr,
					// push constant range count
					.pushConstantRangeCount = 0U,
					// push constant ranges
					.pPushConstantRanges = nullptr,
				};

				// create layout
				vk::try_execute<"failed to create pipeline layout">(
					::vkCreatePipelineLayout,
					vulkan::device::logical(), &info, nullptr, &_layout);
			}

			/* push constant constructor */
			template <ve::size_t N>
			pipeline_layout(const vk::push_constant_range (&pcr)[N])
			/* uninitialized layout */ {

				// create info
				const vk::pipeline_layout_info info {
					// type of struct
					.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
					// pointer to next struct
					.pNext = nullptr,
					// flags
					.flags = 0U,
					// set layout count
					.setLayoutCount = 0U,
					// set layouts
					.pSetLayouts = nullptr,
					// push constant range count
					.pushConstantRangeCount = N,
					// push constant ranges
					.pPushConstantRanges = pcr,
				};

				// create layout
				vk::try_execute<"failed to create pipeline layout">(
					::vkCreatePipelineLayout,
					vulkan::device::logical(), &info, nullptr, &_layout);
			}

			/* deleted copy constructor */
			pipeline_layout(const ___self&) = delete;

			/* move constructor */
			pipeline_layout(___self&& ___ot) noexcept
			: _layout{___ot._layout} {

				// invalidate other
				___ot._layout = nullptr;
			}

			/* destructor */
			~pipeline_layout(void) noexcept {

				// check if layout is valid
				if (_layout == nullptr)
					return;

				// destroy layout
				::vk_destroy_pipeline_layout(
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
					::vk_destroy_pipeline_layout(
							vulkan::device::logical(), _layout, nullptr);

				// move layout
				_layout = ___ot._layout;

				// invalidate other
				___ot._layout = nullptr;

				// done
				return *this;
			}

	}; // class pipeline_layout

} // namespace vulkan

#endif // ___void_engine_vulkan_pipeline_layout___
