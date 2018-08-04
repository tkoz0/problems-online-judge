#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
typedef uint64_t u64;

int main(int argc, char **argv)
{
    u64 X = 1;
    uint32_t printed = 0;
    while (++X, printed != 10)
    {
        // there must exist some N so sum (X+1)+(X+2)+...+N == left
        // N = (-1+sqrt(1+8X^2))/2 from quadratic solution
        u64 det = 1+8*X*X;
        u64 detroot = u64(sqrt(double(det)));
        if (detroot*detroot != det) continue; // will not be integer
        // 1+8X^2 is always odd so the root will be odd and result integer
        u64 N = (detroot-1)/2;
        assert(X*(X-1)/2 == (N*(N+1)/2 - X*(X+1)/2));
        printf("%10lu%10lu\n",X,N);
        printed += 1;
    }
    return 0;
}
