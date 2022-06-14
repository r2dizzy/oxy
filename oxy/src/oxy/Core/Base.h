#pragma once

#if defined( __APPLE__ )
#error "This library is not supported on MacOS."
#endif

// For now we are only building a static library so we will define this.
#define OXY_STATIC

// DLL export/import, windows then Linux

#if defined ( _WIN32 )
# if defined ( OXY_BUILD_DLL ) // OXY_BUILD_DLL if we are building the DLL, else we import
#  define OXY_API __declspec(dllexport)
# elif !defined ( OXY_STATIC )
#  define OXY_API __declspec(dllimport)
# else
#  define OXY_API
# endif
#endif

// Linux
#if defined ( __linux__ )
# if defined ( OXY_BUILD_DLL )
#  define OXY_API __attribute__((visibility("default")))
# elif !defined ( OXY_STATIC )
#  define OXY_API
# else
#  define OXY_API
# endif
#endif

#if defined ( _WIN32 )
#include <Windows.h>
#else
#endif