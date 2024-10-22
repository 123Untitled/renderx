#ifndef ___RENDERX_META_IS_EMPTY___
#define ___RENDERX_META_IS_EMPTY___

#ifndef ___rx_has_builtin
#	ifndef __has_builtin
#		define ___rx_has_builtin(x) 0
#	else
#		define ___rx_has_builtin(x) __has_builtin(x)
#	endif
#endif

#if not ___rx_has_builtin(__is_empty)
#	error "compiler does not support __is_empty"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E M P T Y ------------------------------------------------------

	/* is empty */
	template <typename ___type>
	concept is_empty = __is_empty(___type);

} // namespace xns

#endif // XNS_IS_EMPTY_HEADER

