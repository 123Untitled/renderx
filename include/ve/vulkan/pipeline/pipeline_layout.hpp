#ifndef ___void_engine_vulkan_pipeline_layout___
#define ___void_engine_vulkan_pipeline_layout___

#include "ve/vk/unique.hpp"


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
			vk::unique<vk::pipeline_layout> _layout;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			pipeline_layout(void) noexcept = default;

			/* layout constructor */
			pipeline_layout(const vk::descriptor_set_layout& layout)
			: _layout{___self::_create_pipeline_layout<1U, 0U>(&layout, nullptr)} {
			}

			/* range constructor */
			pipeline_layout(const vk::push_constant_range& range)
			: _layout{___self::_create_pipeline_layout<0U, 1U>(nullptr, &range)} {
			}

			/* layout and range constructor */
			pipeline_layout(const vk::descriptor_set_layout& layout,
							const vk::push_constant_range& range)
			: _layout{___self::_create_pipeline_layout<1U, 1U>(&layout, &range)} {
			}

			/* range and layout constructor */
			pipeline_layout(const vk::push_constant_range& range,
							const vk::descriptor_set_layout& layout)
			: _layout{___self::_create_pipeline_layout<1U, 1U>(&layout, &range)} {
			}

			/* layout array constructor */
			template <vk::u32 Nl>
			pipeline_layout(const vk::descriptor_set_layout (&layouts)[Nl])
			: _layout{___self::_create_pipeline_layout<Nl, 0U>(layouts, nullptr)} {
			}

			/* range array constructor */
			template <vk::u32 Nr>
			pipeline_layout(const vk::push_constant_range (&ranges)[Nr])
			: _layout{___self::_create_pipeline_layout<0U, Nr>(nullptr, ranges)} {
			}

			/* layout and range array constructor */
			template <vk::u32 Nr>
			pipeline_layout(const vk::descriptor_set_layout& layout,
							const vk::push_constant_range   (&ranges)[Nr])
			: _layout{___self::_create_pipeline_layout<1U, Nr>(&layout, ranges)} {
			}

			/* range array and layout constructor */
			template <vk::u32 Nr>
			pipeline_layout(const vk::push_constant_range   (&ranges)[Nr],
							const vk::descriptor_set_layout& layout)
			: _layout{___self::_create_pipeline_layout<1U, Nr>(&layout, ranges)} {
			}

			/* layout array and range constructor */
			template <vk::u32 Nl>
			pipeline_layout(const vk::descriptor_set_layout (&layouts)[Nl],
							const vk::push_constant_range   &range)
			: _layout{___self::_create_pipeline_layout<Nl, 1U>(layouts, &range)} {
			}

			/* range and layout array constructor */
			template <vk::u32 Nl>
			pipeline_layout(const vk::push_constant_range   &range,
							const vk::descriptor_set_layout (&layouts)[Nl])
			: _layout{___self::_create_pipeline_layout<Nl, 1U>(layouts, &range)} {
			}

			/* layout array and range array constructor */
			template <vk::u32 Nl, vk::u32 Nr>
			pipeline_layout(const vk::descriptor_set_layout (&layouts)[Nl],
							const vk::push_constant_range   (&ranges) [Nr])
			: _layout{___self::_create_pipeline_layout<Nl, Nr>(layouts, ranges)} {
			}

			/* range array and layout array constructor */
			template <vk::u32 Nr, vk::u32 Nl>
			pipeline_layout(const vk::push_constant_range   (&ranges) [Nr],
							const vk::descriptor_set_layout (&layouts)[Nl])
			: _layout{___self::_create_pipeline_layout<Nl, Nr>(layouts, ranges)} {
			}

			/* deleted copy constructor */
			pipeline_layout(const ___self&) = delete;

			/* move constructor */
			pipeline_layout(___self&&) noexcept = default;

			/* destructor */
			~pipeline_layout(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::pipeline_layout& {
				return _layout.get();
			}


		private:

			// -- private static methods --------------------------------------

			/* create pipeline layout */
			template <vk::u32 Nl, vk::u32 Nr>
			static auto _create_pipeline_layout(const vk::descriptor_set_layout* layouts,
												const vk::push_constant_range* ranges)
												-> vk::unique<vk::pipeline_layout> {

				// create pipeline layout
				return vk::make_unique<vk::pipeline_layout>(

					// create info
					vk::pipeline_layout_info{
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

	}; // class pipeline_layout

} // namespace vulkan

#endif // ___void_engine_vulkan_pipeline_layout___
