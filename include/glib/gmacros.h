#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifdef __cplusplus
#define G_BEGIN_DECLS extern "C" {
#define G_END_DECLS }
#else
#define G_BEGIN_DECLS
#define G_END_DECLS
#endif
