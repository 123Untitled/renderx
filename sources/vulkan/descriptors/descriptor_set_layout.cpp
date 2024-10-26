#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"


// -- builder -----------------------------------------------------------------


// -- public modifiers --------------------------------------------------------

/* add binding */
auto vulkan::descriptor_set_layout::builder::add_binding(const vk::descriptor_set_layout_binding& binding) -> void {
	_bindings[binding.binding] = binding;
}

/* add binding */
auto vulkan::descriptor_set_layout::builder::add_binding(const vk::u32& binding,
														 const vk::descriptor_type& descriptor_type,
														 const vk::shader_stage_flags& stage_flags,
														 const vk::u32& count) -> void {

	// insert binding
	_bindings[binding] = vk::descriptor_set_layout_binding{
		// binding in shader
		.binding = binding,
		// type of descriptor
		.descriptorType = descriptor_type,
		// may be an array in shader, so descriptorCount define how many
		.descriptorCount = count,
		// stage where the descriptor is going to be used
		.stageFlags = stage_flags,
		// used for texture sampling
		.pImmutableSamplers = nullptr
	};
}


// -- public methods ----------------------------------------------------------

/* build */
auto vulkan::descriptor_set_layout::builder::build(void) const -> vulkan::descriptor_set_layout {

	// create vector of bindings
	std::vector<vk::descriptor_set_layout_binding> bindings;

	// allocate bindings
	bindings.reserve(_bindings.size());

	// fill bindings
	for (const auto& [_, binding] : _bindings) {
		bindings.push_back(binding); }

	// return descriptor set layout
	return vulkan::descriptor_set_layout{bindings};
}


// -- descriptor set layout ---------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* vector constructor */
vulkan::descriptor_set_layout::descriptor_set_layout(const std::vector<vk::descriptor_set_layout_binding>& bindings)
: _layout{___self::_create_descriptor_set_layout(
		bindings.data(),
		static_cast<vk::u32>(bindings.size()))} {
}


// -- public accessors --------------------------------------------------------

/* get */
auto vulkan::descriptor_set_layout::get(void) const noexcept -> const vk::descriptor_set_layout& {
	return _layout.get();
}


// -- private static methods --------------------------------------------------

/* create descriptor set layout */
auto vulkan::descriptor_set_layout::_create_descriptor_set_layout(
		const vk::descriptor_set_layout_binding* bindings,
		const vk::u32& count)
	-> vk::unique<vk::descriptor_set_layout> {

	// create descriptor set layout
	return vk::make_unique<vk::descriptor_set_layout>(
			vk::descriptor_set_layout_info{
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
