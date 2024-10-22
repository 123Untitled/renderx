#include "ve/vulkan/buffer.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::buffer::buffer(void) noexcept
: _buffer{nullptr} {
}

/* parameters constructor */
vulkan::buffer::buffer(const vk::device_size& ___size,
					   const vk::buffer_usage_flags& ___usage)
/* uninitialized buffer */ {

	// create buffer info
	vk::buffer_info info {
		// structure type
		VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		// next structure
		nullptr,
		// flags
		0U,
		// size of buffer
		___size,
		// usage flags
		___usage,
		// sharing mode (exclusive or concurrent)
		VK_SHARING_MODE_EXCLUSIVE,
		// queue family index count (only for concurrent)
		0U,
		// queue family indices (only for concurrent)
		nullptr
	};

	// create buffer
	vk::try_execute<"failed to create buffer">(
			::vk_create_buffer, vulkan::device::logical(),
			&info, nullptr, &_buffer);
}

/* move constructor */
vulkan::buffer::buffer(___self&& ___ot) noexcept
: _buffer{___ot._buffer} {

	// invalidate other
	___ot._buffer = nullptr;
}

/* destructor */
vulkan::buffer::~buffer(void) noexcept {

	// check if buffer is valid
	if (_buffer == nullptr)
		return;

	// release buffer
	::vk_destroy_buffer(vulkan::device::logical(),
			_buffer, nullptr);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::buffer::operator=(___self&& ___ot) noexcept -> ___self& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// release buffer
	if (_buffer != nullptr)
		::vk_destroy_buffer(vulkan::device::logical(),
				_buffer, nullptr);

	// move assign
	_buffer = ___ot._buffer;
	___ot._buffer = nullptr;

	// done
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::buffer::underlying(void) const noexcept -> const vk::buffer& {
	return _buffer;
}
