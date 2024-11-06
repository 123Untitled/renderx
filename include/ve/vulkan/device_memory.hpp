#ifndef ___ENGINE_VULKAN_DEVICE_MEMORY___
#define ___ENGINE_VULKAN_DEVICE_MEMORY___

#include "ve/memory/memcpy.hpp"
#include "ve/exceptions.hpp"
#include "ve/vulkan/device.hpp"
#include "ve/vertex/vertex.hpp"
#include "ve/vk/utils.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* buffer */
	class buffer;


	// -- D E V I C E  M E M O R Y --------------------------------------------

	class device_memory final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::device_memory;


			// -- private members ---------------------------------------------

			/* memory */
			vk::device_memory _memory;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			device_memory(void) noexcept;

			/* buffer / properties constructor */
			device_memory(const vk::buffer&,
						  const vk::memory_property_flags&);

			/* deleted copy constructor */
			device_memory(const ___self&) = delete;

			/* move constructor */
			device_memory(___self&&) noexcept;

			/* destructor */
			~device_memory(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public methods ----------------------------------------------

			/* bind */
			auto bind(const vk::buffer&, const ::vk_device_size& = 0U) const -> void;

			/* bind */
			auto bind(const vulkan::buffer&, const ::vk_device_size& = 0U) const -> void;

			/* map */
			template <typename ___type>
			auto map(const ::vk_device_size& offset = 0U,
					 const ::vk_device_size& size = VK_WHOLE_SIZE) const -> ___type* {

				void* data;

				// map memory
				vk::try_execute<"failed to map memory">(
						::vk_map_memory,
						vulkan::device::logical(),
						_memory,
						offset,
						size,
						0U, // flags (reserved for future use, not implemented yet by the Vulkan API)
						&data // data pointer to store the mapped memory
				);

				// return casted data
				return static_cast<___type*>(data);
			}

			/* unmap */
			auto unmap(void) const noexcept -> void {

				// unmap memory
				::vk_unmap_memory(vulkan::device::logical(),
						_memory);
			}

			/* flush */
			auto flush(const ::vk_device_size& offset = 0U,
					   const ::vk_device_size& size = VK_WHOLE_SIZE) -> void {

				// create memory range
				const vk::mapped_memory_range range{
					.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.pNext  = nullptr,
					.memory = _memory,
					.offset = offset,
					.size   = size
				};

				// flush memory
				vk::try_execute<"failed to flush memory">(
						::vk_flush_mapped_memory_ranges,
						vulkan::device::logical(),
						// memory range count
						1U,
						// memory ranges
						&range);
			}

			/* invalidate */
			auto invalidate(const ::vk_device_size& offset = 0U, const ::vk_device_size& size = VK_WHOLE_SIZE) -> void {

				// create memory range
				const vk::mapped_memory_range range{
					.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.pNext  = nullptr,
					.memory = _memory,
					.offset = offset,
					.size   = size
				};

				// invalidate memory
				vk::try_execute<"failed to invalidate mapped memory ranges">(
						::vk_invalidate_mapped_memory_ranges,
						vulkan::device::logical(),
						// memory range count
						1U,
						// memory ranges
						&range);
			}


		private:

			// -- private static methods --------------------------------------

			/* find memory type */
			static auto _find_memory_type(const vk::u32& filter,
										  const vk::memory_property_flags& flags) -> vk::u32 {


				const vk::physical_device& pdevice = vulkan::device::physical();

				vk::physical_device_memory_properties properties;

				::vk_get_physical_device_memory_properties(pdevice, &properties);


				for (vk::u32 i = 0U; i < properties.memoryTypeCount; ++i) {
					if ((filter & (1 << i))
							&& (properties.memoryTypes[i].propertyFlags & flags) == flags) {
						return i;
					}
				}

				throw ve::exception{"failed to find suitable memory type"};
			}


	}; // class device_memory


	// -- documentations ------------------------------------------------------

    // DEVICE_LOCAL_BIT
	// gpu only memory, fastest access

    // HOST_VISIBLE_BIT
	// memory that is host visible, can be mapped

    // HOST_COHERENT_BIT
	// memory that is host coherent, no need to flush

    // HOST_CACHED_BIT
	// memory that is host cached, faster access

    // LAZILY_ALLOCATED_BIT
	// memory that is lazily allocated

    // PROTECTED_BIT
	// memory that is protected


} // namespace vulkan

#endif // ___ENGINE_VULKAN_DEVICE_MEMORY___
