#include <str_utils/str_starts_ends_with.h>

#include <string.h> /* for: memcmp() */

/* via: https://stackoverflow.com/a/4771038/ */
/*bool*/ int str_starts_with(
    const char* str, size_t str_size,
    const char* prefix, size_t prefix_size
)
{
    return
        (str_size < prefix_size) ?
            /*false*/ 0
        : /* str_size >= preffix_size */
            ( memcmp(str, prefix, prefix_size) == 0 ) ?
                /*true*/ 1
            :
                /*false*/ 0;
}

/*bool*/ int str_ends_with(
    const char* str, size_t str_size,
    const char* suffix, size_t suffix_size
)
{
    return
        (str_size < suffix_size) ?
            /*false*/ 0
        : /* str_size >= suffix_size */
            ( memcmp(str + (str_size - suffix_size), suffix, suffix_size) == 0 ) ?
                /*true*/ 1
            :
                /*false*/ 0;
}
