#ifndef ___RENDERX_VULKAN_IMAGES___
#define ___RENDERX_VULKAN_IMAGES___

#include "renderx/defines.hpp"
#include "renderx/types.hpp"
#include "renderx/vk/typedefs.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- forward declarations ------------------------------------------------

	/* swapchain */
	class swapchain;


	// -- I M A G E S ---------------------------------------------------------

	class images final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = vk::u32;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::images;


			// -- private members ---------------------------------------------

			/* images */
			vk::image* _images;

			/* size */
			size_type _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			images(void) noexcept;

			/* swapchain constructor */
			images(const vulkan::swapchain&);

			/* uncopyable */
			___uncopyable(images);

			/* move constructor */
			images(___self&&) noexcept;

			/* destructor */
			~images(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type&) const noexcept -> const vk::image&;


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type;


			// -- public modifiers --------------------------------------------

			/* recreate */
			auto recreate(const vulkan::swapchain&) -> void;


		private:

			// -- private static methods --------------------------------------

			/* swapchain images count */
			static auto _count(const vulkan::swapchain&) -> size_type;

	}; // class images

} // namespace vulkan

#endif // ___RENDERX_VULKAN_IMAGES___
