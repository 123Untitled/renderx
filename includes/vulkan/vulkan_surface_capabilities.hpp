#ifndef ENGINE_VULKAN_SURFACE_CAPABILITIES_HPP
#define ENGINE_VULKAN_SURFACE_CAPABILITIES_HPP

// vulkan headers
#include <vulkan/vulkan.h>
#include <xns>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* physical device */
	class physical_device;

	/* surface */
	class surface;


	// -- S U R F A C E  C A P A B I L I T I E S --------------------------------

	class surface_capabilities final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::surface_capabilities;


			// -- public lifecycle --------------------------------------------

			/* physical device and surface constructor */
			surface_capabilities(const vulkan::physical_device&,
								 const vulkan::surface&);

			/* copy constructor */
			surface_capabilities(const self&) noexcept;

			/* move constructor */
			surface_capabilities(self&&) noexcept;

			/* destructor */
			~surface_capabilities(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public accessors --------------------------------------------

			/* min image count */
			auto min_image_count(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().minImageCount);

			/* max image count */
			auto max_image_count(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().maxImageCount);

			/* current extent */
			auto current_extent(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().currentExtent);

			/* min image extent */
			auto min_image_extent(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().minImageExtent);

			/* max image extent */
			auto max_image_extent(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().maxImageExtent);

			/* max image array layers */
			auto max_image_array_layers(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().maxImageArrayLayers);

			/* supported transforms */
			auto supported_transforms(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().supportedTransforms);

			/* current transform */
			auto current_transform(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().currentTransform);

			/* supported composite alpha */
			auto supported_composite_alpha(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().supportedCompositeAlpha);

			/* supported usage flags */
			auto supported_usage_flags(void) const noexcept
				-> decltype(xns::declval<::VkSurfaceCapabilitiesKHR>().supportedUsageFlags);


		private:

			// -- private members ---------------------------------------------

			/* capabilities */
			::VkSurfaceCapabilitiesKHR _capabilities;

	}; // class surface_capabilities

} // namespace vulkan

#endif // ENGINE_VULKAN_SURFACE_CAPABILITIES_HPP
