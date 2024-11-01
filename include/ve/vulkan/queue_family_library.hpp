#ifndef ___ve_vulkan_queue_family_library___
#define ___ve_vulkan_queue_family_library___

#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"
#include "ve/vulkan/physical_device.hpp"
#include "ve/vulkan/surface.hpp"
#include "ve/vulkan/queue.hpp"

#include <unordered_set>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- Q U E U E  F A M I L Y  L I B R A R Y -------------------------------

	class queue_family_library final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using _self = ve::queue_family_library;


			// -- private constants -------------------------------------------

			enum : unsigned {
				GRAPHICS = 0U,
				COMPUTE  = 1U
			};


			// -- private members ---------------------------------------------

			/* graphics families */
			std::vector<vk::u32> _graphics;

			/* compute families */
			std::vector<vk::u32> _compute;

			/* combined families */
			std::vector<vk::u32> _combined;

			/* priority */
			float _priority;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> _self& {
				static _self instance{};
				return instance;
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			queue_family_library(void)
			: _graphics{}, _compute{}, _combined{}, _priority{1.0f} {


				// get surface
				const auto& surface = vulkan::surface::shared();

				// get physical device
				const auto& pdevice = ve::physical_device::shared();


				// get queue families properties
				static const auto properties = pdevice.queue_family_properties();

				// loop over properties
				for (vk::u32 i = 0U; i < properties.size(); ++i) {

					// check for graphics family
					const bool is_graphics = (properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT
											&& is_support_surface_and_queue_family(pdevice, surface, i));

					// check for compute family
					const bool is_compute  = properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT;

					// dispatch family
					if (is_graphics == true) {

						if (is_compute == true)
							_combined.push_back(i);
						else
							_graphics.push_back(i);
					}
					else if (is_compute == true)
						_compute.push_back(i);
				}

				// check for empty families
				//if ((_graphics.empty() || _compute.empty()) && _combined.empty())
				//	throw std::runtime_error("failed to find suitable queue families");

				if (_combined.empty())
					throw std::runtime_error("failed to find suitable queue families");
			}


			// -- public static methods ---------------------------------------

			/* graphics queue */
			static auto graphics(void) -> vulkan::queue {
				return vulkan::queue{_self::_shared()._graphics[0], 0U /* index */};
			}

			/* compute queue */
			static auto compute(void) -> vulkan::queue {
				return vulkan::queue{_self::_shared()._compute[0], 0U /* index */};
			}

			/* combined queue */
			static auto combined(void) -> vulkan::queue {
				return vulkan::queue{_self::_shared()._combined[0], 0U /* index */};
			}

			/* info */
			static auto info(void) -> auto {

				// get shared instance
				auto& instance = _self::_shared();

					// graphics info
				return vk::array{
					vk::device_queue_info{
						.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0U,
						.queueFamilyIndex = instance._combined.front(),
						.queueCount = 1U,
						.pQueuePriorities = &instance._priority
					}
				};
			}


		private:

			// -- private static methods --------------------------------------

			/* support surface and queue family */
			static auto is_support_surface_and_queue_family(const vk::physical_device& pdevice,
															const vk::surface& surface,
															const vk::u32 family) -> bool {

				vk::u32 present{VK_FALSE};

				vk::try_execute<"failed to get physical device surface support">(
						::vk_get_physical_device_surface_support_khr,
						pdevice, family, surface, &present);

				return present == VK_TRUE;
			}


	}; // class queue_family_library

} // namespace ve

#endif // ___ve_vulkan_queue_family_library___
