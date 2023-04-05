
#include <filesystem>

#include "Logging.h"

// ! make a better system for this, just use premake in the future
#define PN_ENABLE_ASSERTS
#define PN_DEBUG

#ifdef PN_DEBUG
	#define PN_DEBUGBREAK() __debugbreak()
#endif

#define PN_EXPAND_MACRO(x) x
#define PN_STRINGIFY_MACRO(x) #x

#ifdef PN_ENABLE_ASSERTS
	#define PN_CORE_ASSERT(condition, msg) if(!condition){PN_CORE_FATAL(msg); PN_DEBUGBREAK();}
#else
	#define PN_ASSERT(...)
	#define PN_CORE_ASSERT(...)
#endif