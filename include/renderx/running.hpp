#ifndef ___RENDERX_RUNNING_HPP___
#define ___RENDERX_RUNNING_HPP___

//#include "concurrency/atomic.hpp"
#include <atomic>


// -- W E B  S E R V E R  N A M E S P A C E -----------------------------------

namespace ws {


	// -- R U N N I N G -------------------------------------------------------

	class running final {


		private:


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ws::running;


			// -- private members ---------------------------------------------

			/* is running flag */
			std::atomic<bool> _flag;
			//ws::atomic<bool> _flag;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) noexcept -> ___self& {
				static ___self ___ins;
				return ___ins;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			running(void) noexcept
			: _flag{false} {
			}

			/* deleted copy constructor */
			running(const ___self&) = delete;

			/* deleted move constructor */
			running(___self&&) = delete;

			/* destructor */
			~running(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* state */
			static auto state(void) noexcept -> bool {
				return ___self::_shared()._flag.load();
			}

			/* start */
			static auto start(void) noexcept -> void {
				___self::_shared()._flag.store(true);
			}

			/* stop */
			static inline auto stop(void) noexcept -> void {
				___self::_shared()._flag.store(false);
			}

	}; // class running

} // namespace ws

#endif // ___RUNNING_HPP___

