#pragma once

#ifdef _WIN32
#ifdef OTOOLS_EXPORT
#define OTOOLS_API
#else
#define OTOOLS_API
#endif
#else
#define OTOOLS_API
#endif

#include <random>
#include "OrbitalTools/vendor/Backtrace.h"

#define OE_UNCONST(Return_type, This, method) const_cast<Return_type>(const_cast<const This*>(this)->method())
