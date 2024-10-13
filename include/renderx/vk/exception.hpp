/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#ifndef ___RENDERX_VULKAN_EXCEPTION___
#define ___RENDERX_VULKAN_EXCEPTION___

#include "renderx/diagnostics/exception.hpp"
#include "renderx/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception final : public rx::exception {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using ___self = vk::exception;


			// -- private members ---------------------------------------------

			/* where */
			const char* _where;

			/* what */
			const char* _what;


			// -- private static methods --------------------------------------

			/* strerror */
			static auto _strerror(const vk::result&) noexcept -> const char*;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) = delete;

			/* where and what constructor */
			exception(const char* where, const vk::result what) noexcept
			: _where{where != nullptr ? where : "unknown"}, _what{___self::_strerror(what)} {
			}

			/* copy constructor */
			exception(const ___self&) noexcept = default;

			/* move constructor */
			exception(___self&&) noexcept = default;

			/* destructor */
			~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> const char* override;

	}; // class exception

} // namespace vulkan

#endif // ___RENDERX_VULKAN_EXCEPTION___
