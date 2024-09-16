#pragma once

#ifndef ENGINE_VULKAN_INSTANCE_HEADER
#define ENGINE_VULKAN_INSTANCE_HEADER

#include "engine/vulkan/physical_device.hpp"
#include "engine/vk/typedefs.hpp"
#include "engine/vulkan/unique.hpp"
#include "engine/vk/shared.hpp"
#include "engine/vk/array.hpp"

#include "engine/vulkan/debug_utils_messenger.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- I N S T A N C E -----------------------------------------------------

	class instance final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::instance;


		public:

			// -- public conversion operators ---------------------------------

			/* vk::instance conversion operator */
			operator const vk::instance&(void) const noexcept;


			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> ___self&;

			/* physical devices */
			static auto physical_devices(void) -> const vk::vector<vulkan::physical_device>&;


		private:

			// -- private lifecycle ---------------------------------------

			/* default constructor */
			instance(void);

			/* deleted copy constructor */
			instance(const ___self&) = delete;

			/* deleted move constructor */
			instance(___self&&) = delete;

			/* destructor */
			~instance(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private static methods ----------------------------------

			/* extension properties */
			static auto extension_properties(void) -> vk::vector<vk::extension_properties>;

			/* layer properties */
			static auto layer_properties(void) -> vk::vector<vk::layer_properties>;


			// -- private members -----------------------------------------

			/* instance */
			vk::shared<vk::instance> _instance;

			/* messenger */
			#if defined(ENGINE_VL_DEBUG)
			vulkan::debug_utils_messenger _messenger;
			#endif

	}; // class instance

} // namespace vulkan

#endif // ENGINE_VULKAN_INSTANCE_HEADER
