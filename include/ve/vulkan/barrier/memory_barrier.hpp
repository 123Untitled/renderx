#ifndef ___ve_vulkan_memory_barrier___
#define ___ve_vulkan_memory_barrier___

#include "ve/vk/typedefs.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- M E M O R Y  B A R R I E R ------------------------------------------

	class memory_barrier final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::memory_barrier;


			// -- private members ---------------------------------------------

			/* barrier */
			vk::memory_barrier _barrier;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			memory_barrier(void) noexcept
			: memory_barrier{VK_ACCESS_NONE,
							 VK_ACCESS_NONE} {
			}

			/* parameters constructor */
			memory_barrier(const vk::access_flags& src,
						   const vk::access_flags& dst) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src,
				// destination access mask
				.dstAccessMask = dst} {
			}

			/* transition constructor */
			memory_barrier(const self& src,
						   const vk::access_flags& dst) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src._barrier.dstAccessMask,
				// destination access mask
				.dstAccessMask = dst} {
			}

			/* copy constructor */
			memory_barrier(const self&) noexcept = default;

			/* move constructor */
			memory_barrier(self&&) noexcept = default;

			/* destructor */
			~memory_barrier(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* access masks */
			auto access_masks(const vk::access_flags& src,
							  const vk::access_flags& dst) noexcept -> void {
				_barrier.srcAccessMask = src;
				_barrier.dstAccessMask = dst;
			}


			// -- public conversion operators ---------------------------------

			/* vk::memory_barrier& conversion operator */
			operator vk::memory_barrier&(void) noexcept {
				return _barrier;
			}

			/* const vk::memory_barrier& conversion operator */
			operator const vk::memory_barrier&(void) const noexcept {
				return _barrier;
			}

			/* vk::memory_barrier* conversion operator */
			operator vk::memory_barrier*(void) noexcept {
				return &_barrier;
			}

			/* const vk::memory_barrier* conversion operator */
			operator const vk::memory_barrier*(void) const noexcept {
				return &_barrier;
			}


			// -- forward declarations ----------------------------------------

			/* image */
			class image;

			/* buffer */
			class buffer;

	}; // class memory_barrier


	// -- I M A G E -----------------------------------------------------------

	class memory_barrier::image final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::memory_barrier::image;


			// -- private members ---------------------------------------------

			/* barrier */
			vk::image_memory_barrier _barrier;


		public:

			/* default constructor */
			image(void) noexcept
			: image{VK_ACCESS_NONE,
					VK_ACCESS_NONE,
					VK_IMAGE_LAYOUT_UNDEFINED,
					VK_IMAGE_LAYOUT_UNDEFINED,
					nullptr,
					VK_IMAGE_ASPECT_NONE} {
			}

			/* parameters constructor */
			image(const vk::access_flags& src_access,
				  const vk::access_flags& dst_access,
				  const vk::image_layout& old_layout,
				  const vk::image_layout& new_layout,
				  const vk::image& image,
				  const vk::image_aspect_flags& aspect) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src_access,
				// destination access mask
				.dstAccessMask = dst_access,
				// old layout
				.oldLayout = old_layout,
				// new layout
				.newLayout = new_layout,
				// source queue family index
				.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
				// destination queue family index
				.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
				// image
				.image = image,
				// subresource range
				.subresourceRange = {
					// aspect mask
					.aspectMask = aspect,
					// base mip level
					.baseMipLevel = 0U,
					// level count
					.levelCount = 1U,
					// base array layer
					.baseArrayLayer = 0U,
					// layer count
					.layerCount = 1U
				}} {
			}

			/* transition constructor */
			image(const self& src,
				  const vk::access_flags& dst_access,
				  const vk::image_layout& new_layout) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src._barrier.dstAccessMask,
				// destination access mask
				.dstAccessMask = dst_access,
				// old layout
				.oldLayout = src._barrier.newLayout,
				// new layout
				.newLayout = new_layout,
				// source queue family index
				.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
				// destination queue family index
				.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
				// image
				.image = src._barrier.image,
				// subresource range
				.subresourceRange = src._barrier.subresourceRange} {
			}

			/* copy constructor */
			image(const self&) noexcept = default;

			/* move constructor */
			image(self&&) noexcept = default;

			/* destructor */
			~image(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public modifiers --------------------------------------------

			/* access masks */
			auto access_masks(const vk::access_flags& src,
							  const vk::access_flags& dst) noexcept -> self& {
				_barrier.srcAccessMask = src;
				_barrier.dstAccessMask = dst;
				return *this;
			}

			/* layouts */
			auto layouts(const vk::image_layout& old_layout,
						 const vk::image_layout& new_layout) noexcept -> self& {
				_barrier.oldLayout = old_layout;
				_barrier.newLayout = new_layout;
				return *this;
			}

			/* queue families */
			auto queue_families(const vk::u32& src_family,
								const vk::u32& dst_family) noexcept -> self& {
				_barrier.srcQueueFamilyIndex = src_family;
				_barrier.dstQueueFamilyIndex = dst_family;
				return *this;
			}


			// -- public methods ----------------------------------------------

			/* pipeline barrier */
			auto pipeline_barrier(const vk::command_buffer& buffer,
								  const vk::pipeline_stage_flags& src_stage,
								  const vk::pipeline_stage_flags& dst_stage,
								  const vk::dependency_flags& dependency = 0U) const noexcept -> void {
				// pipeline barrier
				::vk_cmd_pipeline_barrier(
						// command buffer
						buffer,
						// source stage
						src_stage,
						// destination stage
						dst_stage,
						// dependency flags
						dependency,
						// memory barrier count
						0U,
						// memory barriers
						nullptr,
						// buffer memory barrier count
						0U,
						// buffer memory barriers
						nullptr,
						// image memory barrier count
						1U,
						// image memory barriers
						&_barrier);
			}


			// -- public conversion operators ---------------------------------

			/* vk::image_memory_barrier& conversion operator */
			operator vk::image_memory_barrier&(void) noexcept {
				return _barrier;
			}

			/* const vk::image_memory_barrier& conversion operator */
			operator const vk::image_memory_barrier&(void) const noexcept {
				return _barrier;
			}

			/* vk::image_memory_barrier* conversion operator */
			operator vk::image_memory_barrier*(void) noexcept {
				return &_barrier;
			}

			/* const vk::image_memory_barrier* conversion operator */
			operator const vk::image_memory_barrier*(void) const noexcept {
				return &_barrier;
			}

	}; // class memory_barrier::image


	// -- B U F F E R ---------------------------------------------------------

	class memory_barrier::buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::memory_barrier::buffer;


			// -- private members ---------------------------------------------

			/* barrier */
			vk::buffer_memory_barrier _barrier;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			buffer(void) noexcept
			: buffer{VK_ACCESS_NONE,
					 VK_ACCESS_NONE,
					 VK_QUEUE_FAMILY_IGNORED,
					 VK_QUEUE_FAMILY_IGNORED,
					 nullptr, 0U,
					 VK_WHOLE_SIZE} {
			}

			/* parameters constructor */
			buffer(const vk::access_flags& src_access,
				   const vk::access_flags& dst_access,
				   const vk::u32& src_queue_family,
				   const vk::u32& dst_queue_family,
				   const vk::buffer& buffer,
				   const ::vk_device_size& offset,
				   const ::vk_device_size& size) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src_access,
				// destination access mask
				.dstAccessMask = dst_access,
				// source queue family index
				.srcQueueFamilyIndex = src_queue_family,
				// destination queue family index
				.dstQueueFamilyIndex = dst_queue_family,
				// buffer
				.buffer = buffer,
				// offset
				.offset = offset,
				// size
				.size = size} {
			}

			/* transition constructor */
			buffer(const self& src,
				   const vk::access_flags& dst_access) noexcept
			: _barrier{
				// structure type
				.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				// next structure
				.pNext = nullptr,
				// source access mask
				.srcAccessMask = src._barrier.dstAccessMask,
				// destination access mask
				.dstAccessMask = dst_access,
				// source queue family index
				.srcQueueFamilyIndex = src._barrier.dstQueueFamilyIndex,
				// destination queue family index
				.dstQueueFamilyIndex = src._barrier.srcQueueFamilyIndex,
				// buffer
				.buffer = src._barrier.buffer,
				// offset
				.offset = src._barrier.offset,
				// size
				.size = src._barrier.size} {
			}

			/* copy constructor */
			buffer(const self&) noexcept = default;

			/* move constructor */
			buffer(self&&) noexcept = default;

			/* destructor */
			~buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public conversion operators ---------------------------------

			/* vk::buffer_memory_barrier& conversion operator */
			operator vk::buffer_memory_barrier&(void) noexcept {
				return _barrier;
			}

			/* const vk::buffer_memory_barrier& conversion operator */
			operator const vk::buffer_memory_barrier&(void) const noexcept {
				return _barrier;
			}

			/* vk::buffer_memory_barrier* conversion operator */
			operator vk::buffer_memory_barrier*(void) noexcept {
				return &_barrier;
			}

			/* const vk::buffer_memory_barrier* conversion operator */
			operator const vk::buffer_memory_barrier*(void) const noexcept {
				return &_barrier;
			}

	}; // class memory_barrier::buffer


	// -- assertions ----------------------------------------------------------

	/* memory barrier */
	static_assert(sizeof(ve::memory_barrier)
				== sizeof(vk::memory_barrier), "memory barrier size mismatch");

	/* image memory barrier */
	static_assert(sizeof(ve::memory_barrier::image)
				== sizeof(vk::image_memory_barrier), "image memory barrier size mismatch");

	/* buffer memory barrier */
	static_assert(sizeof(ve::memory_barrier::buffer)
				== sizeof(vk::buffer_memory_barrier), "buffer memory barrier size mismatch");

} // namespace ve

#endif // ___ve_vulkan_memory_barrier___
