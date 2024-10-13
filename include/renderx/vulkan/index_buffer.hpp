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

#include "renderx/vulkan/buffer.hpp"
#include "renderx/vk/typedefs.hpp"
#include "renderx/types.hpp"


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


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			index_buffer(void) noexcept = default;

			/* u16 vector constructor */
			index_buffer(const vk::vector<rx::u16>& indices)
			: _buffer(sizeof(rx::u16) * indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT),
			  _type{VK_INDEX_TYPE_UINT16},
			  _count((vk::u32)indices.size()) {
			}

			/* u32 vector constructor */
			index_buffer(const vk::vector<rx::u32>& indices)
			: _buffer(sizeof(rx::u32) * indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT),
			  _type{VK_INDEX_TYPE_UINT32},
			  _count((vk::u32)indices.size()) {
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
