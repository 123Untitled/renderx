#ifndef ENGINE_VULKAN_DEVICE_HPP
#define ENGINE_VULKAN_DEVICE_HPP

// vulkan headers
#include <vulkan/vulkan.h>

// local headers
#include "vulkan_physical_device.hpp"
#include "vulkan_queue_families.hpp"
#include "vulkan_surface.hpp"

#include "shader_library.hpp"

#include "os.hpp"

// -- forward declarations ----------------------------------------------------

//namespace engine {
//	/* shader library */
//	template <xns::basic_string_literal...>
//	class shader_library;
//}

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


			/* deleted copy constructor */
			logical_device(const self&) = delete;

			/* move constructor */
			logical_device(self&&) noexcept;

			/* destructor */
			~logical_device(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* VkDevice conversion operator */
			operator const ::VkDevice&(void) const noexcept;


			// -- public methods ----------------------------------------------

			/* wait idle */
			auto wait_idle(void) const -> void;




		private:

			// -- private static methods --------------------------------------

			/* create device */
			static auto create_device(const vulkan::physical_device&,
									  const ::VkDeviceCreateInfo&) -> ::VkDevice;

			/* create device info */
			static auto create_device_info(::VkDeviceQueueCreateInfo&,
										   ::VkPhysicalDeviceFeatures&) noexcept -> ::VkDeviceCreateInfo;



			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void;

			/* init */
			auto init(void) noexcept -> void;


			// -- private members ---------------------------------------------

			/* vulkan device */
			::VkDevice _device;

			/* queue priority */
			float _priority;

	}; // class device

} // namespace vulkan

#endif // ENGINE_VULKAN_DEVICE_HPP
