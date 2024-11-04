#ifndef ___ve_vulkan_pipeline_layout___
#define ___ve_vulkan_pipeline_layout___

#include "ve/vk/unique.hpp"
#include "ve/vulkan/pipeline/pipeline.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- L A Y O U T ---------------------------------------------------------

	class pipeline::layout final {


		private:

			// -- private members ---------------------------------------------

			/* layout */
			vk::unique<::vk_pipeline_layout> _layout;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			layout(void) noexcept = default;

			/* layout constructor */
			layout(const ::vk_descriptor_set_layout& layout)
			: _layout{_create_pipeline_layout<1U, 0U>(&layout, nullptr)} {
			}

			/* range constructor */
			layout(const vk::push_constant_range& range)
			: _layout{_create_pipeline_layout<0U, 1U>(nullptr, &range)} {
			}

			/* layout and range constructor */
			layout(const ::vk_descriptor_set_layout& layout,
							const vk::push_constant_range& range)
			: _layout{_create_pipeline_layout<1U, 1U>(&layout, &range)} {
			}

			/* range and layout constructor */
			layout(const vk::push_constant_range& range,
							const ::vk_descriptor_set_layout& layout)
			: _layout{_create_pipeline_layout<1U, 1U>(&layout, &range)} {
			}

			/* layout array constructor */
			template <vk::u32 Nl>
			layout(const ::vk_descriptor_set_layout (&layouts)[Nl])
			: _layout{_create_pipeline_layout<Nl, 0U>(layouts, nullptr)} {
			}

			/* range array constructor */
			template <vk::u32 Nr>
			layout(const vk::push_constant_range (&ranges)[Nr])
			: _layout{_create_pipeline_layout<0U, Nr>(nullptr, ranges)} {
			}

			/* layout and range array constructor */
			template <vk::u32 Nr>
			layout(const ::vk_descriptor_set_layout& layout,
							const vk::push_constant_range   (&ranges)[Nr])
			: _layout{_create_pipeline_layout<1U, Nr>(&layout, ranges)} {
			}

			/* range array and layout constructor */
			template <vk::u32 Nr>
			layout(const vk::push_constant_range   (&ranges)[Nr],
							const ::vk_descriptor_set_layout& layout)
			: _layout{_create_pipeline_layout<1U, Nr>(&layout, ranges)} {
			}

			/* layout array and range constructor */
			template <vk::u32 Nl>
			layout(const ::vk_descriptor_set_layout (&layouts)[Nl],
							const vk::push_constant_range   &range)
			: _layout{_create_pipeline_layout<Nl, 1U>(layouts, &range)} {
			}

			/* range and layout array constructor */
			template <vk::u32 Nl>
			layout(const vk::push_constant_range   &range,
							const ::vk_descriptor_set_layout (&layouts)[Nl])
			: _layout{_create_pipeline_layout<Nl, 1U>(layouts, &range)} {
			}

			/* layout array and range array constructor */
			template <vk::u32 Nl, vk::u32 Nr>
			layout(const ::vk_descriptor_set_layout (&layouts)[Nl],
							const vk::push_constant_range   (&ranges) [Nr])
			: _layout{_create_pipeline_layout<Nl, Nr>(layouts, ranges)} {
			}

			/* range array and layout array constructor */
			template <vk::u32 Nr, vk::u32 Nl>
			layout(const vk::push_constant_range   (&ranges) [Nr],
							const ::vk_descriptor_set_layout (&layouts)[Nl])
			: _layout{_create_pipeline_layout<Nl, Nr>(layouts, ranges)} {
			}

			/* deleted copy constructor */
			layout(const layout&) = delete;

			/* move constructor */
			layout(layout&&) noexcept = default;

			/* destructor */
			~layout(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const layout&) -> layout& = delete;

			/* move assignment operator */
			auto operator=(layout&&) noexcept -> layout& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const ::vk_pipeline_layout&(void) const noexcept {
				return _layout.get();
			}


		private:

			// -- private static methods --------------------------------------

			/* create pipeline layout */
			template <vk::u32 Nl, vk::u32 Nr>
			static auto _create_pipeline_layout(const ::vk_descriptor_set_layout* layouts,
												const vk::push_constant_range* ranges)
												-> vk::unique<::vk_pipeline_layout> {

				// create pipeline layout
				return vk::make_unique<::vk_pipeline_layout>(

					// create info
					::vk_pipeline_layout_create_info{
						// type of struct
						VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
						// pointer to next struct
						nullptr,
						// flags
						0U,
						// set layout count
						Nl,
						// set layouts
						layouts,
						// push constant range count
						Nr,
						// push constant ranges
						ranges
					}
				);
			}

	}; // class layout

} // namespace vk

#endif // ___ve_vulkan_pipeline_layout___
