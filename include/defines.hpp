#ifndef ___DEFINES___
#define ___DEFINES___


/* uncopyable */
#define ___uncopyable(___class) \
	/* deleted copy constructor */ \
	___class(const ___class&) = delete; \
	/* deleted copy assignment operator */ \
	auto operator=(const ___class&) -> ___class& = delete;

/* unmovable */
#define ___unmovable(___class) \
	/* deleted move constructor */ \
	___class(___class&&) = delete; \
	/* move assignment operator */ \
	auto operator=(___class&&) -> ___class& = delete;


#endif // ___DEFINES___
