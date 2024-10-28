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

			/* value type */
			using value_type      = vk::descriptor_set;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer         = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = vk::u32;


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
				___self::_init();
			}

			/* destructor */
			~descriptor_sets(void) noexcept {

				// check for null descriptor sets
				if (_sets == nullptr)
					return;

				// check for empty descriptor sets
				if (_size != 0U) {

					// free descriptor sets
					___self::_free_descriptor_sets(_sets, _size);
				}

				// deallocate descriptor sets
				ve::free(_sets);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */ // not implemented yet...
			auto operator=(___self&& other) noexcept -> ___self& = delete;


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
			auto resize(const vulkan::descriptor_set_layout& layout,
						const size_type size) -> void {

				// less size
				if (size < _size) {

					// free descriptor sets
					___self::_free_descriptor_sets(
									(_sets + size),
									(_size - size));

					// update size
					_size = size;
					return;
				}

				// more size (reserve)
				if (size > _size) {

					// check if capacity is valid
					if (___self::_available() < size)
						___self::_reserve(size);

					// allocate descriptor sets
					___self::_allocate_descriptor_sets(layout.get(),
													(size - _size));

					// update size
					_size = size;
				}

			}

			/* push */
			auto push(const vulkan::descriptor_set_layout& layout) -> void {

				// check if capacity is valid
				if (___self::_available() == 0U)
					___self::_reserve(___self::_expand());

				// allocate descriptor sets
				const vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool.get(), // descriptor pool
					.descriptorSetCount = 1U, // swapchain size
					.pSetLayouts = &layout.get() // descriptor set layout
				};

				// allocate descriptor sets
				___self::_allocate_descriptor_sets(layout.get(), 1U);

				// update size
				++_size;
			}

			/* pop */
			auto pop(void) -> void {

				if (_size == 0U)
					return;

				// free last descriptor set (and update size)
				___self::_free_descriptor_sets((_sets + --_size), 1U);
			}

			/* clear */
			auto clear(void) -> void {

				if (_size == 0U)
					return;

				// free descriptor sets
				___self::_free_descriptor_sets(_sets, _size);

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

			/* free descriptor sets */
			auto _free_descriptor_sets(const_pointer sets,
									const size_type size) noexcept -> void {

				// this command does not return any failure codes
				static_cast<void>(::vk_free_descriptor_sets(
										vulkan::device::logical(),
										_pool.get(),
										size,
										sets));
			}

			/* allocate descriptor sets */
			auto _allocate_descriptor_sets(const vk::descriptor_set_layout& layout,
											const size_type size) noexcept -> void {

				// allocate descriptor sets
				const vk::descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool.get(), // descriptor pool
					.descriptorSetCount = size, // swapchain size
					.pSetLayouts = &layout // descriptor set layout
				};

				vk::try_execute<"failed to allocate descriptor sets">(
						::vkAllocateDescriptorSets,
						vulkan::device::logical(),
						&info, (_sets + _size));
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
