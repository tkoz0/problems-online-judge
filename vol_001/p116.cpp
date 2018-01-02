#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef uint32_t u32;
typedef int32_t i32;

#define MAX_ROW 10
#define MAX_COL 100

void solve_backwards_dynamic(i32 **matr, u32 rows, u32 cols)
{
    assert(rows and cols); // nonzero
    if (rows == 1) // special case, only 1 possible path
    {
        // print path and sum numbers
        i32 sum = 0;
        printf("%u", 1); // first 1 (first column in path)
        for (i32 *cp = *matr + 1; cp != *matr + cols; ++cp)
        {
            sum += *cp;
            printf(" %u", 1);
        }
        printf("\n%i\n", sum);
        return;
    }
    // at least 2 rows
}

int main(int argc, char **argv)
{
    u32 rows, cols;
    // allocate a matrix with the maximum required space
    // each input problem will overwrite whatever space it needs
    i32 **matr = (i32**) malloc(MAX_ROW * sizeof(i32*));
    for (i32 **i = matr; i != matr + rows; ++i)
        *i = (i32*) malloc(MAX_COL * sizeof(i32));
    // read input problems until EOF
    while (scanf("%u %u\n", &rows, &cols) == 2)
    {
        assert(rows and rows <= MAX_ROW);
        assert(cols and cols <= MAX_COL); // both of these cant be zero
        // read row*col integers
        int sf;
        for (i32 **rp = matr; rp != matr + rows; ++rp)
            for (i32 *cp = *rp; cp != *rp + cols; ++cp)
            {
                sf = scanf("%i", cp);
                assert(sf == 1);
            }
        solve_backwards_dynamic(matr, rows, cols);
    }
    // cleanup memory
    for (i32 **rp = matr; rp != matr + MAX_ROW; ++rp)
        free(*rp);
    free(matr);
    return 0;
}
