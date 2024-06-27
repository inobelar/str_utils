#include <str_utils/str_split.h>

#include <stdlib.h> /* for: free() */
#include <string.h> /* for: strlen() */
#include <stdio.h>  /* for: printf() */

typedef struct test_case_t_
{
    const char* str;
    char sep;

    /*bool*/ int keep_empty;
    /*bool*/ int skip_escaped;

    size_t chunks_count;
    const char ** chunks;

} test_case_t;

static const char* CHUNKS_1_EMPTY[1] = {""};
static const char* CHUNKS_2_EMPTY[2] = {"", ""};
static const char* CHUNKS_5_EMPTY[5] = {"", "", "", "", ""};
static const char* CHUNKS_1_BACKSLASH[1] = {"\\"};
static const char* CHUNKS_1_BACKSLASH_COMMA[1] = {"\\,"};
static const char* CHUNKS_2_EMPTY__BACKSLASH[2] = {"", "\\"};
static const char* CHUNKS_2_EMPTY__BACKSLASH_COMMA[2] = {"", "\\,"};
static const char* CHUNKS_2_BACKSLASH__BACKSLASH[2] = {"\\", "\\"};
static const char* CHUNKS_2_BACKSLASH__SPACE_BACKSLASH[2] = {"\\", " \\"};
static const char* CHUNKS_3_a__b__c[3] = {"a", "b", "c"};
static const char* CHUNKS_3_first__second__third[3] = {"first", "second", "third"};
static const char* CHUNKS_4_EMPTY__a__b__c[4] = {"", "a", "b", "c"};
static const char* CHUNKS_5_EMPTY__a__EMPTY__b__c[5] = {"", "a", "", "b", "c"};

