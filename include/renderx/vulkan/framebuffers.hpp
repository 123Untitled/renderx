#ifndef ___RENDERX_VULKAN_FRAMEBUFFERS___
#define ___RENDERX_VULKAN_FRAMEBUFFERS___

#include "renderx/defines.hpp"
#include "renderx/types.hpp"
#include "renderx/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* image views */
	class image_views;

	/* render pass */
	class render_pass;


	// -- F R A M E B U F F E R S ---------------------------------------------

	class framebuffers final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::framebuffers;


			// -- private members ---------------------------------------------

			/* frames */
			vk::framebuffer* _frames;

			/* size */
			size_type _size;


			// -- private methods ---------------------------------------------

			/* destroy */
			auto _destroy(void) noexcept -> void;

			/* create */
			auto _create(const vulkan::image_views&,
						 const vulkan::render_pass&,
						 const vk::extent2D&) -> void;


			// -- public static methods ---------------------------------------

			/* info */
			static auto info(const vulkan::render_pass&,
							 const vk::extent2D&) noexcept -> vk::framebuffer_info;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			framebuffers(void) noexcept;

			/* views / render_pass constructor */
			framebuffers(const vulkan::image_views&,
						 const vulkan::render_pass&,
						 const vk::extent2D&);

			/* uncopyable */
			___uncopyable(framebuffers);

			/* move constructor */
			framebuffers(___self&&) noexcept;

			/* destructor */
			~framebuffers(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type&) const noexcept -> const vk::framebuffer&;


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type;


			// -- public modifiers --------------------------------------------

			/* recreate */
			auto recreate(const vulkan::image_views&,
						  const vulkan::render_pass&,
						  const vk::extent2D&) -> void;


		private:

			// -- private classes ---------------------------------------------

			/* guard */
			class _guard final {


				private:

					// -- private members -------------------------------------

					/* self reference */
					___self& _self;

					/* complete */
					bool _complete;


				public:

					// -- public lifecycle ------------------------------------

					/* deleted default constructor */
					_guard(void) = delete;

					/* self constructor */
					_guard(___self&) noexcept;

					/* uncopyable */
					___uncopyable(_guard);

					/* unmovable */
					___unmovable(_guard);

					/* destructor */
					~_guard(void) noexcept;


					// -- public modifiers ------------------------------------

					/* complete */
					auto complete(void) noexcept -> void;

			}; // class _guard

	}; // class framebuffers

} // namespace vulkan

#endif // ___RENDERX_VULKAN_FRAMEBUFFERS___
