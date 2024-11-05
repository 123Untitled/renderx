#ifndef ___ve_vulkan_exception___
#define ___ve_vulkan_exception___

#include "ve/diagnostics/exception.hpp"
#include "ve/vk/typedefs.hpp"


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception final : public rx::exception {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using self = vk::exception;


			// -- private members ---------------------------------------------

			/* where */
			const char* _where;

			/* what */
			const char* _what;


			// -- private static methods --------------------------------------

			/* strerror */
			static auto _strerror(const ::vk_result&) noexcept -> const char*;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) = delete;

			/* where and what constructor */
			exception(const char* where, const ::vk_result& what) noexcept
			: _where{where != nullptr ? where : "unknown"}, _what{self::_strerror(what)} {
			}

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* what */
			auto what(void) const noexcept -> const char* override;

	}; // class exception

} // namespace vk

#endif // ___ve_vulkan_exception___
