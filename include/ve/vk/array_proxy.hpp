#ifndef ___void_engine_vk_array_proxy___
#define ___void_engine_vk_array_proxy___


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	// -- array types ---------------------------------------------------------

	/* dynamic array */
	struct dynamic_array;

	/* static array */
	struct static_array;


	// -- A R R A Y  P R O X Y ------------------------------------------------

	template <typename T>
	class array_proxy final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = vk::array_proxy<T>;

	}; // class array_proxy

} // namespace vk

#endif // ___void_engine_vk_array_proxy___
