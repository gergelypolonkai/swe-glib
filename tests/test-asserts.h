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

#endif /* __SWE_GLIB_TEST_ASSERTS_H__ */
