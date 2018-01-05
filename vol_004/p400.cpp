#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
#define MAX_FILES 100
#define MAX_NAME 60
#define STR_LINE "------------------------------------------------------------"

int strcmp_wrapper(const void *x, const void *y)
{
    return strcmp(*((char**) x), *((char**) y));
}

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u\n", &N) == 1)
    {
        assert (N and N <= MAX_FILES); // limit specified by problem
        char **files = (char**) malloc(N * sizeof(char*));
        size_t *lengths = (size_t*) malloc(N * sizeof(size_t));
        char **fp = files; // file pointer (where to save next string)
        size_t *lp = lengths; // pointer to where to save length of next string
        for (; lp != lengths + N; ++lp, ++fp)
        {
            *fp = NULL;
            if (getline(fp, lp, stdin) == -1)
                assert(0); // should never fail if input is valid
            assert(*fp); // should point to a valid string
            *lp = strlen(*fp);
            (*fp)[*lp - 1] = '\0'; // exclude '\n' at end of string
            --(*lp);
        }
        size_t max = 0; // find longest length
        for (lp = lengths; lp != lengths + N; ++lp)
            if (*lp > max) max = *lp;
        // sort file names
        qsort(files, N, sizeof(char*), &strcmp_wrapper);
        ;//TODO printf formatted
        printf("%s\n", STR_LINE);
        // free memory
        for (fp = files; fp != files + N; ++fp)
            free(*fp);
        free(files);
        free(lengths);
    }
    return 0;
}
