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

				_alloc.map();
				_alloc.memcpy(&data, 0U);
				// copy data
				//_alloc.memcpy(&data);
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

			/* descriptor buffer info */
			//auto descriptor_buffer_info(void) const noexcept -> vk::descriptor_buffer_info {
			//	return vk::descriptor_buffer_info{
			//		.buffer = _uniform_buffer.get(),
			//		.offset = 0U,
			//		.range = sizeof(uniform)
			//	};
			//}


			// -- public methods ----------------------------------------------

			/* update */
			template <typename T>
			auto update(const T& data) -> void {

				// copy data
				_alloc.memcpy(&data, 0U);
			}


	}; // class uniform_buffer



	template <typename T>
	class uniform_buffer_long final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::uniform_buffer_long<T>;


			// -- private members ---------------------------------------------

			/* alignment */
			vk::device_size _alignment;

			/* count */
			vk::u32 _count;

			/* buffer */
			vulkan::buffer _buffer;

			/* allocation */
			vulkan::allocation _alloc;



			// -- private static methods --------------------------------------

			/* compute alignment */
			static auto _compute_alignment(void) -> vk::device_size {

				// get min ubo alignment
				const auto ubo_alignment = ve::physical_device::shared().min_uniform_buffer_offset_alignment();

				// aligned size
				auto alignment = sizeof(T);

				if (ubo_alignment > 0U) {
					alignment = (sizeof(T) + ubo_alignment - 1) & ~(ubo_alignment - 1);
				}

				return alignment;
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			uniform_buffer_long(void) noexcept
			: _alignment{___self::_compute_alignment()},
			  _count{0U},
			  _buffer{},
			  _alloc{} {
			}

			/* count constructor */
			uniform_buffer_long(const vk::u32& count)
			: _alignment{___self::_compute_alignment()},
			  _count{count},
			  _buffer{_alignment * count, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT},
			  _alloc{vulkan::allocator<vulkan::cpu_coherent>::allocate_buffer(_buffer.underlying())} {

			}

			/* deleted copy constructor */
			uniform_buffer_long(const ___self&) = delete;

			/* move constructor */
			uniform_buffer_long(___self&&) noexcept = default;

			/* destructor */
			~uniform_buffer_long(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* update */
			auto update(const vk::u32 index, const T& data) -> void {

				if (index >= _count)
					throw std::out_of_range{"uniform_buffer_long: index out of range"};

				// offset
				const auto offset = _alignment * index;

				// copy data
				_alloc.memcpy(&data, offset);
			}

			/* update all */
			auto update_all(std::vector<T> data) -> void {

				if (data.size() != _count)
					throw std::out_of_range{"uniform_buffer_long: data size mismatch"};

				// copy data
				_alloc.memcpy(data.data());
			}

			/* map */
			auto map(void) -> void {
				_alloc.map();
			}

			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> const vk::buffer& {
				return _buffer.underlying();
			}

			/* descriptor buffer info */
			auto descriptor_buffer_info(void) const noexcept -> vk::descriptor_buffer_info {

				// dynamic offset
				return vk::descriptor_buffer_info{
					.buffer = _buffer.underlying(),
					.offset = 0U,
					.range = _alignment
				};
			}

			/* count */
			auto count(void) const noexcept -> const vk::u32& {
				return _count;
			}

			/* alignment */
			auto alignment(void) const noexcept -> vk::u32 {
				return _alignment;
			}

			/* alignment */
			auto alignment(const vk::u32& index) const noexcept -> vk::u32 {

				return (vk::u32)_alignment * index;
			}


	}; // class uniform_buffer

} // namespace ve

#endif // ___void_engine_uniform_buffer___
