#include <str_utils/str_to_int.h>

#include <stdlib.h> /* for: strtol(), strtoul() */
#include <limits.h> /* for: SCHAR_MIN, SCHAR_MAX, SHRT_MIN, SHRT_MAX, INT_MIN, INT_MAX, LONG_MIN, LONG_MAX, */
#include <errno.h>  /* for: errno, ERANGE */

/*
    Based on: https://stackoverflow.com/a/29378380/
*/

static long
str_to_signed_subrange(
    const char* str, char** end_ptr, int base,
    long min, long max
)
{
    long result;

    errno = 0; /* Clear previous error-number */

    result = strtol(str, end_ptr, base);

    if(result > max)
    {
        errno = ERANGE;
        return max;
    }
    else if(result < min)
    {
        errno = ERANGE;
        return min;
    }

    return result;
}

static unsigned long
str_to_unsigned_subrange(
    const char* str, char** end_ptr, int base,
    unsigned long max
)
{
    unsigned long result;

    errno = 0; /* Clear previous error-number */

    result = strtoul(str, end_ptr, base);

    if(result > max)
    {
        errno = ERANGE;
        return max;
    }

    return result;
}

/* -------------------------------------------------------------------------- */

signed char str_to_signed_char(const char* str, char** end_ptr, int base)
{
    return (signed char) str_to_signed_subrange(str, end_ptr, base, SCHAR_MIN, SCHAR_MAX);
}

signed short str_to_signed_short(const char* str, char** end_ptr, int base)
{
    return (signed short) str_to_signed_subrange(str, end_ptr, base, SHRT_MIN, SHRT_MAX);
}

signed int str_to_signed_int(const char* str, char** end_ptr, int base)
{
    #if (INT_MIN == LONG_MIN) && (INT_MAX == LONG_MAX)
        return (signed int) strtol(str, end_ptr, base);
    #else
        return (signed int) str_to_signed_subrange(str, end_ptr, base, INT_MIN, INT_MAX);
    #endif
}

signed long str_to_signed_long(const char* str, char** end_ptr, int base)
{
    return strtol(str, end_ptr, base);
}

#ifdef STR_UTILS__LONG_LONG_PRESENT
signed long long str_to_signed_long_long(const char* str, char** end_ptr, int base)
{
    return strtoll(str, end_ptr, base);
}
#endif

/* -------------------------------------------------------------------------- */

unsigned char str_to_unsigned_char(const char* str, char** end_ptr, int base)
{
    return (unsigned char) str_to_unsigned_subrange(str, end_ptr, base, UCHAR_MAX);
}

unsigned short str_to_unsigned_short(const char* str, char** end_ptr, int base)
{
    return (unsigned short) str_to_unsigned_subrange(str, end_ptr, base, USHRT_MAX);
}

unsigned int str_to_unsigned_int(const char* str, char** end_ptr, int base)
{
    #if (UINT_MAX == ULONG_MAX)
        return (unsigned int) strtoul(str, end_ptr, base);
    #else
        return (unsigned int) str_to_unsigned_subrange(str, end_ptr, base, UINT_MAX);
    #endif
}

unsigned long str_to_unsigned_long(const char* str, char** end_ptr, int base)
{
    return strtoul(str, end_ptr, base);
}

#ifdef STR_UTILS__LONG_LONG_PRESENT
unsigned long long str_to_unsigned_long_long(const char* str, char** end_ptr, int base)
{
    return strtoull(str, end_ptr, base);
}
#endif


/* -------------------------------------------------------------------------- */

/*
    NOTE: 'is_parsed_<type>(...)` functions are based on:
        https://stackoverflow.com/a/11279798/
 */


/*bool*/ int is_parsed_signed_char(const char* str, const char* end_ptr, int base, signed char* out_result)
{
    signed char result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_signed_char(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_signed_short(const char* str, const char* end_ptr, int base, signed short* out_result)
{
    signed short result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_signed_short(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_signed_int(const char* str, const char* end_ptr, int base, signed int* out_result)
{
    signed int result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_signed_int(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_signed_long(const char* str, const char* end_ptr, int base, signed long* out_result)
{
    signed long result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_signed_long(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

#ifdef STR_UTILS__LONG_LONG_PRESENT
/*bool*/ int is_parsed_signed_long_long(const char* str, const char* end_ptr, int base, signed long long* out_result)
{
    signed long long result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_signed_long_long(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}
#endif

/* -------------------------------------------------------------------------- */

/*bool*/ int is_parsed_unsigned_char(const char* str, const char* end_ptr, int base, unsigned char* out_result)
{
    unsigned char result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_unsigned_char(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_unsigned_short(const char* str, const char* end_ptr, int base, unsigned short* out_result)
{
    unsigned short result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_unsigned_short(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_unsigned_int(const char* str, const char* end_ptr, int base, unsigned int* out_result)
{
    unsigned int result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_unsigned_int(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

/*bool*/ int is_parsed_unsigned_long(const char* str, const char* end_ptr, int base, unsigned long* out_result)
{
    unsigned long result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_unsigned_long(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}

#ifdef STR_UTILS__LONG_LONG_PRESENT
/*bool*/ int is_parsed_unsigned_long_long(const char* str, const char* end_ptr, int base, unsigned long long* out_result)
{
    unsigned long long result;
    char* result_ptr = (char*)end_ptr;

    errno = 0; /* Clear previous error-number */

    result = str_to_unsigned_long_long(str, &result_ptr, base);
    if(errno == ERANGE)
    {
        /* Parsed integer is out of range */
        errno = 0;
        return /*false*/ 0;
    }
    if(result_ptr == str)
    {
        /* Nothing parsed from the string */
        return /*false*/ 0;
    }

    if(out_result != NULL)
    {
        *out_result = result;
    }
    return /*true*/ 1;
}
#endif
