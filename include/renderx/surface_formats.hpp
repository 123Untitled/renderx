#ifndef ___RENDERX_VULKAN_SURFACE_FORMATS___
#define ___RENDERX_VULKAN_SURFACE_FORMATS___

#include "renderx/memory/malloc.hpp"
#include "renderx/memory/allocation_guard.hpp"
#include "renderx/vulkan/device.hpp"
#include "renderx/vk/typedefs.hpp"
#include "renderx/vk/utils.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S U R F A C E  F O R M A T S ----------------------------------------

	class surface_formats final {

		private:

			// -- private members ---------------------------------------------

			/* formats */
			vk::surface_format* _formats;

			/* size */
			vk::u32 _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			surface_formats(void)
			/* uninitialized members */ {

				// get physical device and surface
				const auto& pdevice = vulkan::device::physical();
				const auto& surface = vulkan::surface::shared();

				// get physical device surface formats count
				vk::try_execute<"failed to get physical device surface formats count">(
						::vk_get_physical_device_surface_formats_khr,
						pdevice, surface, &_size, nullptr);

				if (_size == 0U)
					throw std::runtime_error{"no surface formats found"};

				// allocate memory for formats
				_formats = rx::malloc<vk::surface_format>(_size);

				// create guard
				rx::allocation_guard guard{_formats};

				// get physical device surface formats
				vk::try_execute<"failed to get physical device surface formats">(
						::vk_get_physical_device_surface_formats_khr,
						pdevice, surface, &_size, _formats);

				if (_size == 1U && _formats[0U].format == VK_FORMAT_UNDEFINED)
					throw std::runtime_error{"no defined surface formats found"};

				// release guard
				guard.complete();
			}

			/* move constructor */
			surface_formats(surface_formats&& other) noexcept
			: _formats{other._formats}, _size{other._size} {

				// invalidate other
				other._formats = nullptr;
				other._size = 0U;
			}

			/* destructor */
			~surface_formats(void) {

				if (_formats == nullptr)
					return;

				// release memory
				rx::free(_formats);
			}



			/* find */
			auto find(const vk::format& format, const vk::color_space& space) const -> const vk::surface_format& {

				// loop over formats
				for (vk::u32 i = 0U; i < _size; ++i) {

					// check for matching format
					if (_formats[i].format == format && _formats[i].colorSpace == space)
						return *(_formats + i); }

				throw std::runtime_error{"no matching surface format found"};
			}


	}; // class surface_formats

} // namespace vulkan

#endif // ___RENDERX_VULKAN_SURFACE_FORMATS___
