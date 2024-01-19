#define GLFW_INCLUDE_VULKAN

#include "os.hpp"
#include <simd/simd.h>

#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_logical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_shader_module.hpp"
#include "vulkan_swapchain.hpp"

#include "meta_vertex.hpp"
#include "basic_vertex.hpp"

#include "exceptions.hpp"
#include <type_traits>

#include <xns>

namespace vulkan {

	class vertex_descriptor final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::vertex_descriptor;

			/* vertex input binding description */
			using binding = ::VkVertexInputBindingDescription;

			/* vertex input attribute description */
			using attribute = ::VkVertexInputAttributeDescription;


			// -- public lifecycle --------------------------------------------


		private:

			// -- private members ---------------------------------------------

			/* vertex input binding descriptions */
			std::vector<binding> _bindings;

	};
}

namespace engine {

	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::renderer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderer(void)
			:	_window{},
				_instance{},
				_surface{},
				_pdevice{},
				_ldevice{} {

				 _window = glfw::window{800, 600};
				_surface = vulkan::surface{_instance, _window};

				auto devices = _instance.physical_devices();

				for (const auto& device : devices) {

					auto extensions   = device.extensions();
					auto capabilities = device.capabilities(_surface);
					auto formats      = device.formats(_surface);
					auto modes        = device.present_modes(_surface);

					if (is_suitable(device, extensions, capabilities, formats, modes) == true) {
						device.info();
						_pdevice = device;
						_ldevice = vulkan::logical_device{_pdevice, _surface};


						::VkSurfaceFormatKHR format = [](const auto& formats) {
							for (const auto& f : formats) {
								if (f.format == VK_FORMAT_B8G8R8A8_SRGB
									&& f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
									return f;
								}
							}
							return formats[0];
						}(formats);

						::VkPresentModeKHR mode = [](const auto& modes) {
							for (const auto& m : modes) {
								if (m == VK_PRESENT_MODE_MAILBOX_KHR) {
									return m;
								}
							}
							return VK_PRESENT_MODE_FIFO_KHR;
						}(modes);

						::VkExtent2D extent = [](const auto& capabilities, auto& window) -> ::VkExtent2D {
							if (capabilities.currentExtent.width != UINT32_MAX) {
								return capabilities.currentExtent;
							}
							int width, height;
							::glfwGetFramebufferSize(window.underlying(), &width, &height);
							::VkExtent2D extent = {
								.width  = xns::clamp(static_cast<uint32_t>(width),  capabilities.minImageExtent.width,
																					capabilities.maxImageExtent.width),
								.height = xns::clamp(static_cast<uint32_t>(height), capabilities.minImageExtent.height,
																					capabilities.maxImageExtent.height),
							};
							return extent;

						}(capabilities, _window);

						_swapchain = vulkan::swapchain{_ldevice, _surface, capabilities, format, mode, extent};
						return;
					}
				}
				// no suitable physical device found
				throw engine::exception{"failed to find suitable physical device"};

			}


			/* run */
			auto run(void) -> void {

				glfw::events events;
				events.run(_window);
			}


		private:

			/* is device suitable */
			auto is_suitable(const vulkan::physical_device& device,
							 const xns::vector<::VkExtensionProperties>& extensions,
							 const ::VkSurfaceCapabilitiesKHR& capabilities,
							 const xns::vector<::VkSurfaceFormatKHR>& formats,
							 const xns::vector<::VkPresentModeKHR>& modes) noexcept -> bool {

				auto properties = device.properties();
				auto features   = device.features();

				bool swapchain = false;
				for (const auto& extension : extensions) {
					if (std::string{extension.extensionName} == VK_KHR_SWAPCHAIN_EXTENSION_NAME) {
						swapchain = true;
						break;
					}
				}

				//	device_type(properties);
				//device_features(features);

				return swapchain == true
					&& (   properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
						|| properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
					&& (formats.empty() == false)
					&& (modes.empty() == false);

				//&& features.geometryShader;
			}

			// -- private members ---------------------------------------------

			/* window */
			glfw::window _window;

			/* instance */
			vulkan::instance _instance;

			/* surface */
			vulkan::surface _surface;

			/* physical device */
			vulkan::physical_device _pdevice;

			/* device */
			vulkan::logical_device _ldevice;

			/* swapchain */
			vulkan::swapchain _swapchain;

	};

}




int main(void) {

	// memory try block
	try {
		try { // vulkan try block
			engine::renderer renderer;
			renderer.run();
		} catch (const engine::exception& except) {
			except.print();
			return 1;
		}
	} catch (const xns::exception& except) {
		xns::print(except.get_message());
		return 1;
	}
	return 0;
}

	//vulkan::shader_module module;
	//vulkan::shader_library library;

	//glfw::window win;
	//glfw::events events;
	//events.run(win);

	//vulkan::surface surface{instance, win};

	//vulkan::queue_families families{device};

