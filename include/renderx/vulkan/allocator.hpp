#ifndef ___RENDERX_VULKAN_ALLOCATOR_HPP___
#define ___RENDERX_VULKAN_ALLOCATOR_HPP___

#include "engine/vk/typedefs.hpp"
#include "engine/vulkan/device.hpp"
#include "engine/vk/utils.hpp"
#include "renderx/hint.hpp"
#include "renderx/memory/memcpy.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	struct allocation final {

		// -- members ---------------------------------------------------------

		/* memory */
		vk::device_memory memory;

		/* size */
		vk::device_size size;

		/* offset */
		vk::device_size offset;

		/* data */
		void* data;


		/* unmap */
		auto unmap(void) noexcept -> void {
			::vk_unmap_memory(vulkan::device::logical(), memory);
		}

		/* memcpy */
		template <typename ___type>
		auto memcpy(const ___type* src) noexcept -> void {

			// map memory
			vk::try_execute<"failed to map memory">(
					::vk_map_memory, vulkan::device::logical(),
					memory, offset, size,
					0U /* reserved */, &data);

			// copy data
			rx::memcpy(data, src, size);

			// unmap memory
			::vk_unmap_memory(vulkan::device::logical(), memory);
		}

	};


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


	/* gpu */
	struct gpu final {
		static constexpr vk::memory_property_flags property = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	};

	/* cpu */
	struct cpu final {
		static constexpr vk::memory_property_flags property = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
	};

	/* cpu coherent */
	struct cpu_coherent final {
		static constexpr vk::memory_property_flags property = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	};

	/* cpu cached */
	struct cpu_cached final {
		static constexpr vk::memory_property_flags property = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
	};


	// -- A L L O C A T O R ---------------------------------------------------

	template <typename ___type>
	class allocator final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::allocator<___type>;


			// -- private constants -------------------------------------------

			/* default block size */
			enum : vk::device_size {
				___DEFAULT_BLOCK_SIZE___ = 256U * 1024U * 1024U
			};


			// -- allocation types --------------------------------------------




			// -- private classes ---------------------------------------------


			/* linear */
			class linear final {


				private:

					// -- private types ---------------------------------------

					/* self type */
					using ___self = vulkan::allocator<___type>::linear;


					// -- private members -------------------------------------

					/* memory */
					vk::device_memory _memory;

					/* offset */
					vk::device_size _offset;


				public:

					/* deleted default constructor */
					linear(void) = delete;

					/* memory type constructor */
					linear(const vk::u32& memory_type_bits)
					: /* uninitialized device memory */ _offset{0U} {

						// create info
						const vk::memory_allocate_info info {
							// structure type
							VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
							// next structure
							nullptr,
							// allocation size
							___DEFAULT_BLOCK_SIZE___,
							// memory type index
							memory_type_bits
						};

						// create device memory
						vk::try_execute<"failed to allocate memory">(
								::vk_allocate_memory,
								vulkan::device::logical(), &info, nullptr, &_memory);

						rx::hint::success("new memory block allocated");
					}

					/* deleted copy constructor */
					linear(const ___self&) = delete;

					/* deleted move constructor */
					linear(___self&&) = delete;

					/* destructor */
					~linear(void) noexcept {

						// release device memory
						::vk_free_memory(
								vulkan::device::logical(), _memory, nullptr);

						rx::hint::info("memory block released");
					}


					// -- public assignment operators -------------------------

					/* deleted copy assignment operator */
					auto operator=(const ___self&) -> ___self& = delete;

					/* deleted move assignment operator */
					auto operator=(___self&&) -> ___self& = delete;


					/* allocate */
					auto allocate(const vk::memory_requirements& requirements) -> vulkan::allocation {


						vk::device_size aligned_offset = (_offset + requirements.alignment - 1U)
														& ~(requirements.alignment - 1U);

						// check if memory is out of bounds
						if (aligned_offset + requirements.size > ___DEFAULT_BLOCK_SIZE___) {
							throw "out of memory";
							// not implemented...
							// will expand memory with linked list ?
						}

						_offset = aligned_offset + requirements.size;

						return {
							_memory,
							requirements.size,
							aligned_offset,
							nullptr
						};
					}

					/* reset */
					auto reset(void) noexcept -> void {
						_offset = 0U;
					}

					/* memory */
					auto memory(void) const noexcept -> const vk::device_memory& {
						return _memory;
					}

			};



			// -- private members ---------------------------------------------

			/* allocators */
			___self::linear* _allocators[VK_MAX_MEMORY_TYPES];


		public:

			// -- public lifecycle -------------------------------------------

			/* default constructor */
			allocator(void)
			: _allocators{} {
			}

			/* destructor */
			~allocator(void) noexcept {

				for (vk::u32 i = 0U; i < VK_MAX_MEMORY_TYPES; ++i) {
					if (_allocators[i] == nullptr)
						continue;

					delete _allocators[i];
				}

			}


			auto allocate_buffer(const vk::buffer& buffer/*, const vk::memory_property_flags& properties*/) -> vulkan::allocation {

				vk::memory_requirements requirements;

				// get buffer memory requirements
				::vk_get_buffer_memory_requirements(vulkan::device::logical(), buffer, &requirements);

				// find memory type
				const auto memory_type = ___self::_find_memory_type(requirements.memoryTypeBits/*, ___type::property*/);


				// check if allocator is valid
				if (_allocators[memory_type] == nullptr) {
					_allocators[memory_type] = new linear{memory_type};
				}

				// allocate memory
				auto alloc = _allocators[memory_type]->allocate(requirements);

				// bind memory
				vk::try_execute<"failed to bind buffer memory">(
						::vk_bind_buffer_memory, vulkan::device::logical(),
						buffer, alloc.memory, alloc.offset);

				//// map memory
				//vk::try_execute<"failed to map memory">(
				//		::vk_map_memory, vulkan::device::logical(),
				//		alloc.memory, alloc.offset, alloc.size,
				//		0U /* reserved */, &alloc.data);

				return alloc;
			}




			/* find memory type */
			static auto _find_memory_type(const vk::u32& mem_type/*, vk::memory_property_flags flags*/) -> vk::u32 {


				constexpr auto flags = ___type::property;

				vk::physical_device_memory_properties properties;

				// get physical device memory properties
				::vk_get_physical_device_memory_properties(vulkan::device::physical(), &properties);

				// loop over memory types
				for (vk::u32 i = 0U; i < properties.memoryTypeCount; ++i) {

					if (((mem_type & (1U << i)) != 0U)
						&& ((properties.memoryTypes[i].propertyFlags & flags) == flags))
						return i;
				}

				throw "failed to find suitable memory type";
			}


	};

} // namespace vulkan


#endif // ___RENDERX_VULKAN_ALLOCATOR_HPP___
