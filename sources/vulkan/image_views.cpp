#include "renderx/vulkan/image_views.hpp"
#include "renderx/vulkan/images.hpp"
#include "renderx/vulkan/device.hpp"

#include "renderx/vk/utils.hpp"

#include "renderx/memory/malloc.hpp"


// -- private methods ---------------------------------------------------------

/* destroy */
auto vulkan::image_views::_destroy(void) noexcept -> void {

	// loop over views
	for (size_type i = 0U; i < _size; ++i) {

		// destroy image view
		::vk_destroy_image_view(vulkan::device::logical(),
				_views[i], nullptr);
	}
}

/* create */
auto vulkan::image_views::_create(const vulkan::images& images,
								  const vk::format& format) -> void {

	// create guard
	___self::_guard guard{*this};

	// create info
	auto info = ___self::info(format);

	// loop over images
	for (; _size < images.size(); ++_size) {

		// assign image
		info.image = images[_size];

		// create image view
		vk::try_execute<"failed to create image view">(
				::vk_create_image_view,
				vulkan::device::logical(), &info, nullptr, &_views[_size]);
	}

	// release guard
	guard.complete();
}


// -- private static methods --------------------------------------------------

/* info */
auto vulkan::image_views::info(const vk::format& format) noexcept -> vk::image_view_info {

	// return info
	return vk::image_view_info {

		// structure type
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		// next structure
		.pNext = nullptr,
		// flags
		.flags = 0U,
		// image
		.image = nullptr,
		// view type
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		// format
		.format = format,
		// components
		.components = {
			.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.a = VK_COMPONENT_SWIZZLE_IDENTITY
		},
		// subresource range
		.subresourceRange = {
			.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel   = 0U,
			.levelCount     = 1U,
			.baseArrayLayer = 0U,
			.layerCount     = 1U
		}
	};
}


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::image_views::image_views(void) noexcept
: _views{nullptr}, _size{0U} {
}

/* images constructor */
vulkan::image_views::image_views(const vulkan::images& images,
								 const vk::format format)
: _views{rx::malloc<vk::image_view>(images.size())}, _size{0U} {

	// create views
	___self::_create(images, format);
}

/* move constructor */
vulkan::image_views::image_views(vulkan::image_views&& ___ot) noexcept
: _views{___ot._views}, _size{___ot._size} {

	// invalidate other
	___ot._views = nullptr;
	___ot._size  = 0U;
}

/* destructor */
vulkan::image_views::~image_views(void) noexcept {

	// check resources
	if (_views == nullptr)
		return;

	// destroy
	___self::_destroy();

	// release memory
	rx::free(_views);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::image_views::operator=(vulkan::image_views&& ___ot) noexcept -> vulkan::image_views& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// destroy
	___self::_destroy();

	// release memory
	if (_views != nullptr)
		rx::free(_views);

	// move assign
	_views = ___ot._views;
	_size  = ___ot._size;

	// invalidate other
	___ot._views = nullptr;
	___ot._size  = 0U;

	// done
	return *this;
}


// -- public subscript operators ----------------------------------------------

/* subscript operator */
auto vulkan::image_views::operator[](const vk::u32& i) const noexcept -> const vk::image_view& {
	return _views[i];
}


// -- public accessors --------------------------------------------------------

/* size */
auto vulkan::image_views::size(void) const noexcept -> vk::u32 {
	return _size;
}


// -- public modifiers --------------------------------------------------------

/* recreate */
auto vulkan::image_views::recreate(const vulkan::images& images,
								   const vk::format format) -> void {

	// destroy
	___self::_destroy();

	// reset size
	_size = 0U;

	// check size mismatch
	if (_size != images.size()) {

		// reallocate memory
		_views = rx::realloc<vk::image_view>(_views, images.size());
	}

	// create views
	___self::_create(images, format);
}


// -- private classes ---------------------------------------------------------

/* self constructor */
vulkan::image_views::_guard::_guard(___self& self) noexcept
: _self{self}, _complete{false} {
}

/* destructor */
vulkan::image_views::_guard::~_guard(void) noexcept {

	// check completion
	if (_complete)
		return;

	// destroy
	_self._destroy();

	// release memory
	rx::free(_self._views);
}

// -- public modifiers --------------------------------------------------------

/* complete */
auto vulkan::image_views::_guard::complete(void) noexcept -> void {
	_complete = true;
}
