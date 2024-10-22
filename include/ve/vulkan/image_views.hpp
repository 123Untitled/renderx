#ifndef ___RENDERX_VULKAN_IMAGE_VIEWS___
#define ___RENDERX_VULKAN_IMAGE_VIEWS___

#include "ve/defines.hpp"
#include "ve/types.hpp"
#include "ve/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* images */
	class images;


	// -- I M A G E  V I E W S ------------------------------------------------

	class image_views final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = rx::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::image_views;


			// -- private members ---------------------------------------------

			/* image views */
			vk::image_view* _views;

			/* size */
			size_type _size;


			// -- private methods ---------------------------------------------

			/* destroy */
			auto _destroy(void) noexcept -> void;

			/* create */
			auto _create(const vulkan::images&, const vk::format&) -> void;


			// -- public static methods ---------------------------------------

			/* info */
			static auto info(const vk::format&) noexcept -> vk::image_view_info;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			image_views(void) noexcept;

			/* images constructor */
			image_views(const vulkan::images&, const vk::format);

			/* uncopyable */
			___uncopyable(image_views);

			/* move constructor */
			image_views(___self&&) noexcept;

			/* destructor */
			~image_views(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type&) const noexcept -> const vk::image_view&;


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type;


			// -- public modifiers --------------------------------------------

			/* recreate */
			auto recreate(const vulkan::images&, const vk::format) -> void;


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

	}; // class image_views

} // namespace vulkan

#endif // ___RENDERX_VULKAN_IMAGE_VIEWS___
