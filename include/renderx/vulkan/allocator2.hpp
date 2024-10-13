#ifndef ___RENDERX_VULKAN_ALLOCATOR___
#define ___RENDERX_VULKAN_ALLOCATOR___

#include <vulkan/vulkan_core.h>


// -- aliases -----------------------------------------------------------------

namespace vk {

	using allocation_function              = PFN_vkAllocationFunction;
	using reallocation_function            = PFN_vkReallocationFunction;
	using free_function                    = PFN_vkFreeFunction;
	using internal_allocation_notification = PFN_vkInternalAllocationNotification;
	using internal_free_notification       = PFN_vkInternalFreeNotification;
	using allocation_callbacks             = VkAllocationCallbacks;
	using system_allocation_scope          = VkSystemAllocationScope;
	using internal_allocation_type         = VkInternalAllocationType;

} // namespace vk


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- A L L O C A T O R ---------------------------------------------------

	template <typename ___type>
	class allocator final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::allocator<___type>;


			// -- private members ---------------------------------------------

			___type _allocator;

			/* callbacks */
			vk::allocation_callbacks _callbacks;


			// -- private static methods --------------------------------------

			/* allocate */
			static auto VKAPI_PTR _allocate(void* udata, size_t size, size_t alignment, vk::system_allocation_scope scope) -> void* {

				___type& allocator = *static_cast<___type*>(udata);

				switch (scope) {

					case VK_SYSTEM_ALLOCATION_SCOPE_COMMAND:
						return allocator.allocate_command(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:
						return allocator.allocate_object(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_CACHE:
						return allocator.allocate_cache(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:
						return allocator.allocate_device(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:
						return allocator.allocate_instance(size, alignment);

					default:
						return nullptr;
				}
			}

			/* reallocate */
			static auto VKAPI_PTR _reallocate(void* udata, void* original, size_t size, size_t alignment, vk::system_allocation_scope scope) -> void* {

				___type& allocator = *static_cast<___type*>(udata);

				switch (scope) {

					case VK_SYSTEM_ALLOCATION_SCOPE_COMMAND:
						return allocator.reallocate_command(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:
						return allocator.reallocate_object(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_CACHE:
						return allocator.reallocate_cache(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:
						return allocator.reallocate_device(size, alignment);

					case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:
						return allocator.reallocate_instance(size, alignment);

					default:
						return nullptr;
				}
			}

			/* free */
			static auto VKAPI_PTR _free(void* udata, void* memory) noexcept -> void {
				static_cast<___type*>(udata)->free(memory);
			}

			/* allocation notification */
			static auto VKAPI_PTR _allocation_notification(void* udata, size_t size, vk::internal_allocation_type, vk::system_allocation_scope scope) noexcept -> void {
				___type& self = *static_cast<___type*>(udata);
			}

			/* free notification */
			static auto VKAPI_PTR _free_notification(void* udata, size_t size, vk::internal_allocation_type, vk::system_allocation_scope scope) noexcept -> void {
				auto& self = *static_cast<___self*>(udata);
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			allocator(void) noexcept
			: _callbacks{&_allocator, _allocate, _reallocate, _free, _allocation_notification, _free_notification} {
			}


			/* destructor */
			~allocator(void) noexcept = default;


			/* callbacks */
			auto callbacks(void) const noexcept -> const vk::allocation_callbacks& {
				return _callbacks;
			}

	}; // class allocator


} // namespace vulkan

#endif // ___RENDERX_VULKAN_ALLOCATOR___
