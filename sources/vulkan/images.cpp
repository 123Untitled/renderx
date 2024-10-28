#include "ve/vulkan/images.hpp"

#include "ve/vulkan/device.hpp"
#include "ve/vulkan/swapchain.hpp"

#include "ve/vk/utils.hpp"

#include "ve/memory/malloc.hpp"
#include "ve/memory/allocation_guard.hpp"

#include <stdexcept>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::images::images(void) noexcept
: _images{nullptr}, _size{0U} {
}

/* swapchain constructor */
vulkan::images::images(const vulkan::swapchain& ___swp)
/* uninitialized members */ {

	// get swapchain images count
	_size = ___self::_count(___swp);

	// allocate memory for images
	_images = ve::malloc<vk::image>(_size);

	// create guard
	ve::allocation_guard guard{_images};

	// get swapchain images
	vk::try_execute<"failed to get swapchain images">(
			::vk_get_swapchain_images_khr,
			vulkan::device::logical(),
			___swp.underlying(), &_size, _images);

	// release guard
	guard.complete();
}

/* move constructor */
vulkan::images::images(vulkan::images&& ___ot) noexcept
: _images{___ot._images}, _size{___ot._size} {

	// invalidate other
	___ot._images = nullptr;
	___ot._size = 0U;
}

/* destructor */
vulkan::images::~images(void) noexcept {

	// check resources
	if (_images == nullptr)
		return;

	// release memory
	ve::free(_images);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::images::operator=(vulkan::images&& ___ot) noexcept -> vulkan::images& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// release memory
	if (_images != nullptr)
		ve::free(_images);

	// move assign
	_images = ___ot._images;
	_size = ___ot._size;

	// invalidate other
	___ot._images = nullptr;
	___ot._size = 0U;

	// done
	return *this;
}


// -- public subscript operators ----------------------------------------------

/* subscript operator */
auto vulkan::images::operator[](const size_type& i) const noexcept -> const vk::image& {
	return _images[i];
}


// -- public accessors --------------------------------------------------------

/* size */
auto vulkan::images::size(void) const noexcept -> size_type {
	return _size;
}


// -- public modifiers --------------------------------------------------------

/* recreate */
auto vulkan::images::recreate(const vulkan::swapchain& ___swp) -> void {

	// get swapchain images count
	size_type nsize = ___self::_count(___swp);

	// check resources
	if (_images == nullptr) {

		// allocate memory for images
		_images = ve::malloc<vk::image>(nsize);
	}

	// check for size mismatch
	else if (_size != nsize) {

		// release memory
		ve::free(_images);

		// reallocate memory for images
		_images = ve::realloc<vk::image>(_images, nsize);
	}

	// update size
	_size = nsize;

	// get swapchain images
	vk::try_execute<"failed to get swapchain images">(
			::vk_get_swapchain_images_khr,
			vulkan::device::logical(),
			___swp.underlying(), &_size, _images);
}


// -- private static methods --------------------------------------------------

/* swapchain images count */
auto vulkan::images::_count(const vulkan::swapchain& swp) -> size_type {

	// get swapchain images count
	size_type count;

	// try to get swapchain images count
	vk::try_execute<"failed to get swapchain images count">(
			::vk_get_swapchain_images_khr,
			vulkan::device::logical(),
			swp.underlying(), &count, nullptr);

	// check for no images
	if (count == 0U)
		throw std::runtime_error{"no swapchain images found"};

	// done
	return count;
}
