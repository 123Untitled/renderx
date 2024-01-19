#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
vulkan::instance::instance(void)
: _instance{nullptr} {

	// create application info
	auto app_info = self::create_application_info();
	// get required extensions
	auto extensions = glfw::system::vulkan_required_extensions();
	// create instance info
	auto create = self::create_instance_info(app_info, extensions);
	// create instance
	_instance = self::create_instance(create);

	//self::enumerate_extensions();
}

/* move constructor */
vulkan::instance::instance(self&& other) noexcept
: _instance{other._instance} {
	other._instance = nullptr;
}

/* destructor */
vulkan::instance::~instance(void) noexcept {
	free();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto vulkan::instance::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	free();
	_instance = other._instance;
	other._instance = nullptr;
	return *this;
}


// -- public accessors --------------------------------------------------------

/* underlying */
auto vulkan::instance::underlying(void) noexcept -> ::VkInstance& {
	return _instance;
}

/* const underlying */
auto vulkan::instance::underlying(void) const noexcept -> const ::VkInstance& {
	return _instance;
}

/* physical devices */
auto vulkan::instance::physical_devices(void) const -> xns::vector<vulkan::physical_device> {

	::uint32_t count = self::physical_devices_count();

	xns::vector<::VkPhysicalDevice> devices{};
	devices.resize(count);

	if (::vkEnumeratePhysicalDevices(_instance, &count, devices.data()) != VK_SUCCESS)
		throw engine::exception{"failed to get physical devices"};

	xns::vector<vulkan::physical_device> result{};
	result.reserve(count);

	for (const auto& device : devices)
		result.emplace_back(device);

	return result;
}

/* physical devices count */
auto vulkan::instance::physical_devices_count(void) const -> ::uint32_t {
	::uint32_t count = 0;
	if (::vkEnumeratePhysicalDevices(_instance, &count, nullptr) != VK_SUCCESS)
		engine::fatal("failed to get number of physical devices");
	return count;
}



// -- private static methods --------------------------------------------------

/* enumerate extensions */
auto vulkan::instance::extensions(void) -> std::vector<::VkExtensionProperties> {

	::uint32_t count = 0;

	if (::vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr) != VK_SUCCESS)
		engine::fatal("failed to enumerate vulkan instance extensions.");


	std::vector<::VkExtensionProperties> properties;
	properties.resize(count);

	if (::vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data()) != VK_SUCCESS)
		engine::fatal("failed to enumerate vulkan instance extensions.");

	for (const auto& property : properties)
		std::cout << "extension: " << property.extensionName << std::endl;

	return properties;
}

/* create application info */
auto vulkan::instance::create_application_info(void) noexcept -> ::VkApplicationInfo {
	return ::VkApplicationInfo{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = nullptr,
		.pApplicationName   = "application",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName        = "engine",
		.engineVersion      = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion         = VK_API_VERSION_1_0
	};
}

/* create instance info */
auto vulkan::instance::create_instance_info(const ::VkApplicationInfo& app_info,
										    const std::vector<const char*>& extensions) noexcept -> ::VkInstanceCreateInfo {

	return ::VkInstanceCreateInfo{
		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext                   = nullptr,
#if defined(ENGINE_OS_MACOS)
		.flags                   = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
#else
		.flags                   = 0,
#endif
		.pApplicationInfo        = &app_info,
		.enabledLayerCount       = 0,
		.ppEnabledLayerNames     = nullptr,
		.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data()
	};
}

/* create instance */
auto vulkan::instance::create_instance(const ::VkInstanceCreateInfo& create) -> ::VkInstance {
	::VkInstance instance = nullptr;
	if (::vkCreateInstance(&create, nullptr, &instance) != VK_SUCCESS)
		engine::fatal("failed to create vulkan instance.");
	return instance;
}


// -- private methods ---------------------------------------------------------

/* free */
auto vulkan::instance::free(void) noexcept -> void {
	if (_instance == nullptr)
		return;
	::vkDestroyInstance(_instance, nullptr);
}

/* init */
auto vulkan::instance::init(void) noexcept -> void {
	_instance = nullptr;
}
