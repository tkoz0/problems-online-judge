#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
typedef uint32_t u32;

#define RMAX 100000
#define GMAX 100000
#define NMAX 100000

u32 rx[RMAX]; // red positions
u32 rv[RMAX]; // red velocities
u32 gx[GMAX]; // green positions
u32 gv[GMAX]; // green velocities
// segments are divided at these values, left is 0, right is 10^9
u32 segs[NMAX]; // segments
u32 R, G, N;

u32 compute()
{
    return -1;
}

int main(int argc, char **argv)
{
    u32 T;
    int r = scanf("%u",&T);
    assert(r == 1);
    assert(T <= 10);
    for (u32 test_case = 1; test_case <= T; ++test_case)
    {
        r = scanf("%u",&R);
        assert(r == 1);
        r = scanf("%u",&G);
        assert(r == 1);
        r = scanf("%u",&N);
        assert(r == 1);
        assert(R and R <= RMAX);
        assert(G and G <= GMAX);
        assert(N and N <= NMAX);
        ;
        u32 time = compute();
        if (time == -1) printf("-1\n");
        else printf("%u\n",time);
    }
    return 0;
}
