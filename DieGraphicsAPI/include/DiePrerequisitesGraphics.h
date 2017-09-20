#pragma once
#include <DiePrerequisites.h>


#if defined(DIE_GRAPHICS_STATIC_LIB)
#define DIE_GRAPHICS_EXPORT
#else
#if defined(DIE_GRAPHICS_EXPORTS)
#define DIE_GRAPHICS_EXPORT __declspec(dllexport)
#else
#define DIE_GRAPHICS_EXPORT __declspec(dllimport)
#endif
#endif