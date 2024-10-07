#ifndef ___ENGINE_VULKAN_SYNC___
#define ___ENGINE_VULKAN_SYNC___

#include "engine/vk/typedefs.hpp"
#include "engine/vk/info.hpp"
#include "engine/vulkan/device.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S Y N C -------------------------------------------------------------

	template <const vk::u32 MAX_FRAMES_IN_FLIGHT>
	class sync final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::sync<MAX_FRAMES_IN_FLIGHT>;


			// -- private members ---------------------------------------------

			/* current frame */
			vk::u32 _current_frame;

			/* image available semaphores */
			vk::semaphore _image_available[MAX_FRAMES_IN_FLIGHT];

			/* render finished semaphores */
			vk::semaphore _render_finished[MAX_FRAMES_IN_FLIGHT];

			/* fences */
			vk::fence _fences[MAX_FRAMES_IN_FLIGHT];


			// -- private classes ---------------------------------------------

			/* exception guard */
			class _exception_guard final {


				private:

					// -- private members -------------------------------------

					/* self reference */
					___self& _self;

					/* completed */
					bool _completed;


				public:

					// -- public lifecycle ------------------------------------

					/* deleted default constructor */
					_exception_guard(void) = delete;

					/* self constructor */
					_exception_guard(___self& self) noexcept
					: _self{self}, _completed{false} {
					}

					/* deleted copy constructor */
					_exception_guard(const _exception_guard&) = delete;

					/* deleted move constructor */
					_exception_guard(_exception_guard&&) = delete;


					/* destructor */
					~_exception_guard(void) noexcept {

						// free resources if not completed
						if (not _completed)
							_self._free();
					}


					// -- public assignment operators -------------------------

					/* deleted copy assignment operator */
					auto operator=(const _exception_guard&) -> _exception_guard& = delete;

					/* deleted move assignment operator */
					auto operator=(_exception_guard&&) -> _exception_guard& = delete;


					// -- public modifiers ------------------------------------

					/* complete */
					auto complete(void) noexcept -> void {
						_completed = true;
					}

			}; // class _exception_guard


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			sync(void)
			:  _current_frame{0U},
			  _image_available{},
			  _render_finished{},
			  _fences{} {


				// get device
				const auto& device = vulkan::device::logical();

				// semaphore info
				constexpr auto sem_info = vk::info::semaphore();

				// fence info
				constexpr auto fence_info = vk::info::fence<VK_FENCE_CREATE_SIGNALED_BIT>();

				// exception guard
				_exception_guard guard{*this};

				// create semaphores and fences
				for (vk::u32 i = 0U; i < MAX_FRAMES_IN_FLIGHT; ++i) {

					// create image available semaphore
					vk::try_execute<"failed to create semaphore">(
							::vk_create_semaphore,
							device, &sem_info, nullptr, _image_available + i);

					// create render finished semaphore
					vk::try_execute<"failed to create semaphore">(
							::vk_create_semaphore,
							device, &sem_info, nullptr, _render_finished + i);

					// create fence
					vk::try_execute<"failed to create fence">(
							::vk_create_fence,
							device, &fence_info, nullptr, _fences + i);
				}

				// complete guard
				guard.complete();
			}

			/* deleted copy constructor */
			sync(const ___self&) = delete;

			/* deleted move constructor */
			sync(___self&&) = delete;

			/* destructor */
			~sync(void) noexcept {

				// free resources
				___self::_free();
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- public methods ----------------------------------------------

			/* reset current fence */
			auto reset_current_fence(void) noexcept -> void {

				// reset current fence
				vk::try_execute<"failed to reset fence">(
						::vk_reset_fences,
						vulkan::device::logical(),
						1U,
						&(_fences[_current_frame])
				);
			}

			/* wait current fence */
			auto wait_current_fence(void) noexcept -> void {

				// wait current fence
				vk::try_execute<"failed to wait for fence">(
						::vk_wait_for_fences,
						vulkan::device::logical(),
						1U,
						&(_fences[_current_frame]),
						VK_TRUE,
						UINT64_MAX
				);
			}

			// -- public accessors --------------------------------------------

			/* current frame */
			auto current_frame(void) const noexcept -> const vk::u32& {
				return _current_frame;
			}

			/* image available semaphore */
			auto image_available(void) const noexcept -> const vk::semaphore& {
				return _image_available[_current_frame];
			}

			/* render finished semaphore */
			auto render_finished(void) const noexcept -> const vk::semaphore& {
				return _render_finished[_current_frame];
			}

			/* fence */
			auto fence(void) const noexcept -> const vk::fence& {
				return _fences[_current_frame];
			}


			// -- public operators --------------------------------------------

			/* next frame */
			auto operator++(void) noexcept -> void {

				// increment current frame
				_current_frame = (_current_frame + 1U) % MAX_FRAMES_IN_FLIGHT;
			}


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto _free(void) noexcept -> void {

				// get device
				const auto& device = vulkan::device::logical();

				// loop over frames in flight
				for (vk::u32 i = 0U; i < MAX_FRAMES_IN_FLIGHT; ++i) {

					// destroy image available semaphore
					if (_image_available[i])
						::vk_destroy_semaphore(device, _image_available[i], nullptr);

					// destroy render finished semaphore
					if (_render_finished[i])
						::vk_destroy_semaphore(device, _render_finished[i], nullptr);

					// destroy fence
					if (_fences[i])
						::vk_destroy_fence(device, _fences[i], nullptr);
				}
			}

	}; // class sync

} // namespace vulkan

#endif // ___ENGINE_VULKAN_SYNC___
