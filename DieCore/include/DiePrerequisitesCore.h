#pragma once
#include <DiePrerequisites.h>

#if defined(DIE_CORE_STATIC_LIB)
#define DIE_CORE_EXPORT
#else
#if defined(DIE_CORE_EXPORTS)
#define DIE_CORE_EXPORT __declspec(dllexport)
#else
#define DIE_CORE_EXPORT __declspec(dllimport)
#endif
#endif
