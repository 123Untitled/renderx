#ifndef ___ve_vulkan_descriptor_set___
#define ___ve_vulkan_descriptor_set___

#include "ve/vulkan/device.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/descriptor/allocator.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk::descriptor {


	// -- S E T ---------------------------------------------------------------

	class set final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = vk::descriptor::set;


			// -- private members ---------------------------------------------

			/* descriptor set */
			::vk_descriptor_set _set;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			set(void) noexcept = default;

			/* set constructor */
			set(const ::vk_descriptor_set& set) noexcept
			: _set{set} {
			}

			/* layout constructor */
			set(const ::vk_descriptor_set_layout& layout)
			: _set{vk::descriptor::allocator::shared().allocate(layout)} {
			}

			/* copy constructor */
			set(const self&) noexcept = default;

			/* move constructor */
			set(self&&) noexcept = default;

			/* destructor */
			~set(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			operator const ::vk_descriptor_set&(void) const noexcept {
				return _set;
			}


			// -- public methods ----------------------------------------------

			/* bind */
			auto bind(const vk::command_buffer& encoder,
					  const ::vk_pipeline_layout& layout,
					  const vk::u32& first_set = 0U,
					  const vk::pipeline_bind_point& point = VK_PIPELINE_BIND_POINT_GRAPHICS
					  ) const noexcept -> void {

				// bind descriptor sets
				::vk_cmd_bind_descriptor_sets(
						// command buffer
						encoder,
						// bind point
						point,
						// pipeline layout
						layout,
						// first set
						first_set,
						// descriptor set
						1U, &_set,
						// dynamic offset
						0U, nullptr);
			}


			// -- public modifiers --------------------------------------------

			/* write */
			auto write(const ::vk_descriptor_buffer_info& binfo,
					   const ::vk_descriptor_type& type) -> void {

				const ::vk_write_descriptor_set wdset{
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = nullptr,
					.dstSet = _set,
					.dstBinding = 0U,
					.dstArrayElement = 0U,
					.descriptorCount = 1U,
					.descriptorType = type,
					.pImageInfo = nullptr,
					.pBufferInfo = &binfo,
					.pTexelBufferView = nullptr
				};

				// update
				::vk_update_descriptor_sets(
						// logical device
						vulkan::device::logical(),
						// descriptor writes
						1U, &wdset,
						// descriptor copies
						0U, nullptr);
			}

			/* write */
			auto write(const ::vk_descriptor_image_info& iinfo,
					   const ::vk_descriptor_type& type) -> void {

				const ::vk_write_descriptor_set wdset{
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = nullptr,
					.dstSet = _set,
					.dstBinding = 0U,
					.dstArrayElement = 0U,
					.descriptorCount = 1U,
					.descriptorType = type,
					.pImageInfo = &iinfo,
					.pBufferInfo = nullptr,
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


			// -- forward declarations ----------------------------------------

			/* layout */
			class layout;

	}; // class set

} // namespace vk::descriptor

#endif // ___ve_vulkan_descriptor_set___