static const test_case_t TEST_CASES[] =
{
      { /*str*/ " ", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ " ", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ " ", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ " ", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }

    , { /*str*/ ",", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 1, /*chunks*/ CHUNKS_1_EMPTY }
    , { /*str*/ ",", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 1, /*chunks*/ CHUNKS_1_EMPTY }

    , { /*str*/ ",,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_EMPTY }
    , { /*str*/ ",,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 2, /*chunks*/ CHUNKS_2_EMPTY }

    , { /*str*/ ",,,,,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",,,,,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ ",,,,,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 5, /*chunks*/ CHUNKS_5_EMPTY }
    , { /*str*/ ",,,,,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 5, /*chunks*/ CHUNKS_5_EMPTY }

    , { /*str*/ "\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 1, /*chunks*/ CHUNKS_1_BACKSLASH }
    , { /*str*/ "\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL  }
    , { /*str*/ "\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 1, /*chunks*/ CHUNKS_1_BACKSLASH }
    , { /*str*/ "\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }

    , { /*str*/ ",\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 1, /*chunks*/ CHUNKS_1_BACKSLASH }
    , { /*str*/ ",\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 1, /*chunks*/ CHUNKS_1_BACKSLASH_COMMA }
    , { /*str*/ ",\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_EMPTY__BACKSLASH }
    , { /*str*/ ",\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 2, /*chunks*/ CHUNKS_2_EMPTY__BACKSLASH_COMMA }

    , { /*str*/ "\\,\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_BACKSLASH__BACKSLASH }
    , { /*str*/ "\\,\\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ "\\,\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_BACKSLASH__BACKSLASH }
    , { /*str*/ "\\,\\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }

    , { /*str*/ "\\, \\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_BACKSLASH__SPACE_BACKSLASH }
    , { /*str*/ "\\, \\,", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }
    , { /*str*/ "\\, \\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 2, /*chunks*/ CHUNKS_2_BACKSLASH__SPACE_BACKSLASH }
    , { /*str*/ "\\, \\,", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 0, /*chunks*/ NULL }

    , { /*str*/ "a,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ "a,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ "a,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ "a,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }

    , { /*str*/ "first,second,third", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_first__second__third }
    , { /*str*/ "first,second,third", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_first__second__third }
    , { /*str*/ "first,second,third", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_first__second__third }
    , { /*str*/ "first,second,third", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_first__second__third }

    , { /*str*/ ",a,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ ",a,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ ",a,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 4, /*chunks*/ CHUNKS_4_EMPTY__a__b__c }
    , { /*str*/ ",a,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 4, /*chunks*/ CHUNKS_4_EMPTY__a__b__c }

    , { /*str*/ "/a/b/c", /*sep*/ '/', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ "/a/b/c", /*sep*/ '/', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ "/a/b/c", /*sep*/ '/', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 4, /*chunks*/ CHUNKS_4_EMPTY__a__b__c }
    , { /*str*/ "/a/b/c", /*sep*/ '/', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 4, /*chunks*/ CHUNKS_4_EMPTY__a__b__c }

    , { /*str*/ ",a,,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ ",a,,b,c", /*sep*/ ',', /*keep_empty*/ 0, /*skip_escaped*/ 1, /*count*/ 3, /*chunks*/ CHUNKS_3_a__b__c }
    , { /*str*/ ",a,,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 0, /*count*/ 5, /*chunks*/ CHUNKS_5_EMPTY__a__EMPTY__b__c }
    , { /*str*/ ",a,,b,c", /*sep*/ ',', /*keep_empty*/ 1, /*skip_escaped*/ 1, /*count*/ 5, /*chunks*/ CHUNKS_5_EMPTY__a__EMPTY__b__c }

    /* Sentinel (NULL 'str' idicates end of the list) */
    , { /*str*/ NULL, /*sep*/ ' ', /*keep_empty*/ 0, /*skip_escaped*/ 0, /*count*/ 0, /*chunks*/ NULL }
};

int main(void)
{
    /* Test chunks count */
    {
        const test_case_t* test = &(TEST_CASES[0]);
        while(test->str != NULL)
        {
            const size_t chunks_count = str_split_count_chunks(test->str, strlen(test->str), test->sep, test->keep_empty, test->skip_escaped);

            if(chunks_count != test->chunks_count)
            {
                printf(
                    "Test failed (%s): str=\"%s\" sep=\'%c\' keep_empty=%i skip_escaped=%i\n"
                    "  chunks_count: %i, needed_chunks_count %i\n",

                    "str_split_count_chunks",
                    test->str, test->sep, test->keep_empty, test->skip_escaped,
                    (int)chunks_count, (int)test->chunks_count
                );
            }

            test++;
        }
    }

    /* Test chunks count & content */
    {
        const test_case_t* test = &(TEST_CASES[0]);
        while(test->str != NULL) /* Traverse until 'Sentinel' */
        {
            str_chunk_t* chunks;
            const size_t chunks_count = str_split(test->str, strlen(test->str), test->sep, test->keep_empty, test->skip_escaped, &chunks);

            /*bool*/ int success = /*true*/ 1;

            if(chunks_count == test->chunks_count)
            {
                size_t i;
                for(i = 0; i < chunks_count; ++i)
                {
                    if(chunks[i].size == strlen(test->chunks[i]))
                    {
                        if( memcmp(chunks[i].str, test->chunks[i], chunks[i].size) == 0 )
                        {
                            /* success -> noop */
                        }
                        else
                        {
                            success = /*false*/ 0;
                            break;
                        }
                    }
                    else
                    {
                        success = /*false*/ 0;
                        break;
                    }
                }
            }
            else
            {
                success = /*false*/ 0;
            }

            /* -------------------------------------------------------------- */

            if(success == /*false*/ 0)
            {
                #define MIN(a,b) (((a)<(b))?(a):(b))
                #define MAX(a,b) (((a)>(b))?(a):(b))

                const size_t max_chunks = MAX(chunks_count, test->chunks_count);
                size_t i;

                printf(
                    "Test failed (%s): str=\"%s\" sep=\'%c\' keep_empty=%i skip_escaped=%i\n"
                    "  chunks_count: %i, needed_chunks_count %i\n",

                    "str_split",
                    test->str, test->sep, test->keep_empty, test->skip_escaped,
                    (int)chunks_count, (int)test->chunks_count
                );

                for(i = 0; i < max_chunks; ++i)
                {
                    printf(
                        "%i. chunk=\"%.*s\" size=%i test_chunk=\"%s\"\n",

                        (int)(i),

                        (i < chunks_count) ? (int)chunks[i].size : /*'NONE' size*/4,
                        (i < chunks_count) ? chunks[i].str       : "NONE",

                        (i < chunks_count) ? (int)chunks[i].size : 0,

                        (i < test->chunks_count) ? test->chunks[i] : "NONE"
                    );
                }
            }

            if(chunks != NULL)
            {
                free(chunks);
            }

            test++;
        }
    }

    return 0;
}
