#ifndef STR_UTILS__STR_TO_INT_H
#define STR_UTILS__STR_TO_INT_H

/*
    Check for 'signed long long' & 'unsigned long long' types existance, since
    them was instroduced since C99 (and not available in C89, C90, C94(???) )

    Check for C standard version given from here:
        https://stackoverflow.com/a/2115886/
*/
#ifndef STR_UTILS__LONG_LONG_PRESENT
    #if (__STDC_VERSION__ >= 199901L)
        #define STR_UTILS__LONG_LONG_PRESENT
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -------------------------------------------------------------------------- */

signed char      str_to_signed_char         (const char* str, char** end_ptr, int base);

signed short     str_to_signed_short        (const char* str, char** end_ptr, int base);

signed int       str_to_signed_int          (const char* str, char** end_ptr, int base);

signed long      str_to_signed_long         (const char* str, char** end_ptr, int base);

#ifdef STR_UTILS__LONG_LONG_PRESENT
signed long long str_to_signed_long_long    (const char* str, char** end_ptr, int base);
#endif


unsigned char      str_to_unsigned_char     (const char* str, char** end_ptr, int base);

unsigned short     str_to_unsigned_short    (const char* str, char** end_ptr, int base);

unsigned int       str_to_unsigned_int      (const char* str, char** end_ptr, int base);

unsigned long      str_to_unsigned_long     (const char* str, char** end_ptr, int base);

#ifdef STR_UTILS__LONG_LONG_PRESENT
unsigned long long str_to_unsigned_long_long(const char* str, char** end_ptr, int base);
#endif

/* -------------------------------------------------------------------------- */

/*bool*/ int is_parsed_signed_char       (const char* str, const char* end_ptr, int base, signed char* out_result);

/*bool*/ int is_parsed_signed_short      (const char* str, const char* end_ptr, int base, signed short* out_result);

/*bool*/ int is_parsed_signed_int        (const char* str, const char* end_ptr, int base, signed int* out_result);

/*bool*/ int is_parsed_signed_long       (const char* str, const char* end_ptr, int base, signed long* out_result);

#ifdef STR_UTILS__LONG_LONG_PRESENT
/*bool*/ int is_parsed_signed_long_long  (const char* str, const char* end_ptr, int base, signed long long* out_result);
#endif


/*bool*/ int is_parsed_unsigned_char     (const char* str, const char* end_ptr, int base, unsigned char* out_result);

/*bool*/ int is_parsed_unsigned_short    (const char* str, const char* end_ptr, int base, unsigned short* out_result);

/*bool*/ int is_parsed_unsigned_int      (const char* str, const char* end_ptr, int base, unsigned int* out_result);

/*bool*/ int is_parsed_unsigned_long     (const char* str, const char* end_ptr, int base, unsigned long* out_result);

#ifdef STR_UTILS__LONG_LONG_PRESENT
/*bool*/ int is_parsed_unsigned_long_long(const char* str, const char* end_ptr, int base, unsigned long long* out_result);
#endif

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STR_UTILS__STR_TO_INT_H */
