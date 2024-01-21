#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include "vulkan_instance.hpp"
#include "vulkan_surface.hpp"

#include "vk_typedefs.hpp"
#include "vk_functions.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::physical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			physical_device(void) noexcept;

			/* copy constructor */
			physical_device(const self&) noexcept;

			/* move constructor */
			physical_device(self&&) noexcept;

			/* destructor */
			~physical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;





			// -- public conversion operators ---------------------------------

			/* VkPhysicalDevice conversion operator */
			operator const vk::physical_device&() const noexcept;


			// -- public accessors --------------------------------------------

			/* supports swapchain */
			auto supports_swapchain(void) const noexcept -> bool;

			/* have surface formats */
			auto have_surface_formats(const vulkan::surface&) const -> bool;

			/* have present modes */
			auto have_present_modes(const vulkan::surface&) const -> bool;

			/* is support surface and queue family */
			auto is_support_surface_and_queue_family(const vulkan::surface&, const vk::u32) const -> bool;

			/* extension properties */
			auto extension_properties(void) const -> vk::vector<vk::extension_properties>;

			/* surface capabilities */
			auto surface_capabilities(const vulkan::surface&) const -> vk::surface_capabilities;

			/* surface formats */
			auto surface_formats(const vulkan::surface&) const -> vk::vector<vk::surface_format>;

			/* surface present modes */
			auto surface_present_modes(const vulkan::surface&) const -> vk::vector<vk::present_mode>;

			/* properties */
			auto properties(void) const -> vk::physical_device_properties;

			/* features */
			auto features(void) const -> vk::physical_device_features;



		private:

			// -- friends -----------------------------------------------------

			/* vk vector allocator as friend */
			friend typename vk::vector<self>::allocator;


			// -- private lifecycle -------------------------------------------

			/* VkPhysicalDevice constructor */
			physical_device(const vk::physical_device&) noexcept;


			// -- private members ---------------------------------------------

			/* device */
			vk::physical_device _device;

	};

}

#endif // ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
