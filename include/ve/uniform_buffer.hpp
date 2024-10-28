#ifndef ___void_engine_uniform_buffer___
#define ___void_engine_uniform_buffer___

#include "ve/vulkan/buffer.hpp"
#include "ve/vulkan/allocator.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- U N I F O R M  B U F F E R ------------------------------------------

	class uniform_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::uniform_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;

			/* allocation */
			vulkan::allocation _alloc;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			uniform_buffer(void) noexcept = default;

			template <typename T>
			uniform_buffer(const T& data)
			: _buffer{sizeof(T), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT},
			  _alloc{vulkan::allocator<vulkan::cpu_coherent>::allocate_buffer(_buffer.underlying())} {

				// copy data
				_alloc.memcpy(&data);
			}

			/* deleted copy constructor */
			uniform_buffer(const ___self&) = delete;

			/* move constructor */
			uniform_buffer(___self&&) noexcept = default;

			/* destructor */
			~uniform_buffer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::buffer& {
				return _buffer.underlying();
			}

			/* descriptor buffer info */
			auto descriptor_buffer_info(void) const noexcept -> vk::descriptor_buffer_info {
				return vk::descriptor_buffer_info{
					.buffer = _buffer.underlying(),
					.offset = 0U,
					.range = VK_WHOLE_SIZE
				};
			}


			// -- public methods ----------------------------------------------

			/* update */
			template <typename T>
			auto update(const T& data) -> void {

				// copy data
				_alloc.memcpy(&data);
			}


	}; // class uniform_buffer

} // namespace ve

#endif // ___void_engine_uniform_buffer___
