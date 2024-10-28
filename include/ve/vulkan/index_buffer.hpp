/* ------------------------------------------------------------------------- */
/*        :::::::::  :::::::::: ::::    ::: :::::::::  :::::::::: :::::::::  */
/*       :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        :+:    :+:  */
/*      +:+    +:+ +:+        :+:+:+  +:+ +:+    +:+ +:+        +:+    +:+   */
/*     +#++:++#:  +#++:++#   +#+ +:+ +#+ +#+    +:+ +#++:++#   +#++:++#:     */
/*    +#+    +#+ +#+        +#+  +#+#+# +#+    +#+ +#+        +#+    +#+     */
/*   #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        #+#    #+#      */
/*  ###    ### ########## ###    #### #########  ########## ###    ###       */
/* ------------------------------------------------------------------------- */

#ifndef ___RENDERX_VERTEX_INDEX_BUFFER___
#define ___RENDERX_VERTEX_INDEX_BUFFER___

#include "ve/vulkan/buffer.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/types.hpp"
#include "ve/vulkan/allocator.hpp"


// -- V U L K A N -------------------------------------------------------------

namespace vulkan {


	// -- I N D E X  B U F F E R ----------------------------------------------

	class index_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::index_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;

			/* index type */
			vk::index_type _type;

			/* index count */
			vk::u32 _count;

			/* allocation */
			vulkan::allocation _alloc;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			index_buffer(void) noexcept = default;

			/* u16 vector constructor */
			index_buffer(const std::vector<rx::u16>& indices)
			: _buffer(sizeof(rx::u16) * indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT),
			  _type{VK_INDEX_TYPE_UINT16},
			  _count((vk::u32)indices.size()),
			  _alloc{vulkan::allocator<vulkan::cpu_coherent>::allocate_buffer(_buffer.underlying())} {

				// copy data
				_alloc.memcpy(indices.data());
			}

			/* u32 vector constructor */
			index_buffer(const std::vector<rx::u32>& indices)
			: _buffer(sizeof(rx::u32) * indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT),
			  _type{VK_INDEX_TYPE_UINT32},
			  _count((vk::u32)indices.size()),
			  _alloc{vulkan::allocator<vulkan::cpu_coherent>::allocate_buffer(_buffer.underlying())} {

				// copy data
				_alloc.memcpy(indices.data());
			}

			/* deleted copy constructor */
			index_buffer(const ___self&) = delete;

			/* move constructor */
			index_buffer(___self&&) noexcept = default;

			/* destructor */
			~index_buffer(void) noexcept = default;


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

			/* index type */
			auto type(void) const noexcept -> vk::index_type {
				return _type;
			}

	}; // class index_buffer

} // namespace vulkan

#endif // ___RENDERX_VERTEX_INDEX_BUFFER___
