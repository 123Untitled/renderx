#ifndef ___ve_vulkan_physical_device___
#define ___ve_vulkan_physical_device___

#include "ve/vk/typedefs.hpp"
#include <vector>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- P H Y S I C A L  D E V I C E ----------------------------------------

	class physical_device final {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using _self = ve::physical_device;


			// -- private members ---------------------------------------------

			/* device */
			vk::physical_device _pdevice;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> _self& {
				static _self instance{};
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			physical_device(void);

			/* physical device constructor */
			physical_device(const vk::physical_device&) noexcept;

			/* deleted copy constructor */
			physical_device(const _self&) = delete;

			/* deleted move constructor */
			physical_device(_self&&) = delete;

			/* destructor */
			~physical_device(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const _self&) -> _self& = delete;

			/* move assignment operator */
			auto operator=(_self&&) noexcept -> _self& = default;


		public:

			// -- public conversion operators ---------------------------------

			/* const vk::physical_device conversion operator */
			operator const vk::physical_device&(void) const noexcept;


			// -- public accessors --------------------------------------------

			/* supports swapchain */
			auto supports_swapchain(void) const noexcept -> bool;

			/* have surface formats */
			auto have_surface_formats(void) const -> bool;

			/* have present modes */
			auto have_present_modes(void) const -> bool;

			/* extension properties */
			auto extension_properties(void) const -> std::vector<vk::extension_properties>;

			/* surface capabilities */
			auto surface_capabilities(void) const -> vk::surface_capabilities;

			/* surface formats */
			auto surface_formats(void) const -> std::vector<vk::surface_format>;

			/* surface present modes */
			auto surface_present_modes(void) const -> std::vector<vk::present_mode>;

			/* properties */
			auto properties(void) const noexcept -> vk::physical_device_properties;

			/* features */
			auto features(void) const -> vk::physical_device_features;

			/* queue family properties */
			auto queue_family_properties(void) const -> std::vector<vk::queue_family_properties>;


			/* minimum uniform buffer offset alignment */
			auto min_uniform_buffer_offset_alignment(void) const noexcept -> ::vk_device_size {
				return properties().limits.minUniformBufferOffsetAlignment;
			}

			/* max uniform buffer range */
			auto max_uniform_buffer_range(void) const noexcept -> ::vk_device_size {
				return properties().limits.maxUniformBufferRange;
			}


			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> const _self& {
				return _self::_shared();
			}


		private:

			// -- private static methods --------------------------------------

			/* pick physical device */
			static auto _pick_physical_device(void) -> vk::physical_device;

	}; // class physical_device

} // namespace vulkan

#endif // ___ve_vulkan_physical_device___
