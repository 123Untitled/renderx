#define GLFW_INCLUDE_VULKAN

#include "os.hpp"

#include "glfw_window.hpp"
#include "glfw_events.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_logical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_shader_module.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_extension_properties.hpp"

#include "meta_vertex.hpp"
#include "basic_vertex.hpp"

#include "exceptions.hpp"
#include <type_traits>

#include <xns>


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

				// create window
				 _window = glfw::window{800, 600};
				// create surface
				_surface = vulkan::surface{_instance, _window};
				// pick physical device
				auto choice = pick_physical_device();
				// assign physical device
				_pdevice = xns::get<vulkan::physical_device>(choice);
				// create logical device
				_ldevice = vulkan::logical_device{_pdevice, _surface};


				// get formats
				const auto& formats = xns::get<xns::vector<::VkSurfaceFormatKHR>>(choice);
				// get modes
				const auto& modes = xns::get<xns::vector<::VkPresentModeKHR>>(choice);
				// get capabilities
				const auto& capabilities = xns::get<vulkan::surface_capabilities>(choice);


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
					if (capabilities.current_extent().width != UINT32_MAX) {
						return capabilities.current_extent();
					}
					int width, height;
					::glfwGetFramebufferSize(window.underlying(), &width, &height);
					::VkExtent2D extent = {
						.width  = xns::clamp(static_cast<uint32_t>(width),  capabilities.min_image_extent().width,
								capabilities.max_image_extent().width),
						.height = xns::clamp(static_cast<uint32_t>(height), capabilities.min_image_extent().height,
								capabilities.max_image_extent().height),
					};
					return extent;

				}(capabilities, _window);


				_swapchain = vulkan::swapchain{_ldevice, _surface, capabilities, format, mode, extent};

			}


			/* run */
			auto run(void) -> void {

				glfw::events events;
				events.run(_window);
			}


		private:

			/* pick physical device */
			auto pick_physical_device(void) const -> xns::tuple<vulkan::physical_device,
													 vulkan::surface_capabilities,
													 xns::vector<::VkSurfaceFormatKHR>,
													 xns::vector<::VkPresentModeKHR>> {
				// get physical devices
				auto devices = _instance.physical_devices();
				// loop over devices
				for (const auto& device : devices) {

					auto extensions   = device.extensions();
					auto capabilities = device.capabilities(_surface);
					auto formats      = device.formats(_surface);
					auto modes        = device.present_modes(_surface);

					if (not is_suitable(device, extensions, capabilities, formats, modes) == true)
						continue;


					return {device, capabilities,
							xns::move(formats),
							xns::move(modes)};
				}
				// no suitable physical device found
				throw engine::exception{"failed to find suitable physical device"};
			}


			/* is device suitable */
			auto is_suitable(const vulkan::physical_device& device,
							 const xns::vector<vulkan::extension_properties>& extensions,
							 const vulkan::surface_capabilities& capabilities,
							 const xns::vector<::VkSurfaceFormatKHR>& formats,
							 const xns::vector<::VkPresentModeKHR>& modes) const noexcept -> bool {

				auto properties = device.properties();
				auto features   = device.features();

				bool swapchain = false;

				for (const auto& extension : extensions) {
					if (extension.name() == VK_KHR_SWAPCHAIN_EXTENSION_NAME) {
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

