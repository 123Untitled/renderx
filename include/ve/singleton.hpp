#ifndef ___ve_singleton___
#define ___ve_singleton___

#include <concepts>


// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- S I N G L E T O N ---------------------------------------------------

	template <typename T>
	class singleton final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = ve::singleton<T>;


			// -- private members ---------------------------------------------

			/* value */
			T _value;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) /* noexcept() */ -> self& {
				static self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			singleton(void) = default;

			/* deleted copy constructor */
			singleton(const self&) = delete;

			/* deleted move constructor */
			singleton(self&&) = delete;

			/* destructor */
			~singleton(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* shared */
			template <typename... Ts>
			static auto shared(void) /* noexcept() */ -> T& {
				return self::_shared()._value;
			}


	}; // class singleton

} // namespace ve

#endif // ___ve_singleton___
