#ifndef MARTCHUSUTILITY_LIBRARY_GLOBAL_H
#define MARTCHUSUTILITY_LIBRARY_GLOBAL_H

#ifdef _WIN32
# ifndef PLATFORM_WINDOWS
/*!
 * \brief Defined on Windows.
 */
#  define PLATFORM_WINDOWS
# endif
#elif __unix__
# ifndef PLATFORM_UNIX
/*!
 * \brief Defined on any UNIX system.
 */
#  define PLATFORM_UNIX
# endif
#endif
#ifdef __linux__
# ifndef PLATFORM_LINUX
/*!
 * \brief Defined on Linux.
 */
#  define PLATFORM_LINUX
# endif
#endif

/*!
 * \def LIB_EXPORT
 * \brief Marks a symbol for shared library export.
 */

/*!
 * \def LIB_IMPORT
 * \brief Declares a symbol to be an import from a shared library.
 */

/*!
 * \def LIB_HIDDEN
 * \brief Hidden visibility indicates that the symbol will not be placed into
 *        the dynamic symbol table, so no other module (executable or shared library)
 *        can reference it directly.
 */

#ifdef PLATFORM_WINDOWS
# define LIB_EXPORT __declspec(dllexport)
# define LIB_IMPORT __declspec(dllimport)
# define LIB_HIDDEN
#else
# define LIB_EXPORT __attribute__((visibility("default")))
# define LIB_IMPORT __attribute__((visibility("default")))
# define LIB_HIDDEN __attribute__((visibility("hidden")))
#endif

/*!
 * \def USE_NOTHROW
 * \brief Marks a function as never throwing, under no circumstances.
 * \remarks If the function does nevertheless throw, the behaviour is undefined.
 */

#ifndef USE_NOTHROW
# if __cplusplus >= 201103L
#  define USE_NOTHROW noexcept
# else
#  define USE_NOTHROW throw()
# endif
#endif

/*!
 * \def DECLARE_ENUM
 * \brief Forward-declares enums without preventing lupdate to parse the file correctly.
 */

#define DECLARE_ENUM(name, base) enum class name : base;

#define VAR_UNUSED(x) (void)x;

/*!
 * \def IF_DEBUG_BUILD
 * \brief Wraps debug-only lines conveniently.
 */

#ifdef DEBUG_BUILD
# define IF_DEBUG_BUILD(x) x
#else
# define IF_DEBUG_BUILD(x)
#endif

#endif // MARTCHUSUTILITY_LIBRARY_GLOBAL_H
