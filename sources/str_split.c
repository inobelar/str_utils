#include <str_utils/str_split.h>

#include <stdlib.h> /* for: malloc() */

size_t str_split_count_chunks(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped
)
{
    size_t chunks_count = 0;

    /*bool*/ int any_separator_found = /*false*/ 0;
    size_t last_separator_pos = 0;

    size_t i = 0;

    if( (str == NULL) || (size == 0) || (str[0] == '\0') )
    {
        return 0;
    }

    for(i = 0; i < size; ++i)
    {
        /*bool*/ int separator_found = (str[i] == separator) ? /*true*/ 1 : /*false*/ 0;

        if(separator_found == /*true*/ 1)
        {
            if(skip_escaped == /*true*/ 1)
            {
                if( (i > 0) && (str[i-1] == '\\') )
                {
                    separator_found = /*false*/ 0;
                }
            }
        }

        /* ------------------------------------------------------------------ */

        if(separator_found == /*true*/ 1)
        {
            if(i == 0)
            {
                if(keep_empty == /*true*/ 1)
                {
                    chunks_count += 1;
                }
                else /* keep_empty == 0 (false) */
                {
                    /* noop */
                }
            }
            else /* i > 0 */
            {
                if(any_separator_found == /*true*/ 1)
                {
                    const size_t distance_to_prev_separator = (i - last_separator_pos);
                    if(distance_to_prev_separator < 2) /* distance is 1 (or 0 for some unhandled reason) */
                    {
                        if(keep_empty == /*true*/ 1)
                        {
                            chunks_count += 1;
                        }
                        else /* keep_empty == 0 (false) */
                        {
                            /* noop */
                        }
                    }
                    else /* distance >= 2 */
                    {
                        chunks_count += 1;
                    }
                }
                else /* any_separator_found == 0 (false) */
                {
                    chunks_count += 1;
                }
            }

            any_separator_found = /*true*/ 1;
            last_separator_pos = i;
        }
    }

    /* Count trailing chunk (after last separator) */
    if(any_separator_found == /*true */ 1) /* Any separator found, event if `last_separator_pos == 0` */
    {
        if(last_separator_pos < (size-1) )
        {
            chunks_count += 1;
        }
    }

    return chunks_count;
}

/* -------------------------------------------------------------------------- */

size_t str_split(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped,

    str_chunk_t** chunks_out
)
{
    /*bool*/ int any_separator_found = /*false*/ 0;
    size_t last_separator_pos = 0;

    size_t i = 0;
    size_t chunk_idx = 0;

    const size_t chunks_count = str_split_count_chunks(str, size, separator, keep_empty, skip_escaped);

    str_chunk_t* chunks = malloc(sizeof(str_chunk_t) * chunks_count);
    if(chunks != NULL) /* malloc() returns NULL if 'chunks_count' is 0 */
    {
        for(i = 0; i < size; ++i)
        {
            /*bool*/ int separator_found = (str[i] == separator) ? /*true*/ 1 : /*false*/ 0;

            if(separator_found == /*true*/ 1)
            {
                if(skip_escaped == /*true*/ 1)
                {
                    if( (i > 0) && (str[i-1] == '\\') )
                    {
                        separator_found = /*false*/ 0;
                    }
                }
            }

            /* -------------------------------------------------------------- */

            if(separator_found == /*true*/ 1)
            {
                if(i == 0)
                {
                    if(keep_empty == /*true*/ 1)
                    {
                        chunks[chunk_idx].str  = &(str[0]);
                        chunks[chunk_idx].size = 0;

                        chunk_idx += 1;
                    }
                    else /* keep_empty == 0 (false) */
                    {
                        /* noop */
                    }
                }
                else /* i > 0 */
                {
                    if(any_separator_found == /*true*/ 1)
                    {
                        const size_t distance_to_prev_separator = (i - last_separator_pos);
                        if(distance_to_prev_separator < 2) /* distance is 1 (or 0 for some unhandled reason) */
                        {
                            if(keep_empty == /*true*/ 1)
                            {
                                chunks[chunk_idx].str  = &(str[last_separator_pos+1]);
                                chunks[chunk_idx].size = 0;

                                chunk_idx += 1;
                            }
                            else /* keep_empty == 0 (false) */
                            {
                                /* noop */
                            }
                        }
                        else /* distance >= 2 */
                        {
                            chunks[chunk_idx].str  = &(str[last_separator_pos+1]);
                            chunks[chunk_idx].size = distance_to_prev_separator-1;

                            chunk_idx += 1;
                        }
                    }
                    else /* any_separator_found == 0 (false) */
                    {
                        chunks[chunk_idx].str  = &(str[0]);
                        chunks[chunk_idx].size = i;

                        chunk_idx += 1;
                    }
                }

                any_separator_found = /*true*/ 1;
                last_separator_pos = i;
            }
        }

        /* Add trailing chunk (after last separator) */
        if(any_separator_found == /*true*/ 1) /* Any separator found, event if `last_separator_pos == 0` */
        {
            if(last_separator_pos < (size-1) )
            {
                chunks[chunks_count-1].str  = &(str[last_separator_pos+1]);
                chunks[chunks_count-1].size = (size - (last_separator_pos+1));
            }
        }
    }

    *chunks_out = chunks;
    return chunks_count;
}

