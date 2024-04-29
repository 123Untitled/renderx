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

#include "engine/vk/typedefs.hpp"
#include <xns/is_same.hpp>


// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- M E T A  N A M E S P A C E ------------------------------------------

	namespace meta {


		// -- I S  V E R T E X ------------------------------------------------

		/* vertex concept */
		template <typename ___type>
		concept is_vertex = requires {
			{ ___type::pipeline_vertex_input_state_info() } -> xns::same_as<const vk::pipeline_vertex_input_state_info&>;
		};

	} // namespace meta

} // namespace engine

#endif // ENGINE_META_VERTEX_HPP
