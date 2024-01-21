#ifndef ENGINE_VK_FUNCTIONS_HPP
#define ENGINE_VK_FUNCTIONS_HPP


// vulkan headers
#include <vulkan/vulkan.h>
#include "vk_typedefs.hpp"
#include "exceptions.hpp"
#include "vulkan_exception.hpp"

#include <xns>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- types ---------------------------------------------------------------

	/* unsigned integer 32 type */
	using u32 = ::uint32_t;

	/* vector type */
	template <typename T>
	using vector = xns::vector<T>;



	/* try execute */
	template <decltype(sizeof(0)) N, typename F, typename... A>
	inline auto try_execute(F&& f, const char (&msg)[N], A&&... args) -> void {
		// get return type
		using ret_type = decltype(f(xns::forward<A>(args)...));
		// assert return type is vk::result
		static_assert(xns::is_same<ret_type, vk::result>, "invalid return type.");
		// execute function
		if (auto result = f(xns::forward<A>(args)...); result != VK_SUCCESS)
			throw vulkan::exception{msg, result};
	}


	// -- instance ------------------------------------------------------------

	/* create instance */
	inline auto create_instance(const vk::instance_info& info) -> vk::instance {
		vk::instance instance{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateInstance,
						"failed to create vulkan instance",
						&info, nullptr, &instance);
		return instance;
	}

	/* destroy instance */
	inline auto destroy_instance(vk::instance& instance) noexcept -> void {
		::vkDestroyInstance(instance, nullptr);
		instance = VK_NULL_HANDLE;
	}

	/* get instance extensions properties count */
	inline auto get_instance_extension_properties_count(const char* layer = nullptr) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get number of vulkan instance extension properties",
						layer, &count, nullptr);
		return count;
	}

	/* enumerate instance extensions properties */
	inline auto enumerate_instance_extension_properties(const char* layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto count = vk::get_instance_extension_properties_count(layer);
		vk::vector<vk::extension_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateInstanceExtensionProperties,
						"failed to get vulkan instance extension properties",
						layer, &count, properties.data());
		return properties;
	}


	/* get instance layer properties count */
	#if defined(ENGINE_VL_DEBUG)
	inline auto get_instance_layer_properties_count(void) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get number of vulkan instance layer properties",
						&count, nullptr);
		return count;
	}
	#endif

	/* enumerate instance layer properties */
	#if defined(ENGINE_VL_DEBUG)
	inline auto enumerate_instance_layer_properties(void) -> vk::vector<vk::layer_properties> {
		auto count = vk::get_instance_layer_properties_count();
		vk::vector<vk::layer_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateInstanceLayerProperties,
						"failed to get vulkan instance layer properties",
						&count, properties.data());
		return properties;
	}
	#endif


	// -- physical devices ----------------------------------------------------

	/* get physical devices count */
	inline auto get_physical_devices_count(const vk::instance& instance) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get number of physical devices",
						instance, &count, nullptr);
		return count;
	}

	/* enumerate physical devices */
	inline auto enumerate_physical_devices(const vk::instance& instance) -> vk::vector<vk::physical_device> {
		auto count = vk::get_physical_devices_count(instance);
		vk::vector<vk::physical_device> devices;
		devices.resize(count);
		vk::try_execute(::vkEnumeratePhysicalDevices,
						"failed to get physical devices",
						instance, &count, devices.data());
		return devices;
	}

	/* get device extension properties count */
	inline auto get_device_extension_properties_count(const vk::physical_device& device,
													  const char* layer = nullptr) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get number of vulkan device extension properties",
						device, layer, &count, nullptr);
		return count;
	}

	/* enumerate device extension properties */
	inline auto enumerate_device_extension_properties(const vk::physical_device& device,
													  const char* layer = nullptr) -> vk::vector<vk::extension_properties> {
		auto count = vk::get_device_extension_properties_count(device, layer);
		vk::vector<vk::extension_properties> properties;
		properties.resize(count);
		vk::try_execute(::vkEnumerateDeviceExtensionProperties,
						"failed to get vulkan device extension properties",
						device, layer, &count, properties.data());
		return properties;
	}

	/* get physical device surface capabilities */
	inline auto get_physical_device_surface_capabilities(const vk::physical_device& device,
														 const vk::surface& surface) -> vk::surface_capabilities {
		vk::surface_capabilities capabilities;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
						"failed to get physical device surface capabilities",
						device, surface, &capabilities);
		return capabilities;
	}

	/* supports swapchain */
	inline auto supports_swapchain(const vk::extension_properties& property) noexcept -> bool {
		return xns::string_view{property.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	}

	/* get physical device properties */
	inline auto get_physical_device_properties(const vk::physical_device& device) noexcept -> vk::physical_device_properties {
		vk::physical_device_properties properties;
		::vkGetPhysicalDeviceProperties(device, &properties);
		return properties;
	}

	/* get physical device features */
	inline auto get_physical_device_features(const vk::physical_device& device) noexcept -> vk::physical_device_features {
		vk::physical_device_features features;
		::vkGetPhysicalDeviceFeatures(device, &features);
		return features;
	}

	/* get physical device surface support */
	inline auto get_physical_device_surface_support(const vk::physical_device& device,
													const vk::surface& surface, vk::u32 family) -> bool {
		vk::u32 present = false;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceSupportKHR,
						"failed to get physical device surface support",
						device, family, surface, &present);
		return present == VK_TRUE;
	}


	// -- logical devices -----------------------------------------------------

	/* create device */
	inline auto create_device(const vk::physical_device& pdevice, const vk::device_info& info) -> vk::device {
		vk::device device{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateDevice,
						"failed to create logical device",
						pdevice, &info, nullptr, &device);
		return device;
	}

	/* device wait idle */
	inline auto device_wait_idle(const vk::device& device) -> void {
		vk::try_execute(::vkDeviceWaitIdle,
						"failed to wait device idle",
						device);
	}

	/* destroy device */
	inline auto destroy_device(vk::device& device) noexcept -> void {
		::vkDestroyDevice(device, nullptr);
		device = VK_NULL_HANDLE;
	}


	// -- surface formats -----------------------------------------------------

	/* get physical device surface formats count */
	inline auto get_physical_device_surface_formats_count(const vk::physical_device& device,
														  const vk::surface& surface) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get number of physical device surface formats",
						device, surface, &count, nullptr);
		return count;
	}

	/* get physical device surface formats */
	inline auto get_physical_device_surface_formats(const vk::physical_device& device,
													const vk::surface& surface) -> vk::vector<vk::surface_format> {
		auto count = vk::get_physical_device_surface_formats_count(device, surface);
		vk::vector<vk::surface_format> formats;
		formats.resize(count);
		vk::try_execute(::vkGetPhysicalDeviceSurfaceFormatsKHR,
						"failed to get physical device surface formats",
						device, surface, &count, formats.data());
		return formats;
	}


	/* get physical device surface present modes count */
	inline auto get_physical_device_surface_present_modes_count(const vk::physical_device& device,
																const vk::surface& surface) -> vk::u32 {
		vk::u32 count = 0;
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get number of physical device surface present modes",
						device, surface, &count, nullptr);
		return count;
	}

	/* get physical device surface present modes */
	inline auto get_physical_device_surface_present_modes(const vk::physical_device& device,
														  const vk::surface& surface) -> vk::vector<vk::present_mode> {
		auto count = vk::get_physical_device_surface_present_modes_count(device, surface);
		vk::vector<vk::present_mode> modes;
		modes.resize(count);
		vk::try_execute(::vkGetPhysicalDeviceSurfacePresentModesKHR,
						"failed to get physical device surface present modes",
						device, surface, &count, modes.data());
		return modes;
	}


	/* destroy surface */
	inline auto destroy_surface(const vk::instance& instance, vk::surface& surface) noexcept -> void {
		::vkDestroySurfaceKHR(instance, surface, nullptr);
		surface = VK_NULL_HANDLE;
	}



	// -- queue families ------------------------------------------------------

	/* get physical device queue family properties count */
	inline auto get_physical_device_queue_family_properties_count(const vk::physical_device& device) noexcept -> vk::u32 {
		vk::u32 count = 0;
		::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
		return count;
	}

	/* get physical device queue family properties */
	inline auto get_physical_device_queue_family_properties(const vk::physical_device& device) -> vk::vector<vk::queue_family_properties> {
		auto count = vk::get_physical_device_queue_family_properties_count(device);
		vk::vector<vk::queue_family_properties> properties;
		properties.resize(count);
		::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, properties.data());
		return properties;
	}


	// -- queue ---------------------------------------------------------------

	/* get device queue */
	inline auto get_device_queue(const vk::device& device, vk::u32 family, vk::u32 index = 0) noexcept -> vk::queue {
		vk::queue queue{VK_NULL_HANDLE};
		::vkGetDeviceQueue(device, family, index, &queue);
		return queue;
	}


	// -- swapchain -----------------------------------------------------------

	/* create swapchain */
	inline auto create_swapchain(const vk::device& device, const vk::swapchain_info& info) -> vk::swapchain {
		vk::swapchain swapchain{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSwapchainKHR,
						"failed to create swapchain",
						device, &info, nullptr, &swapchain);
		return swapchain;
	}

	/* destroy swapchain */
	inline auto destroy_swapchain(const vk::device& device, vk::swapchain& swapchain) noexcept -> void {
		::vkDestroySwapchainKHR(device, swapchain, nullptr);
		swapchain = VK_NULL_HANDLE;
	}


	// -- renderpass ----------------------------------------------------------

	/* create renderpass */
	inline auto create_renderpass(const vk::device& device, const vk::renderpass_info& info) -> vk::renderpass {
		vk::renderpass renderpass{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateRenderPass,
						"failed to create renderpass",
						device, &info, nullptr, &renderpass);
		return renderpass;
	}


	// -- semaphore -----------------------------------------------------------

	/* create semaphore */
	inline auto create_semaphore(const vk::device& device, const vk::semaphore_info& info) -> vk::semaphore {
		vk::semaphore semaphore{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateSemaphore,
						"failed to create semaphore",
						device, &info, nullptr, &semaphore);
		return semaphore;
	}

	/* destroy semaphore */
	inline auto destroy_semaphore(const vk::device& device, vk::semaphore& semaphore) noexcept -> void {
		if (semaphore == VK_NULL_HANDLE)
			return;
		::vkDestroySemaphore(device, semaphore, nullptr);
		semaphore = VK_NULL_HANDLE;
	}



} // namespace vk

#endif // ENGINE_VK_FUNCTIONS_HPP
