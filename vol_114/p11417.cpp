#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint32_t u32;

u32 gcd(u32 x, u32 y) // euclid gcd algorithm
{
    assert(x >= y);
    while (y)
    {
        u32 t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main(int argc, char **argv)
{
    u32 G[501]; // generate table of G values
    G[0] = 0;
    G[1] = 0;
    G[2] = 1;
    for (u32 g = 3; g <= 500; ++g)
    {
        G[g] = G[g-1];
        for (u32 i = 1; i < g; ++i) G[g] += gcd(g,i);
    }
    u32 N;
    while (scanf("%u",&N) == 1)
    {
        if (!N) break;
        assert(N <= 500);
        printf("%u\n",G[N]);
    }
    return 0;
}
