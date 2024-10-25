#ifndef ___void_engine_vulkan_descriptor_pool___
#define ___void_engine_vulkan_descriptor_pool___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/utils.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  P O O L ----------------------------------------

	class descriptor_pool final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_pool;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vk::descriptor_pool _pool;


		public:

			// -- public lifecycle --------------------------------------------

			/* device and size constructor */
			descriptor_pool(const vk::u32& ___size)
			: _pool{___self::_create_descriptor_pool(___size)} {

				// INFO:
				// recreate pool when swapchain is recreated
			}

			/* deleted copy constructor */
			descriptor_pool(const ___self&) = delete;

			/* move constructor */
			descriptor_pool(___self&& ___ot) noexcept
			: _pool{___ot._pool} {

				// invalidate other
				___ot._pool = nullptr;
			}

			/* destructor */
			~descriptor_pool(void) noexcept {

				// check if pool is valid
				if (_pool == nullptr)
					return;

				// destroy pool
				::vkDestroyDescriptorPool(
						vulkan::device::logical(), _pool, nullptr);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check if this is other
				if (this == &___ot)
					return *this;

				// destroy pool
				if (_pool != nullptr)
					::vkDestroyDescriptorPool(
							vulkan::device::logical(), _pool, nullptr);

				// move pool
				_pool = ___ot._pool;

				// invalidate other
				___ot._pool = nullptr;

				// done
				return *this;
			}


		private:

			// -- private static methods --------------------------------------

			/* create descriptor pool */
			static auto _create_descriptor_pool(const vk::u32& ___size) -> vk::descriptor_pool {

				// pool size
				const vk::descriptor_pool_size pool_size{
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = ___size
				};

				// pool info
				const vk::descriptor_pool_info pool_info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0U,
					.maxSets = ___size,
					.poolSizeCount = 1U,
					.pPoolSizes = &pool_size
				};

				vk::descriptor_pool pool;

				// create descriptor pool
				vk::try_execute<"failed to create descriptor pool">(
						::vkCreateDescriptorPool,
						vulkan::device::logical(),
						&pool_info, nullptr, &pool);

				// done
				return pool;
			}

	}; // class descriptor_pool

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_pool___
