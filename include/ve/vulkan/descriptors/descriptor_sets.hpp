#ifndef ___void_engine_vulkan_descriptor_sets___
#define ___void_engine_vulkan_descriptor_sets___

#include "ve/vk/typedefs.hpp"
#include "ve/memory/malloc.hpp"

#include "ve/vulkan/descriptors/descriptor_pool.hpp"
#include "ve/vulkan/descriptors/descriptor_set_layout.hpp"

#include <stdexcept>


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- D E S C R I P T O R  S E T S ----------------------------------------

	class descriptor_sets final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::descriptor_sets;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vulkan::descriptor_pool _pool;

			/* descriptor sets */
			vk::descriptor_set* _sets;

			/* capacity */
			vk::u32 _capacity;

			/* size */
			vk::u32 _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			descriptor_sets(void) noexcept
			: _pool{}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* pool constructor */
			descriptor_sets(vulkan::descriptor_pool&& pool)
			: _pool{std::move(pool)}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* pool builder constructor */
			descriptor_sets(const vulkan::descriptor_pool::builder& builder)
			: _pool{builder.build()}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* deleted copy constructor */
			descriptor_sets(const ___self&) = delete;

			/* move constructor */
			descriptor_sets(___self&& other) noexcept
			: _pool{std::move(other._pool)},
			  _sets{other._sets},
			  _capacity{other._capacity},
			  _size{other._size} {

				// invalidate other
				other._sets = nullptr;
				other._capacity = 0U;
				other._size = 0U;
			}

			/* destructor */
			~descriptor_sets(void) noexcept {

				// check for null descriptor sets
				if (_sets == nullptr)
					return;

				// check for empty descriptor sets
				if (_size != 0U) {

					// free descriptor sets
					::vk_free_descriptor_sets(
							vulkan::device::logical(),
							_pool.get(),
							_size, _sets);
				}

				// deallocate descriptor sets
				ve::free(_sets);
			}


			// -- public modifiers --------------------------------------------

			/* reserve */
			auto reserve(const vk::u32& capacity) -> void {

				// check if capacity is valid
				if (_capacity > capacity)
					return;

				// call reserve
				___self::_reserve(capacity);
			}

			/* resize */
			auto resize(const size_type size) -> void {

				// less size
				if (size < _size) {

					// free descriptor sets
					::vk_free_descriptor_sets(
							vulkan::device::logical(),
							_pool.get(),
							_size - size, (_sets + size));

					// update size
					_size = size;
					return;
				}

				// more size (reserve)
				if (size > _capacity) {

					___self::_reserve(size);

					// here implement the allocation of the new descriptor sets...

					// set size
					//_size = size;
				}

			}

			/* push */
			auto push(const vulkan::descriptor_set_layout& layout) -> void {

				// check if capacity is valid
				if (_size >= _capacity)
					throw std::out_of_range{"descriptor sets capacity exceeded"};

				// allocate descriptor sets
				const vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool.get(), // descriptor pool
					.descriptorSetCount = 1U, // swapchain size
					.pSetLayouts = &layout.get() // descriptor set layout
				};

				// create descriptor sets
				vk::try_execute<"failed to allocate descriptor sets">(
						::vkAllocateDescriptorSets,
						vulkan::device::logical(),
						&info, (_sets + _size));

				// update size
				++_size;
			}

			/* pop */
			auto pop(void) -> void {

				::vk_free_descriptor_sets(
						vulkan::device::logical(),
						_pool.get(),
						1U, (_sets + _size - 1U));

				// update size
				--_size;
			}

			/* clear */
			auto clear(void) -> void {

				if (_size == 0U)
					return;

				::vk_free_descriptor_sets(
						vulkan::device::logical(),
						_pool.get(),
						_size, _sets);

				// update size
				_size = 0U;
			}

			/* write */
			auto write(const vk::u32& index, const vk::descriptor_buffer_info& binfo) -> void {

				/*
				vk::descriptor_buffer_info buffer_info{
					.buffer = nullptr, // buffer
					.offset = 0U,
					.range = sizeof(0) // must be size of uniform buffer object or struct ) // can be VK_WHOLE_SIZE
				};
				*/

				const vk::write_descriptor_set wdset{
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = nullptr,
					.dstSet = _sets[index],
					.dstBinding = 0U,
					.dstArrayElement = 0U,
					.descriptorCount = 1U,
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.pImageInfo = nullptr,
					.pBufferInfo = &binfo,
					.pTexelBufferView = nullptr
				};

				// update
				::vk_update_descriptor_sets(
						// logical device
						vulkan::device::logical(),
						// descriptor write count
						1U,
						// descriptor writes
						&wdset,
						// descriptor copy count
						0U,
						// descriptor copies
						nullptr);
			}



		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto _init(void) noexcept -> void {
					_sets = nullptr;
					_size = 0;
				_capacity = 0;
			}

			/* free */
			auto _free(void) noexcept -> void {

				// check for empty vector
				if (_sets == nullptr)
					return;

				// deallocate memory
				ve::free(_sets);
			}

			/* reserve */
			auto _reserve(const size_type capacity) -> void {

				// reallocate memory
				_sets = ve::realloc(_sets, capacity);

				// update capacity
				_capacity = capacity;
			}

			/* copy */
			auto _copy_members(const ___self& other) noexcept -> void {
					_sets = other._sets;
					_size = other._size;
				_capacity = other._capacity;
			}

			/* available */
			auto _available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* expand */
			auto _expand(void) noexcept -> size_type {
				return _capacity > 0U ? _capacity * 2U : 1U;
			}



			/* device and size constructor */
			
			/*
			descriptor_sets(const vulkan::descriptor_set_layout& layout,
							const vk::u32& size = 1U)
			: _pool{size}, _sets{nullptr} {


				vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool.get(), // descriptor pool
					.descriptorSetCount = size, // swapchain size
					.pSetLayouts = &layout.get() // descriptor set layout
				};

				// allocate descriptor sets
				_sets = rx::malloc<vk::descriptor_set>(size);


				// create descriptor sets
				vk::try_execute<"failed to allocate descriptor sets">(
						::vkAllocateDescriptorSets,
						vulkan::device::logical(),
						&info, _sets);



				for (vk::u32 i = 0U; i < size; ++i) {

					vk::descriptor_buffer_info buffer_info{
						.buffer = nullptr, // buffer
						.offset = 0U,
						.range = sizeof(0// must be size of uniform buffer object or struct ) // can be VK_WHOLE_SIZE
					};

					vk::write_descriptor_set wdset{
						.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
						.pNext = nullptr,
						.dstSet = _sets[i], // descriptor set
						.dstBinding = 0U,
						.dstArrayElement = 0U,
						.descriptorCount = 1U,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImageInfo = nullptr,
						.pBufferInfo = &buffer_info,
						.pTexelBufferView = nullptr
					};

					vkUpdateDescriptorSets(
							vulkan::device::logical(),
							1U, &wdset, 0U, nullptr);
				}
			}
	*/


	}; // class descriptor_sets

} // namespace vulkan

#endif // ___void_engine_vulkan_descriptor_sets___
