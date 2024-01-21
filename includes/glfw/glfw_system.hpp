#ifndef ENGINE_GLFW_SYSTEM_HPP
#define ENGINE_GLFW_SYSTEM_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>

#include "os.hpp"
#include "exceptions.hpp"
#include <xns>

// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {

	// -- S Y S T E M ---------------------------------------------------------

	class system final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = glfw::system;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			system(const self&) = delete;

			/* deleted move constructor */
			system(self&&) noexcept = delete;

			/* destructor */
			~system(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public static methods ---------------------------------------

			/* is initialized */
			static auto is_initialized(void) noexcept -> bool;

			/* vulkan required extensions */
			static auto vulkan_required_extensions(void) -> xns::vector<const char*>;


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			system(void);


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) noexcept -> self&;

			/* error callback */
			static auto error_callback(int, const char*) noexcept -> void;


			// -- private members ---------------------------------------------

			/* initialized */
			bool _initialized;

	};

}

#endif // ENGINE_GLFW_SYSTEM_HPP