/* -------------------------------------------------------------------------- */

size_t str_split_fixed(
    const char* str, size_t size,
    char separator,
    /*bool*/ int keep_empty,
    /*bool*/ int skip_escaped,

    str_chunk_t* chunks,
    size_t       chunks_max_size
)
{
    /*bool*/ int any_separator_found = /*false*/ 0;
    size_t last_separator_pos = 0;

    size_t i = 0;
    size_t chunk_idx = 0;

    const size_t chunks_count = str_split_count_chunks(str, size, separator, keep_empty, skip_escaped);

    if( (chunks != NULL) && (chunks_max_size != 0) )
    {
        for(i = 0; i < size; ++i)
        {
            /*bool*/ int separator_found = (str[i] == separator) ? /*true*/ 1 : /*false*/ 0;

            if(separator_found == /*true*/ 1)
            {
                if(skip_escaped == /*true*/ 1)
                {
                    if( (i > 0) && (str[i-1] == '\\') )
                    {
                        separator_found = /*false*/ 0;
                    }
                }
            }

            /* -------------------------------------------------------------- */

            if(separator_found == /*true*/ 1)
            {
                if(i == 0)
                {
                    if(keep_empty == /*true*/ 1)
                    {
                        if(chunk_idx >= chunks_max_size) { return chunks_count; } /* guard */

                        chunks[chunk_idx].str  = &(str[0]);
                        chunks[chunk_idx].size = 0;

                        chunk_idx += 1;
                    }
                    else /* keep_empty == 0 (false) */
                    {
                        /* noop */
                    }
                }
                else /* i > 0 */
                {
                    if(any_separator_found == /*true*/ 1)
                    {
                        const size_t distance_to_prev_separator = (i - last_separator_pos);
                        if(distance_to_prev_separator < 2) /* distance is 1 (or 0 for some unhandled reason) */
                        {
                            if(keep_empty == /*true*/ 1)
                            {
                                if(chunk_idx >= chunks_max_size) { return chunks_count; } /* guard */

                                chunks[chunk_idx].str  = &(str[last_separator_pos+1]);
                                chunks[chunk_idx].size = 0;

                                chunk_idx += 1;
                            }
                            else /* keep_empty == 0 (false) */
                            {
                                /* noop */
                            }
                        }
                        else /* distance >= 2 */
                        {
                            if(chunk_idx >= chunks_max_size) { return chunks_count; } /* guard */

                            chunks[chunk_idx].str  = &(str[last_separator_pos+1]);
                            chunks[chunk_idx].size = distance_to_prev_separator-1;

                            chunk_idx += 1;
                        }
                    }
                    else /* any_separator_found == 0 (false) */
                    {
                        if(chunk_idx >= chunks_max_size) { return chunks_count; } /* guard */

                        chunks[chunk_idx].str  = &(str[0]);
                        chunks[chunk_idx].size = i;

                        chunk_idx += 1;
                    }
                }

                any_separator_found = /*true*/ 1;
                last_separator_pos = i;
            }
        }

        /* Add trailing chunk (after last separator) */
        if(any_separator_found == /*true*/ 1) /* Any separator found, event if `last_separator_pos == 0` */
        {
            if(last_separator_pos < (size-1) )
            {
                if((chunks_count-1) >= chunks_max_size) { return chunks_count; } /* guard */

                chunks[chunks_count-1].str  = &(str[last_separator_pos+1]);
                chunks[chunks_count-1].size = (size - (last_separator_pos+1));
            }
        }
    }

    return chunks_count;
}
