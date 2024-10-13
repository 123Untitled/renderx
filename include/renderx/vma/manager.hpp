//#ifndef ___RENDERX_VMA_MANAGER___
//#define ___RENDERX_VMA_MANAGER___
//#define VMA_IMPLEMENTATION
//
//
//#include <vk_mem_alloc.h>
//#include "renderx/vulkan/device.hpp"
//#include "renderx/vulkan/instance.hpp"
//#include "renderx/vk/utils.hpp"
//
//
//// -- V M A -------------------------------------------------------------------
//
//namespace vma {
//
//
//	// -- aliases -------------------------------------------------------------
//
//	/* allocation */
//	using allocation                     = ::VmaAllocation;
//
//	/* allocation create info */
//	using allocation_create_info         = ::VmaAllocationCreateInfo;
//
//	/* allocation info */
//	using allocation_info                = ::VmaAllocationInfo;
//
//	/* allocation info 2 */
//	using allocation_info2               = ::VmaAllocationInfo2;
//
//	/* allocator */
//	using allocator                      = ::VmaAllocator;
//
//	/* allocator create info */
//	using allocator_create_info          = ::VmaAllocatorCreateInfo;
//
//	/* allocator info */
//	using allocator_info                 = ::VmaAllocatorInfo;
//
//	/* budget */
//	using budget                         = ::VmaBudget;
//
//	/* defragmentation context */
//	using defragmentation_context        = ::VmaDefragmentationContext;
//
//	/* defragmentation info */
//	using defragmentation_info           = ::VmaDefragmentationInfo;
//
//	/* defragmentation move */
//	using defragmentation_move           = ::VmaDefragmentationMove;
//
//	/* defragmentation pass move info */
//	using defragmentation_pass_move_info = ::VmaDefragmentationPassMoveInfo;
//
//	/* defragmentation stats */
//	using defragmentation_stats          = ::VmaDefragmentationStats;
//
//	/* detailed statistics */
//	using detailed_statistics            = ::VmaDetailedStatistics;
//
//	/* device memory callbacks */
//	using device_memory_callbacks        = ::VmaDeviceMemoryCallbacks;
//
//	/* pool */
//	using pool                           = ::VmaPool;
//
//	/* pool create info */
//	using pool_create_info               = ::VmaPoolCreateInfo;
//
//	/* statistics */
//	using statistics                     = ::VmaStatistics;
//
//	/* total statistics */
//	using total_statistics               = ::VmaTotalStatistics;
//
//	/* virtual allocation */
//	using virtual_allocation             = ::VmaVirtualAllocation;
//
//	/* virtual allocation create info */
//	using virtual_allocation_create_info = ::VmaVirtualAllocationCreateInfo;
//
//	/* virtual allocation info */
//	using virtual_allocation_info        = ::VmaVirtualAllocationInfo;
//
//	/* virtual block */
//	using virtual_block                  = ::VmaVirtualBlock;
//
//	/* virtual block create info */
//	using virtual_block_create_info      = ::VmaVirtualBlockCreateInfo;
//
//	/* vulkan functions */
//	using vulkan_functions               = ::VmaVulkanFunctions;
//
//
//	/* create allocator */
//	#define vma_create_allocator vmaCreateAllocator
//
//	/* create buffer */
//	#define vma_create_buffer vmaCreateBuffer
//
//
//	// -- M A N A G E R -------------------------------------------------------
//
//	class manager final {
//
//
//		private:
//
//			// -- private types -----------------------------------------------
//
//			/* self type */
//			using ___self = vma::manager;
//
//
//			// -- private members ---------------------------------------------
//
//			/* allocator */
//			vma::allocator _allocator;
//
//
//			// -- private static methods --------------------------------------
//
//			/* shared */
//			static auto _shared(void) -> ___self& {
//				static ___self ___ins;
//				return ___ins;
//			}
//
//
//			// -- private lifecycle -------------------------------------------
//
//			/* default constructor */
//			manager(void)
//			: _allocator{nullptr} {
//
//				// allocator create info
//				const vma::allocator_create_info info{
//					// Flags for created allocator. Use VmaAllocatorCreateFlagBits enum.
//					.flags = 0,
//					// Vulkan physical device.
//					.physicalDevice = vulkan::device::physical(),
//					// Vulkan device.
//					.device = vulkan::device::logical(),
//					// Preferred size of a single VkDeviceMemory block to be allocated from large heaps > 1 GiB. Optional. (0 = use default: 256 MiB)
//					.preferredLargeHeapBlockSize = 0U,
//					// Custom CPU memory allocation callbacks. Optional.
//					.pAllocationCallbacks = nullptr,
//					// Informative callbacks for vkAllocateMemory, vkFreeMemory. Optional.
//					.pDeviceMemoryCallbacks = nullptr,
//					// Either null or a pointer to an array of limits on maximum number of bytes that can be allocated out of particular Vulkan memory heap.
//					.pHeapSizeLimit = nullptr,
//					// Pointers to Vulkan functions. Can be null.
//					.pVulkanFunctions = nullptr,
//					// Handle to Vulkan instance object.
//					.instance = vulkan::instance::shared(),
//					// Optional. Vulkan version that the application uses.
//					.vulkanApiVersion = 0U,
//					// Either null or a pointer to an array of external memory handle types for each Vulkan memory type.
//					.pTypeExternalMemoryHandleTypes = nullptr,
//				};
//
//				// create allocator
//				vk::try_execute<"failed to create vma allocator">(
//						::vma_create_allocator,
//						&info, &_allocator);
//			}
// 
//
//		public:
//
//			// -- public static methods ---------------------------------------
//
//			/* init */
//			static auto init(void) -> void {
//				___self::_shared();
//			}
//
//			/* allocate */
//			static auto allocate_buffer(const vk::buffer_info& binfo) -> vma::allocation {
//
//				// allocation create info
//				const vma::allocation_create_info ___info{
//
//					// use VmaAllocationCreateFlagBits enum.
//					.flags = 0U,
//					// Intended usage of memory.
//					.usage = VMA_MEMORY_USAGE_GPU_ONLY,
//					// Flags that must be set in a Memory Type chosen for an allocation.
//					.requiredFlags = 0U,
//					// Flags that preferably should be set in a memory type chosen for an allocation.
//					.preferredFlags = 0U,
//					// Bitmask containing one bit set for every memory type acceptable for this allocation.
//					.memoryTypeBits = 0U,
//					// Pool that this allocation should be created in.
//					.pool = nullptr,
//					// Custom general-purpose pointer that will be stored in VmaAllocation, can be read as VmaAllocationInfo::pUserData and changed using vmaSetAllocationUserData().
//					.pUserData = nullptr,
//					// A floating-point value between 0 and 1, indicating the priority of the allocation relative to other memory allocations.
//					.priority = 0.0f,
//				};
//
//				// create allocation info
//				//vma::allocation_info ___info;
//
//				// allocation
//				vma::allocation ___allocation;
//
//				vk::buffer buffer;
//
//				// get allocator
//				const auto& allocator = ___self::_shared()._allocator;
//
//				// create buffer
//				vk::try_execute<"failed to allocate buffer">(
//						::vma_create_buffer,
//						allocator, &binfo, &___info, &buffer, &___allocation, nullptr);
//				return ___allocation;
//
//
//				// it is a test, not a real code
//			}
//
//
//	}; // class allocator
//
//} // namespace vma
//
//#endif // ___RENDERX_VMA_MANAGER___
