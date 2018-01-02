#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// for std::swap
#include <algorithm>

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
    // at least 2 rows, allocate temporary space to store dynamic path sums
    i32 *sums = (i32*) calloc(rows, sizeof(i32)); // start zero
    i32 *tmp = (i32*) malloc(rows * sizeof(i32)); // values set each iteration
    u32 col = cols; // start at last column, move towards start
    while (col--)
    {
        i32 ri; // for row index selection (minimum lexicographic order)
        // sums stores dynamic values for min paths starting from each of
        // the rows in the next columns, use those to work backwards 1 column
        // minimum row separately first (next 0, 1, row-1)
        ri = 0;
        if (sums[1] < sums[ri]) ri = 1;
        if (sums[rows - 1] < sums[ri]) ri = rows - 1;
        tmp[0] = sums[ri] + matr[0][col];
        matr[0][col] = ri;
        // maximum row separately next (next row-2, row-1, 0)
        ri = 0;
        if (sums[rows - 2] < sums[ri]) ri = rows - 2;
        if (sums[rows - 1] < sums[ri]) ri = rows - 1;
        tmp[rows - 1] = sums[ri] + matr[rows - 1][col];
        matr[rows - 1][col] = ri;
        // all other rows (1...row-2) (rows in the middle)
        i32 **rp = matr + 1;
        i32 *tmpp = tmp + 1; // pointer to temp array
        i32 rn = 1; // row number
        for (; rp != matr + rows - 1; ++rp, ++rn, ++tmpp)
        {
            ri = rn - 1; // initial row index selection
            if (sums[rn] < sums[ri]) ri = rn;
            if (sums[rn + 1] < sums[ri]) ri = rn + 1;
            *tmpp = sums[ri] + (*rp)[col]; // new min path sum, 1 step backward
            (*rp)[col] = ri; // store next row index
        }
        std::swap(tmp, sums); // swap roles of tmp and sums arrays
    }
    // select minimum path from sums array
    i32 r = 0; // find start row
    for (u32 i = 1; i != rows; ++i)
        if (sums[i] < sums[r]) r = i;
    printf("%i", r);
    i32 minpathval = sums[r]; // save min path value to print after path
    // follow path to print remaining values
    for (col = 0; col != cols - 1; ++col) // ignore last column
    {
        r = matr[r][col];
        printf(" %i", r);
    }
    printf("\n%i\n", minpathval);
    free(sums);
    free(tmp);
}

int main(int argc, char **argv)
{
    u32 rows, cols;
    // allocate a matrix with the maximum required space
    // each input problem will overwrite whatever space it needs
    i32 **matr = (i32**) malloc(MAX_ROW * sizeof(i32*));
    for (i32 **i = matr; i != matr + MAX_ROW; ++i)
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
