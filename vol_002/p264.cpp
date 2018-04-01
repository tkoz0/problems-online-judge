#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef uint32_t u32;
#define NMAX 10000000

int main(int argc, char **argv)
{
    // each diagonal has the property: numerator + denominator = constant
    // find the
    // 1+2+3+...+n = n(n+1)/2 <= x
    // n^2+n <= 2x
    // suppose k^2 <= 2x (largest integer k) --> k = floor(sqrt(2x))
    // k^2+k might be >= 2x now so try k and k-1 for this largest n we need
    // if sum is odd, enumerate down-left, if even, enumerate up-right
    u32 x, term;
    while (scanf("%u", &x) == 1)
    {
        assert(x and x <= NMAX);
        u32 k = (u32) sqrt(2.0 * x);
        if (k*k + k > (x << 1)) --k; // try k-1 (k too big)
        term = x; // save original number
        x -= (k*k + k) >> 1; // x is now the residue after complete diagonals
        if (!x) // sum=k+1
        {
            if ((k+1) & 1) // odd, use end of the diagonal (bottom-left)
                printf("TERM %u IS %u/%u\n", term, k, 1);
            else printf("TERM %u IS %u/%u\n", term, 1, k);
        }
        else // sum=k+2
        {
            if ((k+2) & 1) // odd, start from top right 1/(k+1)
                printf("TERM %u IS %u/%u\n", term, x, k+2-x);
            else printf("TERM %u IS %u/%u\n", term, k+2-x, x);
        }
    }
    return 0;
}
