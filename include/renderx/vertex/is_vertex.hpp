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

#include "renderx/vk/typedefs.hpp"
#include <concepts>

#include "renderx/vertex/vertex.hpp"


// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- M E T A  N A M E S P A C E ------------------------------------------

	namespace meta {


		// -- I S  V E R T E X ------------------------------------------------

		/* vertex concept */
		template <typename ___type>
		concept is_vertex = requires {
			{ ___type::pipeline_vertex_input_state_info() } -> std::same_as<const vk::pipeline_vertex_input_state_info&>;
		};

	} // namespace meta

} // namespace engine


// -- V X  N A M E S P A C E --------------------------------------------------

namespace vx {


	// -- I S  V E R T E X ----------------------------------------------------

	namespace ___impl {


		/* false specialization */
		template <typename ___type>
		struct ___is_vertex final {
			//___xns_not_instantiable(___is_vertex);
			static constexpr bool value = false;
		};

		/* true specialization */
		template <typename... ___types>
		struct ___is_vertex<engine::vertex<___types...>> final {
			//___xns_not_instantiable(___is_vertex);
			static constexpr bool value = true;
		};

	}; // namespace ___impl


	/* is vertex */
	template <typename ___type>
	concept is_vertex = vx::___impl::___is_vertex<___type>::value;


} // namespace vx

#endif // ENGINE_META_VERTEX_HPP
