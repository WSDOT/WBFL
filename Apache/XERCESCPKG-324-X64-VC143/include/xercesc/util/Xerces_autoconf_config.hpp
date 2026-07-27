/* file      : xercesc/util/Xerces_autoconf_config.hpp -*- C -*-
 * license   : Apache License 2.0; see accompanying LICENSE file
 */

#ifndef XERCESC_UTIL_XERCES_AUTOCONF_CONFIG_HPP
#define XERCESC_UTIL_XERCES_AUTOCONF_CONFIG_HPP

/* For the semantics of the following macros refer to
 * Xerces_autoconf_config.hpp.cmake.in.orig and upstream's configure.ac.
 *
 * We won't drop macro (un)definitions just because they are not used by the
 * library itself (as we do for config.h), because this header is installed
 * and the library clients may potentially rely on them.
 */

/* int16_t, etc.
 */
#if defined(__cplusplus)
#  include <cstdint>
#else
#  include <stdint.h> /* Requires C99. */
#endif

#include <inttypes.h>

#include <sys/types.h>

/* Specific for FreeBSD.
 */
#ifdef __FreeBSD__
#  define HAVE_CPUID_H         1
#  define XERCES_HAVE_GETCPUID 1
#endif

/* Specific for POSIX (none).
 */
#ifndef _WIN32
/* Specific for Windows.
 */
#else
#  define XERCES_HAVE_INTRIN_H        1
#  define XERCES_HAVE_CPUID_INTRINSIC 1
#endif

/* Specific for (non-) VC.
 */
#ifndef _MSC_VER
#  define XERCES_SSIZE_T ssize_t
#else
#  define XERCES_SSIZE_T long
#endif

/* Common for all supported OSes/compilers.
 */
#define XERCES_HAVE_CSTDINT      1
#define XERCES_HAVE_STDINT_H     1
#define XERCES_HAVE_SYS_TYPES_H  1
#define XERCES_HAVE_INTTYPES_H   1
#define XERCES_HAS_CPP_NAMESPACE 1
#define XERCES_STD_NAMESPACE     1
#define XERCES_NEW_IOSTREAMS     1
#define XERCES_LSTRSUPPORT       1

#undef XERCES_AUTOCONF
#undef XERCES_HAVE_EMMINTRIN_H
#undef XERCES_INCLUDE_WCHAR_H
#undef XERCES_NO_NATIVE_BOOL
#undef XERCES_HAVE_SSE2_INTRINSIC
#undef XERCES_NO_MATCHING_DELETE_OPERATOR

#define XERCES_S16BIT_INT int16_t
#define XERCES_S32BIT_INT int32_t
#define XERCES_S64BIT_INT int64_t
#define XERCES_U16BIT_INT uint16_t
#define XERCES_U32BIT_INT uint32_t
#define XERCES_U64BIT_INT uint64_t
#define XERCES_XMLCH_T    char16_t
#define XERCES_SIZE_T     size_t

/* Export/import.
 */

/* It's not really clear how exactly the upstream's explicit template
 * instantiation exportation works for VC and Clang targeting MSVC:
 * __declspec(dllexport) is specified for explicit template instantiation
 * declarations that has no 'extern' keyword specified. This, in particular,
 * results with the 'duplicate explicit instantiation ignored' warning for
 * Clang targeting MSVC.
 *
 * We, instead, align the explicit template instantiation exportation with the
 * approach used for the build2 projects, so that the extern keyword is always
 * used for the template instantiation declarations and  __declspec(dllexport)
 * is specified for the declarations for MinGW GCC and for the definitions for
 * VC and Clang targeting MSVC.
 *
 * Note that the XERCES_TEMPLATE_EXTERN macro is now unused by the library.
 */
#undef XERCES_TEMPLATE_EXTERN

