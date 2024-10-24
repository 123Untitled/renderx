#include "ve/vulkan/command_pool.hpp"


// -- public lifecycle --------------------------------------------------------

/* flags constructor */
vulkan::command_pool::command_pool(const vk::command_pool_create_flags& ___flags)
: _pool{} {

	// create info
	vk::command_pool_info info {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = ___flags,
		.queueFamilyIndex = vulkan::device::family()
	};

	// create command pool
	vk::try_execute<"failed to create command pool">(
			::vk_create_command_pool,
			vulkan::device::logical(), &info, nullptr, &_pool);

	// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	// VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
}

/* move constructor */
vulkan::command_pool::command_pool(___self&& ___ot) noexcept
: _pool{___ot._pool} {
	___ot._pool = nullptr;
}

/* destructor */
vulkan::command_pool::~command_pool(void) noexcept {

	// free command pool
	::vk_destroy_command_pool(vulkan::device::logical(), _pool, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::command_pool::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// free command pool
	if (_pool)
		::vk_destroy_command_pool(vulkan::device::logical(), _pool, nullptr);

	// move assign
	_pool = ___ot._pool;
	___ot._pool = nullptr;

	// done
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::command_pool::underlying(void) const noexcept -> const vk::command_pool& {
	return _pool;
}


// -- public methods ----------------------------------------------------------

/* reset to system */
auto vulkan::command_pool::reset_to_system(void) const -> void {

	// info: all command buffer objects allocated from command pool must not be in the pending state
	// command buffer allocations back to the system

	vk::try_execute<"failed to reset command pool">(
			::vk_reset_command_pool, vulkan::device::logical(),
			_pool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}

/* reset to pool */
auto vulkan::command_pool::reset_to_pool(void) const -> void {

	// info: all command buffer objects allocated from command pool must not be in the pending state
	// command buffer allocations back to the pool

	vk::try_execute<"failed to reset command pool">(
			::vk_reset_command_pool, vulkan::device::logical(),
			_pool, 0U);
}

/* trim */
auto vulkan::command_pool::trim(void) const noexcept -> void {

	// trimming a command pool recycles unused memory from the command pool back to the system.
	// command buffers allocated from the pool are not affected by the command.

	::vk_trim_command_pool(vulkan::device::logical(), _pool, 0U /* reserved for future use */);
}
