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

#ifndef ENGINE_META_VERTEX_HPP
#define ENGINE_META_VERTEX_HPP

#include <vulkan/vulkan.h>
#include <concepts>

// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {

	// -- M E T A  N A M E S P A C E ------------------------------------------

	namespace meta {

		// -- I S  V E R T E X ------------------------------------------------

		/* vertex concept */
		template <typename T>
		concept is_vertex = requires {
			{ T::pipeline_vertex_input_state_info() } -> std::same_as<::VkPipelineVertexInputStateCreateInfo>;
		};

	} // namespace meta

} // namespace engine

#endif // ENGINE_META_VERTEX_HPP
