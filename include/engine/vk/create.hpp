/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VK_CREATE_HPP
#define ENGINE_VK_CREATE_HPP

#include "engine/vk/typedefs.hpp"
#include "engine/vk/utils.hpp"
#include "engine/vk/functions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {




	// -- create framebuffer --------------------------------------------------

	/* create framebuffer */
	inline auto create(const vk::device& ___device,
					   const vk::framebuffer_info& ___info) -> vk::framebuffer {
		vk::framebuffer ___framebuffer{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateFramebuffer,
					"failed to create framebuffer",
					___device, &___info, nullptr, &___framebuffer);
		return ___framebuffer;
	}

	/* create framebuffer */
	inline auto create(const vk::framebuffer_info& ___info,
					   const vk::device& ___device) -> vk::framebuffer {
		return vk::create(___device, ___info);
	}


	// -- image view ----------------------------------------------------------

	/* create image view */
	inline auto create(const vk::device& ___device,
					   const vk::image_view_info& info) -> vk::image_view {
		vk::image_view view{VK_NULL_HANDLE};
		vk::try_execute(::vkCreateImageView,
					"failed to create image view",
					___device, &info, nullptr, &view);
		return view;
	}

	/* create image view */
	inline auto create(const vk::image_view_info& ___info,
					   const vk::device& ___device) -> vk::image_view {
		return vk::create(___device, ___info);
	}


	// -- descriptor pool -----------------------------------------------------

	/* create descriptor pool */
	inline auto create(const vk::device& ___device,
					   const vk::descriptor_pool_info& ___info) -> vk::descriptor_pool {

		vk::descriptor_pool ___pool;

		vk::try_execute<"failed to create descriptor pool">(
				::vkCreateDescriptorPool,
				___device, &___info, nullptr, &___pool);

		return ___pool;
	}


	// -- descriptor set layout -----------------------------------------------

	/* create descriptor set layout */
	inline auto create(const vk::device& ___device,
					   const vk::descriptor_set_layout_info& ___info) -> vk::descriptor_set_layout {

		vk::descriptor_set_layout ___layout;

		vk::try_execute<"failed to create descriptor set layout">(
				::vkCreateDescriptorSetLayout,
				___device, &___info, nullptr, &___layout);

		return ___layout;
	}


	// -- is createable -------------------------------------------------------

	/* is creatable */
	template <typename ___type, typename... ___params>
	concept is_creatable = requires(___params&&... ___args) {
		{ vk::create(std::forward<___params>(___args)...) } -> std::same_as<___type>;
	};

	/* create return */
	template <typename... ___params>
	using create_return = decltype(vk::create(std::declval<___params>()...));


} // namespace vk

#endif // ENGINE_VK_CREATE_HPP
