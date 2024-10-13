#include "renderx/vulkan/device_memory.hpp"
#include "renderx/vulkan/buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::device_memory::device_memory(void) noexcept
: _memory{nullptr} {
}

/* buffer / properties constructor */
vulkan::device_memory::device_memory(const vk::buffer& ___bf,
									 const vk::memory_property_flags& ___properties)
/* uninitialized device memory */ {

	// get device
	const vk::device& ldevice = vulkan::device::logical();

	vk::memory_requirements ___requirements;

	// get buffer memory requirements
	::vk_get_buffer_memory_requirements(ldevice,
			___bf, &___requirements);

	// create info
	const vk::memory_allocate_info info{
		// structure type
		VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		// next structure
		nullptr,
		// allocation size
		___requirements.size,
		// memory type index
		___self::_find_memory_type(___requirements.memoryTypeBits,
				___properties)
	};

	// create device memory
	vk::try_execute<"failed to allocate memory">(
			::vk_allocate_memory,
			ldevice, &info, nullptr, &_memory);
}

/* move constructor */
vulkan::device_memory::device_memory(___self&& ___ot) noexcept
: _memory{___ot._memory} {

	// invalidate other
	___ot._memory = nullptr;
}

/* destructor */
vulkan::device_memory::~device_memory(void) noexcept {

	// check if memory is valid
	if (_memory == nullptr)
		return;

	// release memory
	::vk_free_memory(vulkan::device::logical(),
			_memory, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::device_memory::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// release memory
	if (_memory != nullptr)
		::vk_free_memory(vulkan::device::logical(),
				_memory, nullptr);

	// move assign
	_memory = ___ot._memory;
	___ot._memory = nullptr;

	// done
	return *this;
}


// -- public methods ----------------------------------------------------------

/* bind buffer memory */
auto vulkan::device_memory::bind(const vk::buffer& ___buffer, const vk::device_size& ___offset) const -> void {

	// bind buffer to memory
	vk::try_execute<"failed to bind buffer memory">(
			::vk_bind_buffer_memory,
			vulkan::device::logical(), ___buffer, _memory, ___offset);

	// 4th parameter is offset in memory, but we want to bind from the beginning
	// its used for memory allocation of multiple buffers in one memory block
	// must be divisible by 'requirements.alignment'
	// very useful for optimization !
}

/* bind */
auto vulkan::device_memory::bind(const vulkan::buffer& ___buffer, const vk::device_size& ___offset) const -> void {

	// bind buffer to memory
	___self::bind(___buffer.underlying(), ___offset);
}
