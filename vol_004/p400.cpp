#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
#define MAX_FILES 100
#define MAX_NAME 60
#define LINE_WIDTH 60
#define STR_LINE "------------------------------------------------------------"

int strcmp_wrapper(const void *x, const void *y)
{
    return strcmp(*((char**) x), *((char**) y));
}

void output_fixedw(char *fname, u32 width)
{
    u32 len = strlen(fname);
    assert(len <= width);
    printf("%s", fname);
    for (; len != width; ++len) printf(" "); // pad with spaces
}

void output_files(char **files, u32 N, u32 cols, u32 max)
{
    assert(cols);
    u32 rows = N / cols;
    if (N % cols) ++rows; // extra left over so another row needed for them all
    for (u32 r = 0; r != rows; ++r)
    {
        u32 i = r;
        for (u32 c = 0; c != cols - 1; ++c, i += rows)
            if (i < N)
                output_fixedw(files[i], max + 2);
        if (i < N)
            output_fixedw(files[i], max);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    assert(LINE_WIDTH >= MAX_NAME);
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
        assert(max <= MAX_NAME);
        qsort(files, N, sizeof(char*), &strcmp_wrapper); // should print sorted
        printf("%s\n", STR_LINE);
        u32 cols = (LINE_WIDTH + 2) / ((u32) max + 2);
        assert(cols); // width will be max+2 and max for rightmost column
        // number of columns known, print files formatted now
        output_files(files, N, cols, max);
        // free memory
        for (fp = files; fp != files + N; ++fp)
            free(*fp);
        free(files);
        free(lengths);
    }
    return 0;
}
