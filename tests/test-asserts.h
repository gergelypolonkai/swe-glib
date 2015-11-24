#ifndef __SWE_GLIB_TEST_ASSERTS_H__
#define __SWE_GLIB_TEST_ASSERTS_H__

#include <glib.h>

/* Check equality with fuzzyness. Thanks for ebassi@GNOME and graphene */
#define gswe_assert_fuzzy_equals(n1,n2,epsilon) \
  G_STMT_START { \
    typeof ((n1)) __n1 = (n1); \
    typeof ((n2)) __n2 = (n2); \
    typeof ((epsilon)) __epsilon = (epsilon); \
    if (__n1 > __n2) { \
      if ((__n1 - __n2) <= __epsilon) ; else { \
        g_assertion_message_cmpnum (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                    #n1 " == " #n2 " (+/- " #epsilon ")", \
                                    __n1, "==", __n2, 'f'); \
      } \
    } else { \
      if ((__n2 - __n1) <= __epsilon) ; else { \
        g_assertion_message_cmpnum (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                    #n1 " == " #n2 " (+/- " #epsilon ")", \
                                    __n1, "==", __n2, 'f'); \
      } \
    } \
  } G_STMT_END

/* g_assert_null() and g_assert_nonnull() were defined in 2.36 and
 * 2.40. Requiring a newer GLib just because of this would be an
 * overkill, so let's just backport them:
 */
#ifndef g_assert_null
#define g_assert_null(expr)     do { if G_LIKELY ((expr) == NULL) ; else \
                                    g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                            "'" #expr "' should be NULL"); \
                                } while (0)
#endif

#ifndef g_assert_nonnull
#define g_assert_nonnull(expr)  do { if G_LIKELY ((expr) != NULL) ; else \
                                    g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                            "'" #expr "' should not be NULL"); \
                                } while (0)
#endif

/* g_assert_true() and g_assert_false() were defined in 2.38. Requiring
 * a newer GLib just because of this would be an overkill, so let's just
 * backport them:
 */
#ifndef g_assert_true
#define g_assert_true(expr) G_STMT_START { \
                                if G_LIKELY (expr) ; else \
                                    g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                        "'" #expr "' should be TRUE"); \
                            } G_STMT_END
#endif

#ifndef g_assert_false
#define g_assert_false(expr) G_STMT_START { \
                                 if G_LIKELY (!(expr)) ; else \
                                     g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                                         "'" #expr "' should be FALSE"); \
                                 } G_STMT_END

#endif

#endif /* __SWE_GLIB_TEST_ASSERTS_H__ */