#if defined(LIBXERCES_C_STATIC)         /* Using static. */
#  define XERCES_PLATFORM_IMPORT
#  define XERCES_PLATFORM_DECEXPORT
#elif defined(LIBXERCES_C_STATIC_BUILD) /* Building static. */
#  define XERCES_PLATFORM_EXPORT
#  define XERCES_PLATFORM_DECEXPORT
#  define XERCES_PLATFORM_DEFEXPORT
#elif defined(LIBXERCES_C_SHARED)       /* Using shared. */
#  ifdef _WIN32
#    define XERCES_DLL_EXPORT         1
#    define XERCES_PLATFORM_IMPORT    __declspec(dllimport)
#    define XERCES_PLATFORM_DECEXPORT __declspec(dllimport)
#  else
#    define XERCES_PLATFORM_IMPORT
#    define XERCES_PLATFORM_DECEXPORT
#  endif
#elif defined(LIBXERCES_C_SHARED_BUILD) /* Building shared. */
#  ifdef _WIN32
#    define XERCES_DLL_EXPORT      1
#    define XERCES_PLATFORM_EXPORT __declspec(dllexport)
#    if defined(_MSC_VER)
#      define XERCES_PLATFORM_DECEXPORT
#      define XERCES_PLATFORM_DEFEXPORT __declspec(dllexport)
#    else
#      define XERCES_PLATFORM_DECEXPORT __declspec(dllexport)
#      define XERCES_PLATFORM_DEFEXPORT
#    endif
#  else
#    define XERCES_PLATFORM_EXPORT
#    define XERCES_PLATFORM_DECEXPORT
#    define XERCES_PLATFORM_DEFEXPORT
#  endif
#else
/* If none of the above macros are defined, then we assume we are being used
 * by some third-party build system that cannot/doesn't signal the library
 * type. Note that falling back to defining the XERCES_PLATFORM_IMPORT macro
 * as empty would work for both the static and shared libraries (being
 * sub-optimal for the later) but only for functions. Xerces-C++, however,
 * also exports data symbols, which cannot be imported this way. Thus,
 * where matters (Windows), we just issue an error.
 */
#  ifdef _WIN32
#    error define LIBXERCES_C_STATIC or LIBXERCES_C_SHARED preprocessor macro to signal Xerces-C++ library type being linked
#  else
#    define XERCES_PLATFORM_IMPORT
#    define XERCES_PLATFORM_DECEXPORT
#  endif
#endif

#ifdef XERCES_DLL_EXPORT
#  define DLL_EXPORT
#endif

/* Is only defined on Windows by the upstream package but seems to be
 * redundant.
 */
#undef XERCES_STATIC_LIBRARY

/* XMLSize_t is the unsigned integral type.
 */
typedef XERCES_SIZE_T		 XMLSize_t;
typedef XERCES_SSIZE_T   XMLSSize_t;

#define XERCES_SIZE_MAX  SIZE_MAX
#define XERCES_SSIZE_MAX SSIZE_MAX

/* Define our version of the XML character
 */
typedef XERCES_XMLCH_T XMLCh;

/* Define unsigned 16, 32, and 64 bit integers
 */
typedef XERCES_U16BIT_INT XMLUInt16;
typedef XERCES_U32BIT_INT XMLUInt32;
typedef XERCES_U64BIT_INT XMLUInt64;

/* Define signed 16, 32, and 64 bit integers
 */
typedef XERCES_S16BIT_INT XMLInt16;
typedef XERCES_S32BIT_INT XMLInt32;
typedef XERCES_S64BIT_INT XMLInt64;

/* XMLFilePos is the type used to represent a file position.
 */
typedef XMLUInt64 XMLFilePos;

/* XMLFileLoc is the type used to represent a file location (line/column).
 */
typedef XMLUInt64 XMLFileLoc;

/* Force on the Xerces debug token if it is on in the build environment
 */
#if defined(_DEBUG)
#define XERCES_DEBUG
#endif

#endif /* XERCESC_UTIL_XERCES_AUTOCONF_CONFIG_HPP */
