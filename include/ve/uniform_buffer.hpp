#ifndef ___void_engine_uniform_buffer___
#define ___void_engine_uniform_buffer___

#include "ve/vulkan/buffer.hpp"


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- U N I F O R M  B U F F E R ------------------------------------------

	class uniform_buffer final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::uniform_buffer;


			// -- private members ---------------------------------------------

			/* buffer */
			vulkan::buffer _buffer;


	}; // class uniform_buffer

} // namespace ve

#endif // ___void_engine_uniform_buffer___
