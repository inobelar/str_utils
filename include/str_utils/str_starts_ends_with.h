#ifndef STR_UTILS__STR_STARTS_ENDS_WITH_H
#define STR_UTILS__STR_STARTS_ENDS_WITH_H

#include <stddef.h> /* for: size_t */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -------------------------------------------------------------------------- */

/*bool*/ int str_starts_with(
    const char* str, size_t str_size,
    const char* prefix, size_t prefix_size
);

/*bool*/ int str_ends_with(
    const char* str, size_t str_size,
    const char* suffix, size_t suffix_size
);

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STR_UTILS__STR_STARTS_ENDS_WITH_H */
