#ifndef STR_UTILS__STR_SPLIT_H
#define STR_UTILS__STR_SPLIT_H

#include <stddef.h> /* for: size_t */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -------------------------------------------------------------------------- */

/**
    @param[in] str          String buffer pointer
    @param[in] size         String buffer length
    @param[in] separator    Separator character
    @param[in] keep_empty   [bool] If set to 1 (true) - empty chunks will be
                            counted, if 0 (false) - they will be skipped
    @param[in] skip_escaped [bool] If set to 1 (true) - escaped separators
                            (followed by '\' symbol) will not be detected

    @return count of chunks, or 0 if:
    - empty string was passed
    - string not contains any separators
    - @a skip_escaped was set to 1 (true), and all separators are 'escaped'
*/
size_t str_split_count_chunks(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped
);

/* -------------------------------------------------------------------------- */

typedef struct str_chunk_t_
{
    const char* str;  /** Pointer to the first character in chunk */
    size_t      size; /** Chunk size (0 if empty) */
} str_chunk_t;

/**
    @param[in]  str          String buffer pointer
    @param[in]  size         String buffer length
    @param[in]  separator    Separator character
    @param[in]  keep_empty   [bool] If set to 1 (true) - empty chunks will be
                             counted, if 0 (false) - they will be skipped
    @param[in]  skip_escaped [bool] If set to 1 (true) - escaped separators
                             (followed by '\' symbol) will not be detected

    @param[out] chunks_out   Array of string chunks, separated by @a separator

    @return count of chunks, or 0 if:
    - empty string was passed
    - string not contains any separators
    - @a skip_escaped was set to 1 (true), and all separators are 'escaped'

    @attention Internally, @a chunks_out array is allocated by `malloc()`, so
    dont forget to call `free()` after use.
*/
size_t str_split(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped,

    str_chunk_t** chunks_out
);

size_t str_split_fixed(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped,

    str_chunk_t* chunks_out,
    size_t       chunks_out_size
);

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STR_UTILS__STR_SPLIT_H */
