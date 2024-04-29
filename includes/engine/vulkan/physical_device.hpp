/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HEADER
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HEADER

#include "engine/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* surface */
	class surface;


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::physical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			physical_device(void) noexcept;

			/* vk::physical_device constructor */
			physical_device(const vk::physical_device&) noexcept;

			/* copy constructor */
			physical_device(const self&) noexcept = default;

			/* move constructor */
			physical_device(self&&) noexcept = default;

			/* destructor */
			~physical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::physical_device conversion operator */
			operator const vk::physical_device&(void) const noexcept;


			// -- public accessors --------------------------------------------

			/* find queue family */
			auto find_queue_family(const vulkan::surface&, const vk::queue_flags_bits) const -> vk::u32;

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

			// -- private members ---------------------------------------------

			/* device */
			vk::physical_device _pdevice;

	}; // class physical_device


	// -- assertions ----------------------------------------------------------

	static_assert(sizeof(vulkan::physical_device) == sizeof(vk::physical_device),
		"vk::physical_device size mismatch");

} // namespace vulkan

#endif // ENGINE_VULKAN_PHYSICAL_DEVICE_HEADER
