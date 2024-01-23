#ifndef ENGINE_VULKAN_DEVICE_HPP
#define ENGINE_VULKAN_DEVICE_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_physical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"

#include "os.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- D E V I C E ---------------------------------------------------------

	class logical_device final {
		
		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vulkan::logical_device;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			logical_device(void) noexcept;

			/* physical device and surface constructor */
			logical_device(const vulkan::physical_device&,
						   const vulkan::surface&);


			/* copy constructor */
			logical_device(const self&) noexcept;

			/* move constructor */
			logical_device(self&&) noexcept;

			/* destructor */
			~logical_device(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* VkDevice conversion operator */
			operator const vk::device&(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* wait idle */
			auto wait_idle(void) const -> void;




		private:

			// -- private members ---------------------------------------------

			/* vulkan device */
			vulkan::shared<vk::device> _device;

			/* queue priority */
			float _priority;

	}; // class device


	/* shared device type */
	using shared_device = xns::shared_ptr<vulkan::logical_device>;


} // namespace vulkan

#endif // ENGINE_VULKAN_DEVICE_HPP
