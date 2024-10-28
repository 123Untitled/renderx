#include "ve/vulkan/descriptors/descriptor_pool.hpp"
#include <iostream>


// -- B U I L D E R -----------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::descriptor_pool::builder::builder(void) noexcept
: _sizes{}, _flags{VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT}, _max_sets{1000U} {
}


// -- public modifiers --------------------------------------------------------

/* add pool size */
auto vulkan::descriptor_pool::builder::add_pool_size(const vk::descriptor_type& type,
													 const vk::u32& count) -> void {

	// push back pool size
	_sizes.push_back(
			vk::descriptor_pool_size{
				// type of descriptor
				.type = type,
				// number of descriptors
				.descriptorCount = count
			});
}

/* set pool flags */
auto vulkan::descriptor_pool::builder::set_pool_flags(const vk::descriptor_pool_create_flags& flags) noexcept -> void {
	_flags = flags;
}

/* set max sets */
auto vulkan::descriptor_pool::builder::set_max_sets(const vk::u32& max_sets) noexcept -> void {
	_max_sets = max_sets;
}


// -- public methods ----------------------------------------------------------

/* build */
auto vulkan::descriptor_pool::builder::build(void) const -> vulkan::descriptor_pool {

	// create descriptor pool
	return vulkan::descriptor_pool{*this};
}


// -- D E S C R I P T O R  P O O L --------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* builder constructor */
vulkan::descriptor_pool::descriptor_pool(const vulkan::descriptor_pool::builder& builder)
: _pool{___self::_create_descriptor_pool(builder)} {

	std::cout << "pool descriptor created" << std::endl;
	// INFO:
	// recreate pool when swapchain is recreated
}


// -- public accessors --------------------------------------------------------

/* get */
auto vulkan::descriptor_pool::get(void) const noexcept -> const vk::descriptor_pool& {
	return _pool.get();
}


// -- public methods ----------------------------------------------------------

/* reset */
auto vulkan::descriptor_pool::reset(void) const -> void {

	vk::try_execute<"failed to reset descriptor pool">(
			::vk_reset_descriptor_pool,
			vulkan::device::logical(), _pool.get(), 0U);
}


// -- private static methods --------------------------------------------------

/* create descriptor pool */
auto vulkan::descriptor_pool::_create_descriptor_pool(const vulkan::descriptor_pool::builder& builder)
	-> vk::unique<vk::descriptor_pool> {

	// pool info
	const vk::descriptor_pool_info info{
		// type of structure
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		// next structure
		.pNext = nullptr,
		// flags
		.flags = builder._flags,
		// max sets (swapchain images ?)
		.maxSets = builder._max_sets,
		// pool size count
		.poolSizeCount = static_cast<vk::u32>(builder._sizes.size()),
		// pool sizes
		.pPoolSizes = builder._sizes.data()
	};

	// create descriptor pool
	return vk::make_unique<vk::descriptor_pool>(info);
}
