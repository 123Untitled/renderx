#ifndef ___ve_vulkan_sync___
#define ___ve_vulkan_sync___

#include "ve/vk/unique.hpp"
#include "ve/vk/utils.hpp"
#include "ve/vk/typedefs.hpp"
#include "ve/vk/info.hpp"
#include "ve/vulkan/device.hpp"

#include "ve/vulkan/fence.hpp"
#include "ve/vulkan/semaphore.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S Y N C -------------------------------------------------------------

	class sync final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::sync;


			// -- private members ---------------------------------------------

			/* current frame */
			vk::u32 _current_frame;

			/* image available semaphores */
			std::vector<ve::semaphore> _image_available;

			/* render finished semaphores */
			std::vector<ve::semaphore> _render_finished;

			/* fences */
			std::vector<ve::fence> _fences;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			sync(void) noexcept = default;

			/* size constructor */
			sync(const vk::u32& frame_in_flight)
			:  _current_frame{0U},
			  _image_available{},
			  _render_finished{},
			  _fences{} {

				// create semaphores and fences
				_image_available.resize(frame_in_flight);
				_render_finished.resize(frame_in_flight);
						 _fences.resize(frame_in_flight);
			}

			/* deleted copy constructor */
			sync(const ___self&) = delete;

			/* move constructor */
			sync(___self&&) noexcept = default;

			/* destructor */
			~sync(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public methods ----------------------------------------------

			/* reset current fence */
			auto reset_current_fence(void) noexcept -> void {

				// reset current fence
				_fences[_current_frame].reset();
			}

			/* wait current fence */
			auto wait_current_fence(void) noexcept -> void {

				// wait current fence
				_fences[_current_frame].wait();
			}

			// -- public accessors --------------------------------------------

			/* current frame */
			auto current_frame(void) const noexcept -> const vk::u32& {
				return _current_frame;
			}

			/* current image available */
			auto current_image_available(void) const noexcept -> const vk::semaphore& {
				return _image_available[_current_frame].get();
			}

			/* current render finished */
			auto current_render_finished(void) const noexcept -> const vk::semaphore& {
				return _render_finished[_current_frame].get();
			}

			/* current fence */
			auto current_fence(void) const noexcept -> const vk::fence& {
				return _fences[_current_frame].get();
			}


			// -- public operators --------------------------------------------

			/* next frame */
			auto operator++(void) noexcept -> void {

				// increment current frame
				_current_frame = (_current_frame + 1U) % _image_available.size();
			}

	}; // class sync

} // namespace ve

#endif // ___ENGINE_VULKAN_SYNC___
