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

#ifndef ENGINE_VULKAN_PIPELINE_LIBRARY_HPP
#define ENGINE_VULKAN_PIPELINE_LIBRARY_HPP


// vulkan headers
#include <vulkan/vulkan.h>

#include "renderx/vk/typedefs.hpp"

//#include <unordered_map>
//#include <string_view>


// -- V U L K A N  N A M E S P A C E ------------------------------------------

namespace vulkan {


	// -- P I P E L I N E  L I B R A R Y ---------------------------------------

	//class pipeline_library final {


	//	public:

	//		// -- public types ------------------------------------------------

	//		/* self type */
	//		using self = vulkan::pipeline_library;


	//		// -- public lifecycle --------------------------------------------

	//		/* default constructor */
	//		pipeline_library(void);


	//	private:

	//		// -- private types -----------------------------------------------

	//		/* map type */
	//		using map_type = std::unordered_map<std::string_view, vk::pipeline>;


	//		// -- private members ---------------------------------------------

	//		/* map */
	//		map_type _map;

	//}; // class pipeline_library

} // namespace vulkan

#endif // ENGINE_VULKAN_PIPELINE_LIBRARY_HPP
