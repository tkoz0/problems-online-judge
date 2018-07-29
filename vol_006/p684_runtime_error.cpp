#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <utility>
#include <algorithm>

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
    // functions to divide out common factors from rows and columns
    // so the integers do not get too large
    void _divide_row(u32 r, num_t *detmult, num_t *detdiv)
    {
        num_t minmag = 0;
        for (u32 c = 0; c < N; ++c) minmag = std::min(minmag,labs(M[r][c]));
        for (num_t d = 2; d <= minmag; ++d)
        {
            // if d divides all in row: divide row, update minmag/=d
            // if detmult%d==0: detmult/=d else: detdiv*=d
            for (u32 c = 0; c < N; ++c) if (M[r][c] % d != 0) goto _dr_cont;
            for (u32 c = 0; c < N; ++c) M[r][c] /= d; // divide row
            minmag /= d;
            if (*detmult % d == 0) *detmult /= d;
            else *detdiv *= d;
            _dr_cont:;
        }
    }
    void _divide_col(u32 c, num_t *detmult, num_t *detdiv)
    {
        num_t minmag = 0;
        for (u32 r = 0; r < N; ++r) minmag = std::min(minmag,labs(M[r][c]));
        for (num_t d = 2; d <= minmag; ++d)
        {
            for (u32 r = 0; r < N; ++r) if (M[r][c] % d != 0) goto _dc_cont;
            for (u32 r = 0; r < N; ++r) M[r][c] /= d;
            minmag /= d;
            if (*detmult % d == 0) *detmult /= d;
            else *detdiv *= d;
            _dc_cont:;
        }
    }
    // compute determinant by row reduction to upper triangle and then
    // multiplying the diagonal
    num_t det()
    {
        num_t detmult = 1, detdiv = 1;
        // simplify matrix of common factors
        for (u32 r = 0; r < N; ++r) _divide_row(r,&detmult,&detdiv);
        for (u32 c = 0; c < N; ++c) _divide_col(c,&detmult,&detdiv);
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
            for (u32 r = c+1; r < N; ++r) // use pivot row to eliminate downward
            {
                if (M[r][c] == 0) continue; // row already has 0 in column c
                num_t submult = M[r][c]; // multiple of pivot row to subtract
                // multiply this row by pivot, so can subtract integer multiple
                for (u32 cc = c; cc < N; ++cc) M[r][cc] *= pivot;
                detmult *= pivot;
assert(detmult != 0);
// this assertion fails, integer overflow occurs
                for (u32 cc = c; cc < N; ++cc) M[r][cc] -= submult*M[c][cc];
                assert(M[r][c] == 0); // must elinate 0s in current column
                // simplify modified rows and columns
                _divide_row(r,&detmult,&detdiv);
                for (u32 cc = c; cc < N; ++cc) _divide_col(cc,&detmult,&detdiv);
            }
        }
        num_t determinant = 1;
        for (u32 z = 0; z < N; ++z) determinant *= M[z][z];
//        assert(detmult != 0);
//        assert(determinant % detmult == 0);
if (detmult == 0) return 0;
// runtime error occurs, only possible cause is detmult==0
        return (determinant/detmult)*detdiv;
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
