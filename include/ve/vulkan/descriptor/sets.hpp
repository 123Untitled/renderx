#ifndef ___ve_vulkan_descriptor_sets___
#define ___ve_vulkan_descriptor_sets___

#include "ve/vk/typedefs.hpp"
#include "ve/memory/malloc.hpp"

#include "ve/vulkan/descriptor/pool.hpp"
#include "ve/vulkan/descriptor/set.hpp"

#include <stdexcept>
#include <iostream>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk::descriptor {


	// -- S E T S -------------------------------------------------------------

	class sets final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::sets;


			// -- private members ---------------------------------------------

			/* descriptor pool */
			vk::descriptor::pool _pool;

			/* descriptor sets */
			::vk_descriptor_set* _sets;

			/* capacity */
			vk::u32 _capacity;

			/* size */
			vk::u32 _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			sets(void) noexcept
			: _pool{}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* pool constructor */
			sets(vk::descriptor::pool&& pool)
			: _pool{std::move(pool)}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* pool builder constructor */
			sets(const vk::descriptor::pool::builder& builder)
			: _pool{builder.build()}, _sets{nullptr}, _capacity{0U}, _size{0U} {
			}

			/* deleted copy constructor */
			sets(const self&) = delete;

			/* move constructor */
			sets(self&& other) noexcept
			: _pool{std::move(other._pool)},
			  _sets{other._sets},
			  _capacity{other._capacity},
			  _size{other._size} {

				// invalidate other
				other._init();
			}

			/* destructor */
			~sets(void) noexcept {

				// check for null descriptor sets
				if (_sets == nullptr)
					return;

				// check for empty descriptor sets
				if (_size != 0U) {

					// free descriptor sets
					self::_free_descriptor_sets(_sets, _size);
				}

				// deallocate descriptor sets
				ve::free(_sets);
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// free descriptor sets
				if (_size != 0U)
					self::_free_descriptor_sets(_sets, _size);

				// deallocate descriptor sets
				if (_sets != nullptr)
					ve::free(_sets);

				// move pool
				_pool.operator=(std::move(other._pool));

				// copy members
				self::_copy_members(other);

				// invalidate other
				other._init();

				// done
				return *this;
			}

			// -- public subscript operators ----------------------------------

			/* [] operator */
			auto operator[](const size_type& index) const noexcept -> vk::descriptor::set {
				return vk::descriptor::set{*(_sets + index)};
			}


			// -- public accessors --------------------------------------------

			/* data */
			auto data(void) const noexcept -> ::vk_descriptor_set* {
				return _sets;
			}

			/* data */
			auto data(const size_type& index) const noexcept -> ::vk_descriptor_set* {
				return _sets + index;
			}



			// -- public modifiers --------------------------------------------

			/* reserve */
			auto reserve(const vk::u32& capacity) -> void {

				// check if capacity is valid
				if (_capacity > capacity)
					return;

				// call reserve
				self::_reserve(capacity);
			}

			/* push */
			auto push(const ::vk_descriptor_set_layout& layout) -> void {

				// check if capacity is valid
				if (self::_available() == 0U)
					self::_reserve(self::_expand());

				// allocate descriptor sets
				self::_allocate_descriptor_sets(layout, 1U);

				// update size
				++_size;
			}

			/* pop */
			auto pop(void) -> void {

				if (_size == 0U)
					return;

				// free last descriptor set (and update size)
				self::_free_descriptor_sets((_sets + --_size), 1U);
			}

			/* clear */
			auto clear(void) -> void {

				if (_size == 0U)
					return;

				// free descriptor sets
				self::_free_descriptor_sets(_sets, _size);

				// update size
				_size = 0U;
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto _init(void) noexcept -> void {
					_sets = nullptr;
					_size = 0U;
				_capacity = 0U;
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
			auto _free_descriptor_sets(::vk_descriptor_set* sets,
										const size_type size) noexcept -> void {

				// this command does not return any failure codes
				static_cast<void>(::vk_free_descriptor_sets(
										vulkan::device::logical(),
										_pool,
										size,
										sets));
			}

			/* allocate descriptor sets */
			auto _allocate_descriptor_sets(const ::vk_descriptor_set_layout& layout,
											const size_type size) -> void {

				// allocate descriptor sets
				const ::vk_descriptor_set_allocate_info info{
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext = nullptr,
					.descriptorPool = _pool, // descriptor pool
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
			auto _copy_members(const self& other) noexcept -> void {
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

	}; // class descriptor_sets

} // namespace vk::descriptor

#endif // ___ve_vulkan_descriptor_sets___
