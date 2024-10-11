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

#ifndef ENGINE_VK_DESTROY_HPP
#define ENGINE_VK_DESTROY_HPP

#include "engine/vk/typedefs.hpp"
#include "engine/vk/functions.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- D E S T R O Y -------------------------------------------------------



	// -- framebuffer ---------------------------------------------------------

	/* destroy framebuffer */
	inline auto destroy(const vk::device& ___device,
						const vk::framebuffer& ___framebuffer) noexcept -> void {
		::vkDestroyFramebuffer(___device, ___framebuffer, nullptr);
	}

	inline auto destroy(const vk::framebuffer& ___framebuffer,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyFramebuffer(___device, ___framebuffer, nullptr);
	}


	// -- image view ----------------------------------------------------------

	/* destroy image view */
	inline auto destroy(const vk::device& ___device,
						const vk::image_view& ___image_view) noexcept -> void {
		::vkDestroyImageView(___device, ___image_view, nullptr);
	}

	inline auto destroy(const vk::image_view& ___image_view,
						const vk::device& ___device) noexcept -> void {
		::vkDestroyImageView(___device, ___image_view, nullptr);
	}




	// -- I S  D E S T R O Y A B L E ------------------------------------------

	/* is destroyable */
	template <typename... ___params>
	concept is_destroyable = requires(___params&&... ___args) {
		{ vk::destroy(std::forward<___params>(___args)...) } -> std::same_as<void>;
	};


} // namespace vk

#endif // ENGINE_VK_DESTROY_HPP
