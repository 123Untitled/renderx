#include "vulkan_surface_capabilities.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"


// -- public lifecycle --------------------------------------------------------

/* physical device and surface constructor */
vulkan::surface_capabilities::surface_capabilities(const vulkan::physical_device& physical_device,
												   const vulkan::surface& surface)
: _capabilities{} {
	// get surface capabilities
	auto result = ::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device.underlying(),
															  surface.underlying(),
															  &_capabilities);
	if (result != VK_SUCCESS) {
		throw engine::exception("failed to get surface capabilities");
	}
}

/* copy constructor */
vulkan::surface_capabilities::surface_capabilities(const self& other) noexcept
: _capabilities{other._capabilities} {}

/* move constructor */
vulkan::surface_capabilities::surface_capabilities(self&& other) noexcept
: self{other} /* copy */ {}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
auto vulkan::surface_capabilities::operator=(const self& other) noexcept -> self& {
	_capabilities = other._capabilities;
	return *this;
}

/* move assignment operator */
auto vulkan::surface_capabilities::operator=(self&& other) noexcept -> self& {
	return self::operator=(other); /* copy */
}


// -- public accessors --------------------------------------------------------

/* min image count */
auto vulkan::surface_capabilities::min_image_count(void) const noexcept
	-> decltype(_capabilities.minImageCount) {
	return _capabilities.minImageCount;
}

/* max image count */
auto vulkan::surface_capabilities::max_image_count(void) const noexcept
	-> decltype(_capabilities.maxImageCount) {
	return _capabilities.maxImageCount;
}

/* current extent */
auto vulkan::surface_capabilities::current_extent(void) const noexcept
	-> decltype(_capabilities.currentExtent) {
	return _capabilities.currentExtent;
}

/* min image extent */
auto vulkan::surface_capabilities::min_image_extent(void) const noexcept
	-> decltype(_capabilities.minImageExtent) {
	return _capabilities.minImageExtent;
}

/* max image extent */
auto vulkan::surface_capabilities::max_image_extent(void) const noexcept
	-> decltype(_capabilities.maxImageExtent) {
	return _capabilities.maxImageExtent;
}

/* max image array layers */
auto vulkan::surface_capabilities::max_image_array_layers(void) const noexcept
	-> decltype(_capabilities.maxImageArrayLayers) {
	return _capabilities.maxImageArrayLayers;
}

/* supported transforms */
auto vulkan::surface_capabilities::supported_transforms(void) const noexcept
	-> decltype(_capabilities.supportedTransforms) {
	return _capabilities.supportedTransforms;
}

/* current transform */
auto vulkan::surface_capabilities::current_transform(void) const noexcept
	-> decltype(_capabilities.currentTransform) {
	return _capabilities.currentTransform;
}

/* supported composite alpha */
auto vulkan::surface_capabilities::supported_composite_alpha(void) const noexcept
	-> decltype(_capabilities.supportedCompositeAlpha) {
	return _capabilities.supportedCompositeAlpha;
}

/* supported usage flags */
auto vulkan::surface_capabilities::supported_usage_flags(void) const noexcept
	-> decltype(_capabilities.supportedUsageFlags) {
	return _capabilities.supportedUsageFlags;
}
