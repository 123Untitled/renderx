#ifndef ___ve_vulkan_descriptor_set_layout___
#define ___ve_vulkan_descriptor_set_layout___

#include "ve/vk/unique.hpp"
#include "ve/vulkan/descriptor/set.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk::descriptor {


	// -- L A Y O U T ---------------------------------------------------------

	class set::layout final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::set::layout;


			// -- private members ---------------------------------------------

			/* descriptor set layout */
			vk::unique<::vk_descriptor_set_layout> _layout;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			layout(void) noexcept = default;

			/* bindings constructor */
			template <unsigned N>
			layout(const ::vk_descriptor_set_layout_binding (&bindings)[N])
			: _layout{self::_create_descriptor_set_layout(bindings, N)} {
			}

			/* builder constructor */
			layout(const self::builder&);

			/* deleted copy constructor */
			layout(const self&) = delete;

			/* move constructor */
			layout(self&&) noexcept = default;

			/* destructor */
			~layout(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const ::vk_descriptor_set_layout&(void) const noexcept;


		private:

			// -- private static methods --------------------------------------

			/* create descriptor set layout */
			static auto _create_descriptor_set_layout(
					const ::vk_descriptor_set_layout_binding* bindings,
					const vk::u32& count)
				-> vk::unique<::vk_descriptor_set_layout>;

	}; // class layout


	// -- B U I L D E R -------------------------------------------------------

	class set::layout::builder final {


		private:

			// -- friends -----------------------------------------------------

			/* layout as friend */
			friend class vk::descriptor::set::layout;


			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::set::layout::builder;


			// -- private members ---------------------------------------------

			/* bindings */
			std::vector<::vk_descriptor_set_layout_binding> _bindings;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			builder(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* binding */
			auto binding(const ::vk_descriptor_type&,
						 const ::vk_shader_stage_flags&,
						 const vk::u32& = 1U) -> self&;

			/* reset */
			auto reset(void) -> void;


			// -- public methods ----------------------------------------------

			/* build */
			auto build(void) const -> vk::descriptor::set::layout;

	}; // class builder

} // namespace vk::descriptor

#endif // ___ve_vulkan_descriptor_set_layout___
