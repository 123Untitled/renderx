#include "ve/vulkan/descriptor/layout.hpp"


// -- B U I L D E R -----------------------------------------------------------

// -- public modifiers --------------------------------------------------------

/* binding */
auto vk::descriptor::set::layout::builder::binding(const ::vk_descriptor_type& type,
												   const ::vk_shader_stage_flags& stage,
												   const vk::u32& count) -> self& {

	// push binding
	_bindings.emplace_back(
		::vk_descriptor_set_layout_binding{
			// binding in shader
			.binding = static_cast<vk::u32>(_bindings.size()),
			// type of descriptor
			.descriptorType = type,
			// may be an array in shader, so descriptorCount define how many
			.descriptorCount = count,
			// stage where the descriptor is going to be used
			.stageFlags = stage,
			// used for texture sampling
			.pImmutableSamplers = nullptr
		});

	return *this;
}

/* reset */
auto vk::descriptor::set::layout::builder::reset(void) -> void {
	_bindings.clear();
}


// -- public methods ----------------------------------------------------------

/* build */
auto vk::descriptor::set::layout::builder::build(void) const -> vk::descriptor::set::layout {

	// return descriptor set layout
	return vk::descriptor::set::layout{*this};
}


// -- L A Y O U T -------------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* builder constructor */
vk::descriptor::set::layout::layout(const builder& builder)
: _layout{self::_create_descriptor_set_layout(
					builder._bindings.data(),
					static_cast<vk::u32>(builder._bindings.size()))} {
}


// -- public conversion operators ---------------------------------------------

/* const reference conversion operator */
vk::descriptor::set::layout::operator const ::vk_descriptor_set_layout&(void) const noexcept {
	return _layout.get();
}


// -- private static methods --------------------------------------------------

/* create descriptor set layout */
auto vk::descriptor::set::layout::_create_descriptor_set_layout(
		const ::vk_descriptor_set_layout_binding* bindings,
		const vk::u32& count)
	-> vk::unique<::vk_descriptor_set_layout> {

	// create descriptor set layout
	return vk::make_unique<::vk_descriptor_set_layout>(
			::vk_descriptor_set_layout_create_info{
				// type of structure
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				// next structure
				.pNext = nullptr,
				// flags
				.flags = 0U,
				// binding count
				.bindingCount = count,
				// bindings
				.pBindings = bindings
			});
}
