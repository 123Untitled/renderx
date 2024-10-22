/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_SWAPCHAIN___
#define ___RENDERX_VULKAN_SWAPCHAIN___

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "ve/vulkan/device.hpp"
#include "ve/vulkan/render_pass.hpp"
#include "ve/vulkan/semaphore.hpp"

#include "ve/vulkan/images.hpp"
#include "ve/vulkan/image_views.hpp"
#include "ve/vulkan/framebuffers.hpp"


#include "ve/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S W A P C H A I N ---------------------------------------------------

	class swapchain final {


		public:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::swapchain;


			// -- private members ---------------------------------------------

			/* swapchain */
			vk::swapchain _swapchain;

			/* size */
			vk::u32 _size;

			/* extent */
			vk::extent2D _extent;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			swapchain(void) noexcept;

			/* parameters constructor */
			swapchain(const vk::u32&,
					  const vk::surface_format&,
					  const vk::extent2D&,
					  const vk::surface_capabilities&,
					  const vk::present_mode&);

			/* deleted copy constructor */
			swapchain(const ___self&) = delete;

			/* move constructor */
			swapchain(___self&&) noexcept;

			/* destructor */
			~swapchain(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> vk::u32 {
				return _size;
			}

			/* extent */
			auto extent(void) const noexcept -> const vk::extent2D& {
				return _extent;
			}

			/* underlying */
			auto underlying(void) const noexcept -> const vk::swapchain& {
				return _swapchain;
			}

			/* acquire next image */
			auto acquire_next_image(const vk::semaphore&,
									vk::u32&) const -> vk::result;



			// -- public modifiers --------------------------------------------

			/* re-create */
			//auto recreate(const vulkan::device&,
			//			  const vk::surface&) -> void;

			auto recreate(const vk::u32&,
					  const vk::surface_format&,
					  const vk::extent2D&,
					  const vk::surface_capabilities&,
					  const vk::present_mode&) -> void;

	}; // class swapchain

} // namespace vulkan

#endif // ___RENDERX_VULKAN_SWAPCHAIN___
