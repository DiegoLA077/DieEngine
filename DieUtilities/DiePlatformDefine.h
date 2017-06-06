#pragma once

//Initial platform/compiler-related stuff to se

#define DIE_PLATFORM_WIN32 1				//Windows platform
#define DIE_PLATFORM_LINUX 2				//Linux
#define DIE_PLATFORM_APPLE 3				//Apple
#define DIE_PLATFORM_PS4   4				//PlayStation 4 

#define DIE_COMPILER_MSVC 1				//Visual Studio Compiler
#define DIE_COMPILER_GNUC 2				//GCC Compiler
#define DIE_COMPILER_INTEL 3				//Intel
#define DIE_COMPILER_CLANG 4				//Clang 

#define DIE_ARCHITECTURE_x86_32 1			//Intel x86 32bits
#define DIE_ARCHITECTURE_x86_64 2			//Intel x86 64bits

#define DIE_ENDIAN_LITTLE 1				//Little Endian
#define DIE_ENDIAN_BIG    2				//Big Endian

#define DIE_ENDIAN DIE_ENDIAN_LITTLE		//Define the actual type

#define DIE_EDITOR_BUILD 1


//Compiler type and version

#if defined (_MSC_VER)
#define DIE_COMPILER DIE_COMPILER_MSVC
#define COMP_VER_ _MSC_VER
#define DIE_THREADLOCAL __declspec(thread)
#elif defined(__GNUC__)
#define DIE_COMPILER DIE_COMPILER_GNUC
#define COMP_VER_(((__GNUC__)*100)+(__GNUC_MINOR__*10)+ __GNUC_PATCHLEVEL__)
#define THREADLOCAL __thread
#elif defined (__INTEL_COMPILER)
#define DIE_COMPILER DIE_COMPILER_INTEL
#define COMP_VER_ __INTEL_COMPILER

#elif defined ( __clang__ )
#define DIE_COMPILER DIE_COMPILER_CLANG
#define COMP_VER_ __clang_major__
#define THREADLOCAL __thread
#else 
#pragma error "No know compiler. "
#endif


//See if we can use __forceinline or if we need to use __inline instead

#if DIE_COMPILER == DIE_COMPILER_MSVC 
#if COMP_VER_ >= 1200
#define FORCEINLINE __forceinline
#ifndef RESTRICT
#define RESTRICT __restrict
#endif
#endif
#elif defined(__MINGW32__)
#if !defined(FORCEINLINE)
#define FORCEINLINE __inline
#ifndef RESTRICT
#define RESTRICT
#endif
#endif
#else
#define FORCEINLINE __inline
#ifndef RESTRICT
#define RESTRICT __restrict
#endif 
#endif


//Finds the current platform
#if defined(__WIN32__) || defined(_WIN32)
#define DIE_PLATFORM DIE_PLATFORM_WIN32
#elif defined(__APPLE_CC__)
#define DIE_PLATFORM DIE_PLATFORM_APPLE
#elif defined(__ORBIS__)
#define DIE_PLATFORM DIE_PLATFORM_PS4
#else
#define DIE_PLATFORM DIE_PLATFORM_LINUX
#endif

//Find the architecture type 

#if defined(__x86_64__) || defined(_M_x64)
#define ARCH_TYPE ARCHITECTURE_x86_64
#else
#define ARCH_TYPE DIE_ARCHITECTURE_x86_32
#endif

//Memory Aligment macros

#if DIE_COMPILER == DIE_COMPILER_MSVC
#define MS_ALIGN(n) __declspec(align(n))
#ifndef GCC_PACK
#define GCC_PACK(n)
#endif
#ifndef GCC_ALINGN 
#define GCC_ALIGN(n)
#endif
#elif (DIE_COMPILER == DIE_COMPILER_GNUC && DIE_PLATFORM == DIE_PLATFORM_PS4)
#define MS_ALIGN(n)
#define GCC_PACK(n)
#define GCC_ALIGN(n) __atribute__((__aligned__(n)))
#else
#define MS_ALIGN(n)
#define GCC_PACK(n)	 __atribute__((__packed, aligned__(n)))
#define GCC_ALIGN(n) __atribute__((__aligned__(n)))
#endif

//For throw override

#if DIE_COMPILER == DIE_COMPILER_MSVC
#define _NOEXCEPT noexcept
#elif DIE_COMPILER == DIE_COMPILER_INTEL
#define _NOEXCEPT noexcept
#elif DIE_COMPILER == DIE_COMPILER_GNUC
#define _NOEXCEPT noexcept
#else 
#define _NOEXCEPT
#endif

//Windows specific settings

#if DIE_PLATFORM == DIE_PLATFORM_WIN32
#if defined (STATIC_LIB)
#define D_UTILITIES_EXPORT
#else
#if defined(UTILITIES_EXPORTS)
#define D_UTILITIES_EXPORT __declspec(dllexport)
#else
#if defined (__MINGW32__)
#define D_UTILITIES_EXPORT
#else
#define  D_UTILITIES_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define DEBUG_MODE 1
#else
#define DEBUG_MODE 0 
#endif
#if D_COMPILER == D_COMPILER_INTEL
#define THREADLOCAL __declspec(thread)
#endif
#endif

#if D_PLATFORM == D_PLATFORM_LINUX || PLATFORM == D_PLATFORM_APPLE
#if defined (GCC_VISIBILITY)
#define UTILITY_EXPORT __attribute__ ((visibility("default")))
#else
#define UTILITY_EXPORT
#endif

#define stricmp strcasecmp

#if defined(_DEBUG) || defined (DEBUG)
#define DEBUG_MODE 1
#else 
#define DEBUG_MODE 0
#endif

#if D_COMPILER == D_COMPILER_INTEL
#define THREADLOCAL __thread
#endif
#endif

#if D_PLATFORM == D_PLATFORM_PS4
#if defined (STATIC_LIB)
#define UTILITY_EXPORT
#else
#if defined(UTILITY_EXPORTS)
#define UTILITY_EXPORT __declspec(dllexport)
#else
#if defined (__MINGW32__)
#define UTILITY_EXPORT
#else
#define  UTILITY_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define DEBUG_MODE 1
#else
#define DEBUG_MODE 0 
#endif
#endif

#if DEBUG_MODE
#define DEBUG_ONLY(x)x
#define D_ASSERT(x) assert x
#else
#define DEBUG_ONLY(x)
#define D_ASSERT(x)
#endif