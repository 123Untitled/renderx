#ifndef ___ve_vulkan_descriptor_allocator___
#define ___ve_vulkan_descriptor_allocator___

#include "ve/vk/unique.hpp"
#include "ve/vk/array.hpp"
#include "ve/utility/exchange.hpp"
#include <vector>
#include <iostream>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk::descriptor {


	// -- A L L O C A T O R ---------------------------------------------------

	class allocator final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::allocator;


			// -- private constants -------------------------------------------

			enum : vk::u32 {
				BLOCK_SIZE = 1024U
			};


			// -- private members ---------------------------------------------

			/* current pool */
			::vk_descriptor_pool _current;

			/* used pools */
			std::vector<vk::unique<::vk_descriptor_pool>> _used;

			/* free pools */
			std::vector<vk::unique<::vk_descriptor_pool>> _free;


			// -- private methods ---------------------------------------------



			auto _new_pool(const vk::u32& count = BLOCK_SIZE,
						   const ::vk_descriptor_pool_create_flags& flags
						   = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT) -> vk::unique<::vk_descriptor_pool> {

				struct weight final {
					const ::vk_descriptor_type type;
					const float multiplier;
				};

				constexpr vk::array weigths {
					weight{VK_DESCRIPTOR_TYPE_SAMPLER,                0.5f},
					weight{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4.0f},
					weight{VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          4.0f},
					weight{VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1.0f},
					weight{VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1.0f},
					weight{VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1.0f},
					weight{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         2.0f},
					weight{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         2.0f},
					weight{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1.0f},
					weight{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1.0f},
					weight{VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       0.5f}
				};


				vk::array<::vk_descriptor_pool_size, weigths.size()>
					pool_sizes;


				for (vk::u32 i = 0U; i < weigths.size(); ++i) {
					pool_sizes[i] = {
						.type = weigths[i].type,
						.descriptorCount = static_cast<vk::u32>(weigths[i].multiplier
											* static_cast<float>(count))
					};
				}


				// create info
				const ::vk_descriptor_pool_create_info info{
					// type of structure
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
					// next structure
					.pNext = nullptr,
					// flags
					.flags = flags,
					// max sets
					.maxSets = count,
					// pool size count
					.poolSizeCount = pool_sizes.size(),
					// pool sizes
					.pPoolSizes = pool_sizes.data()
				};

				// create descriptor pool
				return vk::make_unique<::vk_descriptor_pool>(info);
			}

			/* update current */
			auto _update_current(void) -> void {

				// check for available pools
				if (_free.empty() == true) {

					// create new pool
					_used.emplace_back(_new_pool());
				}
				else {

					// take pool from free list
					_used.emplace_back(std::move(_free.back()));

					// remove from free list
					_free.pop_back();
				}

				// update current
				_current = _used.back();
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			allocator(void) noexcept
			: _current{nullptr}, _used{}, _free{} {
			}

			/* deleted copy constructor */
			allocator(const self&) = delete;

			/* move constructor */
			allocator(self&& other) noexcept
			: _current{ve::exchange(other._current, nullptr)},
			  _used{std::move(other._used)}, _free{std::move(other._free)} {
			}

			/* destructor */
			~allocator(void) noexcept = default;



			// -- public methods ----------------------------------------------

			/* allocate */
			auto allocate(const ::vk_descriptor_set_layout& layout) -> ::vk_descriptor_set {

				// check for current pool
				if (_current == nullptr) {
					std::cout << "current is null" << std::endl;
					_update_current();
				}

				// create info
				::vk_descriptor_set_allocate_info info{
					// type of structure
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					// next structure
					.pNext = nullptr,
					// descriptor pool
					.descriptorPool = _current,
					// descriptor set count
					.descriptorSetCount = 1U,
					// descriptor set layouts
					.pSetLayouts = &layout
				};

				::vk_descriptor_set set;

				// allocate descriptor set
				vk::result result = ::vk_allocate_descriptor_sets(
					vulkan::device::logical(), &info, &set);

				// check result
				switch (result) {

					// success
					case VK_SUCCESS:
						return set;

					// pool error
					case VK_ERROR_FRAGMENTED_POOL:
					case VK_ERROR_OUT_OF_POOL_MEMORY:

						// grab new pool
						_update_current();

						// update info
						info.descriptorPool = _current;

						// try again
						result = ::vk_allocate_descriptor_sets(
							vulkan::device::logical(), &info, &set);

						// check result and return
						if (result == VK_SUCCESS)
							return set;

					// handle error
					default:
						throw vk::exception("failed to allocate descriptor set", result);
				}

				// unreachable
			}

			/* reset */
			auto reset(void) -> void {

				// loop over used pools
				while (_used.empty() == false) {

					// always return vk_success
					static_cast<void>(::vk_reset_descriptor_pool(
						vulkan::device::logical(), _used.back(), 0U));

					// move to free list
					_free.emplace_back(std::move(_used.back()));

					// remove from used list
					_used.pop_back();
				}

				// reset current
				_current = nullptr;
			}


			// -- public static methods ---------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self instance;
				return instance;
			}

	}; // class allocator

} // namespace vk

#endif // ___ve_vulkan_descriptor_allocator___
