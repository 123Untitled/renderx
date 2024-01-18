#ifndef ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
#define ENGINE_VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include "vulkan_instance.hpp"

// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::physical_device;


			// -- public lifecycle --------------------------------------------

			/* copy constructor */
			physical_device(const self& other) noexcept
			: _device{other._device} {}

			/* move constructor */
			physical_device(self&& other) noexcept
			: self{other} /* copy */ {}

			/* destructor */
			~physical_device(void) noexcept = default;



			// -- public static methods ---------------------------------------

			/* pick physical device */
			static auto pick(const vulkan::instance& instance) noexcept -> self {

				auto devices = self::enumerate_physical_devices(instance);

				for (const auto& device : devices) {
					if (self::is_device_suitable(device) == true) {
						return self{device};
					}
				}
				std::cerr << "error: failed to find a suitable physical device" << std::endl;
				return {};
			}


			// -- public convertion operators ---------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> ::VkPhysicalDevice {
				return _device;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			physical_device(void) noexcept
			: _device{VK_NULL_HANDLE} {}

			/* ::VkPhysicalDevice constructor */
			physical_device(::VkPhysicalDevice device) noexcept
			: _device{device} {}



			// -- private static methods --------------------------------------

			/* enumerate physical devices */
			static auto enumerate_physical_devices(const vulkan::instance& instance) -> std::vector<::VkPhysicalDevice> {

				::uint32_t  count = 0;
				::VkResult result = ::vkEnumeratePhysicalDevices(instance,
																 &count, nullptr);

				if (result != VK_SUCCESS) {
					std::cerr << "error: failed to get physical device count" << std::endl;
					return {}; }

				if (count == 0) {
					std::cerr << "error: no physical devices found" << std::endl;
					return {}; }

				std::vector<::VkPhysicalDevice> devices;
				devices.resize(count);

				result = ::vkEnumeratePhysicalDevices(instance, &count, devices.data());

				if (result != VK_SUCCESS) {
					std::cerr << "error: failed to enumerate physical devices" << std::endl;
					return {};
				}

				std::cout << "found " << count << " physical devices" << std::endl;
				return devices;
			}


			/* is device suitable */
			static bool is_device_suitable(const ::VkPhysicalDevice& device) noexcept {

				::VkPhysicalDeviceProperties properties;
				::VkPhysicalDeviceFeatures   features;

				::vkGetPhysicalDeviceProperties(device, &properties);
				::vkGetPhysicalDeviceFeatures(device, &features);

				std::cout << "check device: " << properties.deviceName << std::endl;

				//	device_type(properties);
				//device_features(features);

				return true;
				return (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
					|| properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				    && features.geometryShader;
			}



			/* device type */
			static auto device_type(const ::VkPhysicalDeviceProperties& properties) noexcept -> void {
				// switch over device type
				switch (properties.deviceType) {
					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
						std::cout << "device type: discrete gpu" << std::endl;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
						std::cout << "device type: integrated gpu" << std::endl;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
						std::cout << "device type: virtual gpu" << std::endl;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_CPU:
						std::cout << "device type: cpu" << std::endl;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_OTHER:
						std::cout << "device type: other" << std::endl;
						break;
					default:
						std::cout << "device type: unknown" << std::endl;
						break;
				}
			}

			/* device features */
			static auto device_features(const ::VkPhysicalDeviceFeatures& features) noexcept -> void {
				// switch over device features

				std::cout << "                     robustBufferAccess: " << features.robustBufferAccess << std::endl;
				std::cout << "                    fullDrawIndexUint32: " << features.fullDrawIndexUint32 << std::endl;
				std::cout << "                         imageCubeArray: " << features.imageCubeArray << std::endl;
				std::cout << "                       independentBlend: " << features.independentBlend << std::endl;
				std::cout << "                         geometryShader: " << features.geometryShader << std::endl;
				std::cout << "                     tessellationShader: " << features.tessellationShader << std::endl;
				std::cout << "                      sampleRateShading: " << features.sampleRateShading << std::endl;
				std::cout << "                           dualSrcBlend: " << features.dualSrcBlend << std::endl;
				std::cout << "                                logicOp: " << features.logicOp << std::endl;
				std::cout << "                      multiDrawIndirect: " << features.multiDrawIndirect << std::endl;
				std::cout << "              drawIndirectFirstInstance: " << features.drawIndirectFirstInstance << std::endl;
				std::cout << "                             depthClamp: " << features.depthClamp << std::endl;
				std::cout << "                         depthBiasClamp: " << features.depthBiasClamp << std::endl;
				std::cout << "                       fillModeNonSolid: " << features.fillModeNonSolid << std::endl;
				std::cout << "                            depthBounds: " << features.depthBounds << std::endl;
				std::cout << "                              wideLines: " << features.wideLines << std::endl;
				std::cout << "                            largePoints: " << features.largePoints << std::endl;
				std::cout << "                             alphaToOne: " << features.alphaToOne << std::endl;
				std::cout << "                          multiViewport: " << features.multiViewport << std::endl;
				std::cout << "                      samplerAnisotropy: " << features.samplerAnisotropy << std::endl;
				std::cout << "                 textureCompressionETC2: " << features.textureCompressionETC2 << std::endl;
				std::cout << "             textureCompressionASTC_LDR: " << features.textureCompressionASTC_LDR << std::endl;
				std::cout << "                   textureCompressionBC: " << features.textureCompressionBC << std::endl;
				std::cout << "                  occlusionQueryPrecise: " << features.occlusionQueryPrecise << std::endl;
				std::cout << "                pipelineStatisticsQuery: " << features.pipelineStatisticsQuery << std::endl;
				std::cout << "         vertexPipelineStoresAndAtomics: " << features.vertexPipelineStoresAndAtomics << std::endl;
				std::cout << "               fragmentStoresAndAtomics: " << features.fragmentStoresAndAtomics << std::endl;
				std::cout << " shaderTessellationAndGeometryPointSize: " << features.shaderTessellationAndGeometryPointSize << std::endl;
				std::cout << "              shaderImageGatherExtended: " << features.shaderImageGatherExtended << std::endl;
				std::cout << "      shaderStorageImageExtendedFormats: " << features.shaderStorageImageExtendedFormats << std::endl;
				std::cout << "          shaderStorageImageMultisample: " << features.shaderStorageImageMultisample << std::endl;
				std::cout << "    shaderStorageImageReadWithoutFormat: " << features.shaderStorageImageReadWithoutFormat << std::endl;
				std::cout << "   shaderStorageImageWriteWithoutFormat: " << features.shaderStorageImageWriteWithoutFormat << std::endl;
				std::cout << "shaderUniformBufferArrayDynamicIndexing: " << features.shaderUniformBufferArrayDynamicIndexing << std::endl;
				std::cout << " shaderSampledImageArrayDynamicIndexing: " << features.shaderSampledImageArrayDynamicIndexing << std::endl;
				std::cout << "shaderStorageBufferArrayDynamicIndexing: " << features.shaderStorageBufferArrayDynamicIndexing << std::endl;
				std::cout << " shaderStorageImageArrayDynamicIndexing: " << features.shaderStorageImageArrayDynamicIndexing << std::endl;
				std::cout << "                     shaderClipDistance: " << features.shaderClipDistance << std::endl;
				std::cout << "                     shaderCullDistance: " << features.shaderCullDistance << std::endl;
				std::cout << "                          shaderFloat64: " << features.shaderFloat64 << std::endl;
				std::cout << "                            shaderInt64: " << features.shaderInt64 << std::endl;
				std::cout << "                            shaderInt16: " << features.shaderInt16 << std::endl;
				std::cout << "                shaderResourceResidency: " << features.shaderResourceResidency << std::endl;
				std::cout << "                   shaderResourceMinLod: " << features.shaderResourceMinLod << std::endl;
				std::cout << "                          sparseBinding: " << features.sparseBinding << std::endl;
				std::cout << "                  sparseResidencyBuffer: " << features.sparseResidencyBuffer << std::endl;
				std::cout << "                 sparseResidencyImage2D: " << features.sparseResidencyImage2D << std::endl;
				std::cout << "                 sparseResidencyImage3D: " << features.sparseResidencyImage3D << std::endl;
				std::cout << "                sparseResidency2Samples: " << features.sparseResidency2Samples << std::endl;
				std::cout << "                sparseResidency4Samples: " << features.sparseResidency4Samples << std::endl;
				std::cout << "                sparseResidency8Samples: " << features.sparseResidency8Samples << std::endl;
				std::cout << "               sparseResidency16Samples: " << features.sparseResidency16Samples << std::endl;
				std::cout << "                 sparseResidencyAliased: " << features.sparseResidencyAliased << std::endl;
				std::cout << "                variableMultisampleRate: " << features.variableMultisampleRate << std::endl;
				std::cout << "                       inheritedQueries: " << features.inheritedQueries << std::endl;
			}


			// -- private members ---------------------------------------------

			/* device */
			::VkPhysicalDevice _device;

	};

}

#endif // ENGINE_VULKAN_PHYSICAL_DEVICE_HPP
