#include "ve/vulkan/framebuffers.hpp"
#include "ve/vulkan/image_views.hpp"
#include "ve/vulkan/render_pass.hpp"
#include "ve/vulkan/device.hpp"

#include "ve/vk/utils.hpp"

#include "ve/memory/malloc.hpp"

// -- private methods ---------------------------------------------------------

/* destroy */
auto vulkan::framebuffers::_destroy(void) noexcept -> void {

	// loop over framebuffers
	for (size_type i = 0U; i < _size; ++i) {

		// destroy framebuffer
		::vk_destroy_framebuffer(vulkan::device::logical(),
				_frames[i], nullptr);
	}
}

/* create */
auto vulkan::framebuffers::_create(const vulkan::image_views& views,
								   const vulkan::render_pass& rpass,
								   const vk::extent2D& extent) -> void {

	// create guard
	___self::_guard guard{*this};

	// create info
	auto info = ___self::info(rpass, extent);

	// loop over views
	for (; _size < views.size(); ++_size) {

		// set number of attachments
		info.attachmentCount = 1U;

		// set attachment
		info.pAttachments = &(views[_size]);

		// create framebuffer
		vk::try_execute<"failed to create framebuffer">(
				::vk_create_framebuffer,
				vulkan::device::logical(), &info, nullptr, &(_frames[_size]));
	}

	// release guard
	guard.complete();
}


// -- private static methods --------------------------------------------------

/* info */
auto vulkan::framebuffers::info(const vulkan::render_pass& rpass,
								const vk::extent2D& extent) noexcept -> vk::framebuffer_info {

	// return info
	return vk::framebuffer_info {

		// structure type
		VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		// next structure
		nullptr,
		// flags (none)
		0U,
		// render pass
		rpass.underlying(),
		// attachment count
		0U,
		// attachments
		nullptr,
		// width
		extent.width,
		// height
		extent.height,
		// layers
		1U
	};
}


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::framebuffers::framebuffers(void) noexcept
: _frames{nullptr}, _size{0U} {
}

/* views / render_pass constructor */
vulkan::framebuffers::framebuffers(const vulkan::image_views& views,
								   const vulkan::render_pass& rpass,
								   const vk::extent2D& extent)
: _frames{rx::malloc<vk::framebuffer>(views.size())}, _size{0U} {

	// create framebuffers
	___self::_create(views, rpass, extent);
}

/* move constructor */
vulkan::framebuffers::framebuffers(vulkan::framebuffers&& ___ot) noexcept
: _frames{___ot._frames}, _size{___ot._size} {

	// invalidate other
	___ot._frames = nullptr;
	___ot._size   = 0U;
}

/* destructor */
vulkan::framebuffers::~framebuffers(void) noexcept {

	// destroy
	___self::_destroy();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::framebuffers::operator=(vulkan::framebuffers&& ___ot) noexcept -> vulkan::framebuffers& {

	// check for self-assignment
	if (this == &___ot)
		return *this;

	// destroy
	___self::_destroy();

	// move assign
	_frames = ___ot._frames;
	  _size = ___ot._size;

	// invalidate other
	___ot._frames = nullptr;
	___ot._size   = 0U;

	return *this;
}


// -- public subscript operators ----------------------------------------------

/* subscript operator */
auto vulkan::framebuffers::operator[](const size_type& ___ix) const noexcept -> const vk::framebuffer& {
	return _frames[___ix];
}

// -- public accessors --------------------------------------------------------

/* size */
auto vulkan::framebuffers::size(void) const noexcept -> size_type {
	return _size;
}


// -- public modifiers --------------------------------------------------------

/* recreate */
auto vulkan::framebuffers::recreate(const vulkan::image_views& views,
									const vulkan::render_pass& rpass,
									const vk::extent2D& extent) -> void {

	// destroy
	___self::_destroy();

	// reset size
	_size = 0U;

	// check size mismatch
	if (_size != views.size()) {

		// reallocate memory
		_frames = rx::realloc<vk::framebuffer>(_frames, views.size());
	}

	// create views
	___self::_create(views, rpass, extent);
}


// -- private classes ---------------------------------------------------------

/* self constructor */
vulkan::framebuffers::_guard::_guard(___self& self) noexcept
: _self{self}, _complete{false} {
}

/* destructor */
vulkan::framebuffers::_guard::~_guard(void) noexcept {

	// check completion
	if (_complete)
		return;

	// destroy
	_self._destroy();

	// release memory
	rx::free(_self._frames);
}

// -- public modifiers --------------------------------------------------------

/* complete */
auto vulkan::framebuffers::_guard::complete(void) noexcept -> void {
	_complete = true;
}
