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

#ifndef ENGINE_VK_FUNCTIONS_HEADER
#define ENGINE_VK_FUNCTIONS_HEADER


// vulkan headers
#include <vulkan/vulkan.h>

#include "ve/vk/typedefs.hpp"
#include "ve/vk/exception.hpp"

#include "ve/vk/utils.hpp"

#include <string_view>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* get instance extensions properties count */
	inline auto get_instance_extension_properties_count(const char* ___layer = nullptr) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute<"failed to enumerate instance extension properties">(
				::vk_enumerate_instance_extension_properties,
				___layer, &___count, nullptr);
		return ___count;
	}

	/* enumerate instance extensions properties */
	inline auto enumerate_instance_extension_properties(const char* ___layer = nullptr) -> std::vector<vk::extension_properties> {
		auto ___count = vk::get_instance_extension_properties_count(___layer);
		std::vector<vk::extension_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute<"failed to enumerate instance extension properties">(
				::vk_enumerate_instance_extension_properties,
				___layer, &___count, ___properties.data());
		return ___properties;
	}

	/* get instance layer properties count */
	#if defined(ENGINE_VL_DEBUG)
	inline auto get_instance_layer_properties_count(void) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute<"failed to enumerate instance layer properties">(
				::vk_enumerate_instance_layer_properties,
				&___count, nullptr);
		return ___count;
	}
	#endif

	/* enumerate instance layer properties */
	#if defined(ENGINE_VL_DEBUG)
	inline auto enumerate_instance_layer_properties(void) -> std::vector<vk::layer_properties> {
		auto ___count = vk::get_instance_layer_properties_count();
		std::vector<vk::layer_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute<"failed to enumerate instance layer properties">(
				::vk_enumerate_instance_layer_properties,
				&___count, ___properties.data());
		return ___properties;
	}
	#endif

	/* get instance proc address */
	template <typename F>
	inline auto get_instance_proc_addr(const vk::instance& ___instance, const char* ___name) -> F {
		auto ___func = ::vk_get_instance_proc_addr(___instance, ___name);
		if (___func == nullptr)
			throw vk::exception{"failed to get instance proc addr", VK_ERROR_INITIALIZATION_FAILED};
		return reinterpret_cast<F>(___func);
	}


	// -- physical devices ----------------------------------------------------

	/* get physical devices count */
	inline auto get_physical_devices_count(const vk::instance& ___instance) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute<"failed to enumerate physical devices">(
				::vk_enumerate_physical_devices,
				___instance, &___count, nullptr);
		return ___count;
	}

	/* enumerate physical devices */
	template <typename T>
	auto enumerate_physical_devices(const vk::instance& ___instance) -> std::vector<T> {

		static_assert(sizeof(T) == sizeof(vk::physical_device),
					  "T must be same size as vk::physical_device");

		auto ___count = vk::get_physical_devices_count(___instance);
		std::vector<T> ___devices;
		___devices.resize(___count);
		vk::try_execute<"failed to enumerate physical devices">(
				::vk_enumerate_physical_devices,
				___instance, &___count,
				reinterpret_cast<vk::physical_device*>(___devices.data()));
		return ___devices;
	}

	/* get device extension properties count */
	inline auto get_device_extension_properties_count(const vk::physical_device& ___device,
													  const char* ___layer = nullptr) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute<"failed to enumerate device extension properties">(
				::vk_enumerate_device_extension_properties,
				___device, ___layer, &___count, nullptr);
		return ___count;
	}

	/* enumerate device extension properties */
	inline auto enumerate_device_extension_properties(const vk::physical_device& ___device,
													  const char* ___layer = nullptr) -> std::vector<vk::extension_properties> {
		auto ___count = vk::get_device_extension_properties_count(___device, ___layer);
		std::vector<vk::extension_properties> ___properties;
		___properties.resize(___count);
		vk::try_execute<"failed to enumerate device extension properties">(
				::vk_enumerate_device_extension_properties,
				___device, ___layer, &___count, ___properties.data());
		return ___properties;
	}

	/* supports swapchain */
	inline auto supports_swapchain(const vk::extension_properties& ___property) noexcept -> bool {
		return std::string_view{___property.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	}

	/* get physical device features */
	inline auto get_physical_device_features(const vk::physical_device& ___device) noexcept -> vk::physical_device_features {
		vk::physical_device_features ___features;
		::vkGetPhysicalDeviceFeatures(___device, &___features);
		return ___features;
	}

	/* get physical device surface support */
	inline auto get_physical_device_surface_support(const vk::physical_device& ___device,
													const vk::surface& ___surface, vk::u32 ___family) -> bool {
		vk::u32 ___present = VK_FALSE;
		vk::try_execute<"failed to get physical device surface support">(
				::vk_get_physical_device_surface_support_khr,
				___device, ___family, ___surface, &___present);
		return ___present == VK_TRUE;
	}




	// -- queue families ------------------------------------------------------

	/* get physical device queue family properties count */
	inline auto get_physical_device_queue_family_properties_count(const vk::physical_device& ___device) noexcept -> vk::u32 {
		vk::u32 ___count = 0U;
		::vkGetPhysicalDeviceQueueFamilyProperties(___device, &___count, nullptr);
		return ___count;
	}

	/* get physical device queue family properties */
	inline auto get_physical_device_queue_family_properties(const vk::physical_device& ___device) -> std::vector<vk::queue_family_properties> {
		auto ___count = vk::get_physical_device_queue_family_properties_count(___device);
		std::vector<vk::queue_family_properties> ___properties;
		___properties.resize(___count);
		::vkGetPhysicalDeviceQueueFamilyProperties(___device, &___count, ___properties.data());
		return ___properties;
	}



	// -- swapchain -----------------------------------------------------------

	/* get swapchain images count */
	inline auto get_swapchain_images_count(const vk::device& ___device, const vk::swapchain& ___swapchain) -> vk::u32 {
		vk::u32 ___count = 0U;
		vk::try_execute<"failed to get swapchain images">(
				::vk_get_swapchain_images_khr,
				___device, ___swapchain, &___count, nullptr);
		return ___count;
	}

	/* get swapchain images */
	inline auto get_swapchain_images(const vk::device& ___device, const vk::swapchain& ___swapchain) -> std::vector<vk::image> {

		auto ___count = vk::get_swapchain_images_count(___device, ___swapchain);
		std::vector<vk::image> ___images;
		___images.resize(___count);
		vk::try_execute<"failed to get swapchain images">(
				::vk_get_swapchain_images_khr,
				___device, ___swapchain, &___count, ___images.data());
		return ___images;
	}

} // namespace vk

#endif // ENGINE_VK_FUNCTIONS_HEADER
