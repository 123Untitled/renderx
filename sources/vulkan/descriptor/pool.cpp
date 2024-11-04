#include "ve/vulkan/descriptor/pool.hpp"
#include <iostream>


// -- B U I L D E R -----------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* default constructor */
vk::descriptor::pool::builder::builder(void) noexcept
: _sizes{}, _flags{
	VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT
}, _max_sets{0U} {
}


// -- public modifiers --------------------------------------------------------

/* pool size */
auto vk::descriptor::pool::builder::pool_size(const ::vk_descriptor_type& type,
											  const vk::u32& count) -> builder& {

	// push back pool size
	_sizes.push_back(
			::vk_descriptor_pool_size{
				// type of descriptor
				.type = type,
				// number of descriptors
				.descriptorCount = count
			});

	return *this;
}

/* pool flags */
auto vk::descriptor::pool::builder::pool_flags(
		const ::vk_descriptor_pool_create_flags& flags) noexcept -> builder& {
	_flags = flags;
	return *this;
}

/* set max sets */
auto vk::descriptor::pool::builder::max_sets(const vk::u32& max_sets) noexcept -> builder& {
	_max_sets = max_sets;
	return *this;
}


// -- public methods ----------------------------------------------------------

/* build */
auto vk::descriptor::pool::builder::build(void) const -> vk::descriptor::pool {

	// create descriptor pool
	return vk::descriptor::pool{*this};
}


// -- D E S C R I P T O R  P O O L --------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* builder constructor */
vk::descriptor::pool::pool(const vk::descriptor::pool::builder& builder)
: _pool{self::_create_descriptor_pool(builder)} {
}


// -- public conversion operators ---------------------------------------------

/* const reference conversion operator */
vk::descriptor::pool::operator const ::vk_descriptor_pool&(void) const noexcept {
	return _pool.get();
}


// -- public methods ----------------------------------------------------------

/* reset */
auto vk::descriptor::pool::reset(void) const -> void {

	vk::try_execute<"failed to reset descriptor pool">(
			::vk_reset_descriptor_pool,
			vulkan::device::logical(), _pool.get(), 0U);
}


// -- private static methods --------------------------------------------------

/* create descriptor pool */
auto vk::descriptor::pool::_create_descriptor_pool(const vk::descriptor::pool::builder& builder)
	-> vk::unique<::vk_descriptor_pool> {

	// create info
	const ::vk_descriptor_pool_create_info info{
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
	return vk::make_unique<::vk_descriptor_pool>(info);
}
