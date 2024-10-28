#ifndef ___void_engine_vulkan_descriptor_set_layout___
#define ___void_engine_vulkan_descriptor_set_layout___

#include "ve/vk/unique.hpp"
#include <unordered_map>


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
			vk::unique<vk::descriptor_set_layout> _layout;


		public:

			// -- forward declarations ----------------------------------------

			/* builder */
			class builder;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			descriptor_set_layout(void) noexcept = default;

			/* bindings constructor */
			template <vk::u32 N>
			descriptor_set_layout(const vk::descriptor_set_layout_binding (&bindings)[N])
			: _layout{___self::_create_descriptor_set_layout(bindings, N)} {
			}

			/* vector constructor */
			descriptor_set_layout(const std::vector<vk::descriptor_set_layout_binding>&);

			/* deleted copy constructor */
			descriptor_set_layout(const ___self&) = delete;

			/* move constructor */
			descriptor_set_layout(___self&&) noexcept = default;

			/* destructor */
			~descriptor_set_layout(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::descriptor_set_layout&;


		private:

			// -- private static methods --------------------------------------

			/* create descriptor set layout */
			static auto _create_descriptor_set_layout(const vk::descriptor_set_layout_binding* bindings,
													  const vk::u32& count)
				-> vk::unique<vk::descriptor_set_layout>;

	}; // class descriptor_set_layout


	// -- B U I L D E R -------------------------------------------------------

	class descriptor_set_layout::builder {


		private:

			// -- private members ---------------------------------------------

			/* map */
			std::unordered_map<vk::u32,
				vk::descriptor_set_layout_binding> _bindings;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			builder(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* add binding */
			auto add_binding(const vk::descriptor_set_layout_binding&) -> void;

			/* add binding */
			auto add_binding(const vk::u32&,
							 const vk::descriptor_type&,
							 const vk::shader_stage_flags&,
							 const vk::u32& = 1) -> void;


			// -- public methods ----------------------------------------------

			/* build */
			auto build(void) const -> vulkan::descriptor_set_layout;

	}; // class descriptor_set_layout::builder

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_set_layout___
