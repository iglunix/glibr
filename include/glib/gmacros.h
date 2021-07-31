#ifndef _G_MACROS_H_
#define _G_MACROS_H_

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAX(a, b) (((a) > (b))?(a):(b))
#define MIN(a, b) (((a) < (b))?(a):(b))

#ifdef __cplusplus
#define G_BEGIN_DECLS extern "C" {
#define G_END_DECLS }
#else
#define G_BEGIN_DECLS
#define G_END_DECLS
#endif

#define G_GNUC_CONST
#define G_DEPRECATED
#define G_DEPRECATED_FOR(f)
#define G_GNUC_PURE

#define G_GNUC_PRINTF(f,a)

/*
 * This is meant to hint the compiler
 * for optimisation. We do not do such things.
 */
#define G_UNLIKELY(e)

#endif
