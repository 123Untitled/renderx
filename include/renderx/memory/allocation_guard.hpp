#ifndef ___RENDEX_MEMORY_ALLOCATION_GUARD___
#define ___RENDEX_MEMORY_ALLOCATION_GUARD___

#include "renderx/memory/malloc.hpp"
#include "renderx/defines.hpp"


// -- R X  N A M E S P A C E --------------------------------------------------

namespace rx {


	// -- A L L O C A T I O N  G U A R D --------------------------------------

	class allocation_guard final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = rx::allocation_guard;


			// -- private members ---------------------------------------------

			/* data */
			void* _data;

			/* complete */
			bool _complete;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			allocation_guard(void) = delete;

			/* data constructor */
			allocation_guard(void* const ___data) noexcept
			: _data{___data}, _complete{false} {
			}

			/* uncopyable */
			___uncopyable(allocation_guard);

			/* unmovable */
			___unmovable(allocation_guard);

			/* destructor */
			~allocation_guard(void) noexcept {

				// check complete
				if (_complete == true)
					return;

				// release memory
				rx::free(_data);
			}


			// -- public modifiers --------------------------------------------

			/* complete */
			auto complete(void) noexcept -> void {
				_complete = true;
			}

	}; // class allocation_guard

} // namespace rx

#endif // ___RENDEX_MEMORY_ALLOCATION_GUARD___
