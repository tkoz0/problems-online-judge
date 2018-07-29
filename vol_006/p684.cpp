#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <utility>

typedef uint32_t u32;
typedef int64_t num_t;

struct MATRIX
{
    u32 N;
    num_t **M;
    MATRIX(u32 size)
    {
        N = size;
        M = (num_t**) malloc(N*sizeof(num_t*));
        int ret;
        for (u32 r = 0; r < N; ++r)
        {
            M[r] = (num_t*) malloc(N*sizeof(num_t));
            for (u32 c = 0; c < N; ++c)
            {
                ret = scanf("%li",&M[r][c]);
                assert(ret == 1);
            }
        }
    }
    ~MATRIX()
    {
        for (u32 r = 0; r < N; ++r) free(M[r]);
        free(M);
    }
    // compute determinant by row reduction to upper triangle and then
    // multiplying the diagonal
    num_t det()
    {
        num_t detmult = 1;
        for (u32 c = 0; c < N; ++c) // pivot column
        {
            if (M[c][c] == 0) // swap in a row without a 0 in column c
            {
                u32 sr = -1; // swap row
                for (u32 r = c+1; r < N; ++r)
                    if (M[r][c] != 0)
                    {
                        sr = r;
                        break;
                    }
                if (sr == -1) return 0; // matrix will have 0 on diagonal
                detmult *= -1; // row swap negates determinant
                std::swap(M[c],M[sr]);
            }
            num_t pivot = M[c][c];
            assert(pivot != 0);
// issue believed to be due to the repeated multiplication
// fix might be to divide out common factors from rows
// the detmult!=0 assertion failed likely due to overflow
            for (u32 r = c+1; r < N; ++r) // use pivot row to eliminate downward
            {
                if (M[r][c] == 0) continue; // row already has 0 in column c
                num_t submult = M[r][c]; // multiple of pivot row to subtract
                // multiply this row by pivot, so can subtract integer multiple
                for (u32 cc = c; cc < N; ++cc) M[r][cc] *= pivot;
                detmult *= pivot;
                for (u32 cc = c; cc < N; ++cc) M[r][cc] -= submult*M[c][cc];
                assert(M[r][c] == 0); // must elinate 0s in current column
            }
        }
        num_t determinant = 1;
        for (u32 z = 0; z < N; ++z) determinant *= M[z][z];
        assert(detmult != 0);
        assert(determinant % detmult == 0);
        return determinant/detmult;
    }
};

int main(int argc, char **argv)
{
    u32 n;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break; // 0 terminates input
        assert(n <= 30);
        MATRIX M = MATRIX(n);
        printf("%li\n",M.det());
    }
    printf("*\n");
    return 0;
}
