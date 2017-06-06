#pragma once

#if defined(DIE_UTILITIES_STATIC_LIB)
#define DIE_UTILITIES_EXPORT
#else
#if defined(DIE_UTILITIES_EXPORTS)
#define DIE_UTILITIES_EXPORT __declspec(dllexport)
#else
#define DIE_UTILITIES_EXPORT __declspec(dllimport)
#endif
#endif