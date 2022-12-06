#pragma once

#ifdef _WIN32
#ifdef OTOOLS_EXPORT
#define OTOOLS_API __declspec(dllexport)
#else
#define OTOOLS_API __declspec(dllimport)
#endif
#else
#define OTOOLS_API
#endif

#include <random>
#include <chrono>

#define OE_UNCONST(Return_type, This, method) const_cast<Return_type>(const_cast<const This*>(this)->method())
