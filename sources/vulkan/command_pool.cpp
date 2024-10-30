#include "ve/vulkan/command_pool.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ve::command_pool::command_pool(void)
: ve::command_pool{VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT} {
}

/* flags constructor */
ve::command_pool::command_pool(const vk::command_pool_create_flags& flags)
: _pool{

	// create command pool
	vk::make_unique<vk::command_pool>(

		// create info
		vk::command_pool_info{
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.pNext = nullptr,
			.flags = flags,
			.queueFamilyIndex = vulkan::device::family()
		})} {

	/*
	VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
	*/
}


// -- public conversion operators ---------------------------------------------

/* const vk::command_pool& conversion operator */
ve::command_pool::operator const vk::command_pool&(void) const noexcept {
	return _pool;
}



// -- public methods ----------------------------------------------------------

/* reset to system */
auto ve::command_pool::reset_to_system(void) const -> void {

	// info: all command buffer objects allocated from command pool must not be in the pending state
	// command buffer allocations back to the system

	vk::try_execute<"failed to reset command pool">(
			::vk_reset_command_pool, vulkan::device::logical(),
			_pool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}

/* reset to pool */
auto ve::command_pool::reset_to_pool(void) const -> void {

	// info: all command buffer objects allocated from command pool must not be in the pending state
	// command buffer allocations back to the pool

	vk::try_execute<"failed to reset command pool">(
			::vk_reset_command_pool, vulkan::device::logical(),
			_pool, 0U);
}

/* trim */
auto ve::command_pool::trim(void) const noexcept -> void {

	// trimming a command pool recycles unused memory from the command pool back to the system.
	// command buffers allocated from the pool are not affected by the command.

	::vk_trim_command_pool(vulkan::device::logical(), _pool, 0U /* reserved for future use */);
}
