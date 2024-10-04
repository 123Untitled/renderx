/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ENGINE_VULKAN_BUFFER_HPP
#define ENGINE_VULKAN_BUFFER_HPP

#include "engine/vk/shared.hpp"
#include "engine/vertex/vertex.hpp"
#include "engine/vulkan/device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- V E R T E X  B U F F E R --------------------------------------------

	class buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vk::shared<vk::buffer> _buffer;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			buffer(void) noexcept = default;

			/* default constructor */
			template <typename... ___params>
			buffer(const vk::shared<vk::device>& ___dv,
				   const vk::vector<engine::vertex<___params...>>& ___vtx)
			: _buffer{___dv,
				vk::buffer_info{
					// structure type
					VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
					// next structure
					nullptr,
					// flags
					0U,
					// size of buffer
					sizeof(engine::vertex<___params...>) * ___vtx.size(),
					// usage flags
					VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
					// sharing mode (exclusive or concurrent)
					VK_SHARING_MODE_EXCLUSIVE,
					// queue family index count (not implemented yet...)
					0U,
					// queue family indices (not implemented yet...)
					nullptr
				}} {
			}

			/* copy constructor */
			buffer(const ___self&) noexcept = default;

			/* move constructor */
			buffer(___self&&) noexcept = default;

			/* destructor */
			~buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::shared<vk::buffer>& conversion operator */
			operator vk::shared<vk::buffer>&() noexcept {
				return _buffer;
			}

			/* const vk::shared<vk::buffer>& conversion operator */
			operator const vk::shared<vk::buffer>&() const noexcept {
				return _buffer;
			}

	}; // class buffer





	// -- D E V I C E  M E M O R Y --------------------------------------------

	class device_memory final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::device_memory;


			// -- private members ---------------------------------------------

			/* memory */
			vk::shared<vk::device_memory> _memory;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			device_memory(void) noexcept = default;

			/* buffer constructor */
			device_memory(const vk::shared<vk::buffer>& ___bf, const vulkan::device& ___dv)
			: _memory{___self::_create_device_memory(___bf, ___dv)} {
			}



			template <typename... ___params>
			auto bind_and_map(const vk::shared<vk::buffer>& ___bf,
							  const vk::vector<engine::vertex<___params...>>& ___vtx) -> void {

				// bind
				vk::bind_buffer_memory(___bf.dependency(), ___bf, _memory /*, offset */);
				// 4th parameter is offset in memory, but we want to bind from the beginning
				// its used for memory allocation of multiple buffers in one memory block
				// must be divisible by 'requirements.alignment'
				// very useful for optimization !

				// map memory
				void* data = vk::map_memory(___bf.dependency(), _memory, 0U, VK_WHOLE_SIZE);


				std::memcpy(
						data,
						___vtx.data(),
						sizeof(engine::vertex<___params...>) * ___vtx.size()
				);

				// unmap memory
				vk::unmap_memory(___bf.dependency(), _memory);

				// to see later :
				//::vkFlushMappedMemoryRanges(device, 1, &(::VkMappedMemoryRange{
				//	.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
				//	.pNext  = nullptr,
				//	.memory = _memory,
				//	.offset = 0,
				//	.size   = VK_WHOLE_SIZE
				//}));
				// ::vkInvalidateMappedMemory
			}

		private:

			// -- private static methods --------------------------------------

			/* create device memory */
			static auto _create_device_memory(const vk::shared<vk::buffer>& ___bf,
											  const vulkan::device& ___dv) -> vk::shared<vk::device_memory> {


				const auto ___reqs = vk::get_buffer_memory_requirements(
					___bf.dependency(),
					___bf);

				const vk::memory_allocate_info info{
					// structure type
					VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					// next structure
					nullptr,
					// allocation size
					___reqs.size,
					// memory type index
					___self::_find_memory_type(
									___dv.physical_device(),
							___reqs.memoryTypeBits,
									VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
									| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
				};

				return vk::shared<vk::device_memory>{___bf.dependency(), info};
			}


			/* find memory type */
			static auto _find_memory_type(const vk::physical_device& ___pd,
										  const vk::u32& filter,
										  const vk::memory_property_flags& flags) -> vk::u32 {

				const auto properties = vk::get_physical_device_memory_properties(___pd);


				for (vk::u32 i = 0U; i < properties.memoryTypeCount; ++i) {
					if ((filter & (1 << i))
							&& (properties.memoryTypes[i].propertyFlags & flags) == flags) {
						return i;
					}
				}

				throw engine::exception{"failed to find suitable memory type"};
			}


	}; // class device_memory

} // namespace vulkan

#endif // ENGINE_VULKAN_BUFFER_HPP
