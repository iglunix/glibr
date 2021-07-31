#include <assert.h>

#define g_assert(expr) assert(expr)
/*
 * TODO: Do something
 * for now we do nothing;
 * the testing framework is not critical
 */
#define g_assert_no_error(expr)

/*
 * TODO: Do something
 */
#define g_assert_not_reached()

void gtest_init (int *argc, char const ***argv, ...);

#define G_STATIC_ASSERT(s) _Static_assert(s, #s)
