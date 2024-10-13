#ifndef ___RENDEX_VULKAN_SWAPCHAIN_MANAGER___
#define ___RENDEX_VULKAN_SWAPCHAIN_MANAGER___

#include "renderx/vulkan/swapchain.hpp"
#include "renderx/vulkan/images.hpp"
#include "renderx/vulkan/image_views.hpp"
#include "renderx/vulkan/framebuffers.hpp"

#include "renderx/glfw/window.hpp"
#include "renderx/glfw/events.hpp"


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- S W A P C H A I N  M A N A G E R ------------------------------------

	class swapchain_manager final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vulkan::swapchain_manager;


			// -- private members ---------------------------------------------

			/* format */
			vk::surface_format _format;

			/* capabilities */
			vk::surface_capabilities _capabilities;

			/* extent */
			vk::extent2D _extent;

			/* present mode */
			vk::present_mode _mode;

	 		/* size */
			vk::u32 _size;

			/* render pass */
			vulkan::render_pass _render_pass;

			/* swapchain */
			vulkan::swapchain _swapchain;

			/* images */
			vulkan::images _images;

			/* image views */
			vulkan::image_views _views;

			/* framebuffers */
			vulkan::framebuffers _frames;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			swapchain_manager(void);

			/* uncopyable */
			___uncopyable(swapchain_manager);

			/* move constructor */
			swapchain_manager(___self&&) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* recreate */
			auto recreate(void) -> void;


			// -- public accessors --------------------------------------------

			/* swapchain */
			auto swapchain(void) const noexcept -> const vulkan::swapchain& {
				return _swapchain;
			}

			/* render pass */
			auto render_pass(void) const noexcept -> const vulkan::render_pass& {
				return _render_pass;
			}

			/* images */
			auto images(void) const noexcept -> const vulkan::images& {
				return _images;
			}

			/* views */
			auto views(void) const noexcept -> const vulkan::image_views& {
				return _views;
			}

			/* frames */
			auto frames(void) const noexcept -> const vulkan::framebuffers& {
				return _frames;
			}

			/* size */
			auto size(void) const noexcept -> vk::u32 {
				return _swapchain.size();
			}


		private:

			// -- private static methods --------------------------------------

			/* pick mode */
			static auto _pick_mode(void) noexcept -> vk::present_mode;

			/* pick extent */
			static auto _pick_extent(const vk::surface_capabilities&) noexcept -> vk::extent2D;

			/* pick count */
			static auto _pick_count(const vk::surface_capabilities&) noexcept -> vk::u32;

	}; // class swapchain_manager

} // namespace vulkan

#endif // ___RENDEX_VULKAN_SWAPCHAIN_MANAGER___
