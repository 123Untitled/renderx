/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___ENGINE_GLFW_SYSTEM_HPP___
#define ___ENGINE_GLFW_SYSTEM_HPP___

#include "renderx/glfw/init.hpp"


// -- G L F W  N A M E S P A C E ----------------------------------------------

namespace glfw {


	// -- forward declarations ------------------------------------------------

	/* window */
	class window;


	// -- S Y S T E M ---------------------------------------------------------

	class system final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = glfw::system;


			// -- private members ---------------------------------------------

			/* init */
			glfw::init _init;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) noexcept -> ___self&;

			/* error callback */
			static auto _error_callback(int, const char*) noexcept -> void;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			system(void);

			/* deleted copy constructor */
			system(const ___self&) = delete;

			/* deleted move constructor */
			system(___self&&) = delete;

			/* destructor */
			~system(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private methods ---------------------------------------------

			/* vulkan required extensions */
			auto _vulkan_required_extensions(void) -> std::vector<const char*>;


		public:

			// -- public static methods ---------------------------------------

			/* init */
			static auto init(void) -> void;

			/* vulkan required extensions */
			static auto vulkan_required_extensions(void) -> std::vector<const char*>;


	}; // class system

} // namespace glfw

#endif // ___ENGINE_GLFW_SYSTEM_HPP___
