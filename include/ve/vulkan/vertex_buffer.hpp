/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_VULKAN_VERTEX_BUFFER___
#define ___RENDERX_VULKAN_VERTEX_BUFFER___

#include "ve/vertex/vertex.hpp"
#include "ve/vulkan/buffer.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vulkan/allocator.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- V E R T E X  B U F F E R --------------------------------------------

	class vertex_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::vertex_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;

			/* vertex count */
			vk::u32 _count;

			/* allocation */
			vulkan::allocation _alloc;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			vertex_buffer(void) noexcept = default;

			/* vector constructor */
			template <typename... ___params>
			vertex_buffer(const vk::vector<ve::vert3x>& vertices)
			:
			  // create buffer
			  _buffer(sizeof(ve::vert3x) * vertices.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT),
			  // set vertex count
			  _count((vk::u32)vertices.size()),
			  // allocate memory
			  _alloc(vulkan::allocator<vulkan::cpu_coherent>::allocate_buffer(_buffer.underlying())) {

				// copy data
				_alloc.memcpy(vertices.data());
			}

			/* deleted copy constructor */
			vertex_buffer(const ___self&) = delete;

			/* move constructor */
			vertex_buffer(___self&&) noexcept = default;

			/* destructor */
			~vertex_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* underlying */
			auto underlying(void) const noexcept -> const vk::buffer& {
				return _buffer.underlying();
			}

			/* count */
			auto count(void) const noexcept -> vk::u32 {
				return _count;
			}

	}; // class vertex_buffer

} // namespace vulkan

#endif // ___RENDERX_VULKAN_VERTEX_BUFFER___
