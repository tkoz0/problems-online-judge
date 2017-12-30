#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef uint32_t u32;
typedef int32_t i32;
#define MAX_SIZE 100

// O(N^4), iterates start and end columns, sums down resetting if it becomes 0
i32 solve1(i32 **arr, u32 N)
{
    assert(N >= 1);
    i32 max = -128; // smallest possible max sum is -127 (if all nums = -127)
    // choose a top side of the rectangle (x), then add rows going down (y)
    // reset the sum to zero if if becomes negative
    for (u32 x1 = 0; x1 != N; ++x1)
        for (u32 x2 = x1 + 1; x2 <= N; ++x2)
        {
            i32 sum = 0;
            for (i32 **row = arr; row != arr + N; ++row)
            {
                // add row
                for (i32 *col = *row + x1; col != *row + x2; ++col)
                    sum += *col;
                // reset sum as if negative values dont contribute to it
                if (sum < 0)
                {
                    sum = 0;
                    continue;
                }
                if (sum > max) max = sum;
            }
        }
    assert(max != -128);
    return max;
}

// given a starting row, an increasing ending row is iterated across
// the columns are summed into an array storing sums of each column
// column sums are iterated to find maximum, running time is O(N^3)
i32 solve2(i32 **arr, u32 N)
{
    assert(N >= 1);
    i32 max = -128;
    i32 *colsum = (i32*) malloc(N * sizeof(i32));
    for (i32 **r1 = arr; r1 != arr + N; ++r1)
    {
        // zero initialize column sums
        for (i32 *i = colsum; i != colsum + N; ++i) *i = 0;
        for (i32 **r2 = r1; r2 != arr + N; ++r2)
        {
            // sum row2 values to colums
            i32 *colpos = colsum;
            for (i32 *n = *r2; n != *r2 + N; ++n, ++colpos)
                *colpos += *n;
            // find max sum through colpos
            i32 sum = 0;
            for (colpos = colsum; colpos != colsum + N; ++colpos)
            {
                sum += *colpos;
                if (sum > max) max = sum;
                if (sum < 0) sum = 0;
            }
        }
    }
    free(colsum);
    assert(max != -128);
    return max;
}

int main(int argc, char **argv)
{
    u32 N;
    int sf = scanf("%u\n", &N);
    assert(sf);
    assert(N <= MAX_SIZE); // specification says N <= 100
    assert(N); // shouldnt be zero
    // allocate array
    i32 **arr = (i32**) malloc(N * sizeof(i32*));
    for (i32 **row = arr; row != arr + N; ++row)
        *row = (i32*) malloc(N * sizeof(i32));
    // read N^2 integers
    i32 **row = arr;
    for (; row != arr + N; ++row)
    {
        i32 *col = *row; // iterator for where to store numbers
        for (; col != *row + N; ++col)
        {
            sf = scanf("%i", col);
            assert(-127 <= *col and *col <= 127); // range specified
            assert(sf);
        }
    }
//    printf("%i\n", solve1(arr, N));
    printf("%i\n", solve2(arr, N));
    // free memory
    for (i32 **row = arr; row != arr + N; ++row)
        free(*row);
    free(arr);
    return 0;
}
