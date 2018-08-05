#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
typedef uint32_t u32;
#define LLIM 1000 // up to 999 length
#define NLIM 50 // up to 49 cuts
#define CASE_INFINITY (LLIM*LLIM)

int main(int argc, char **argv)
{
    u32 l, n;
    u32 cost[NLIM+1][NLIM+1]; // cost[i][j] is for cutting cuts[i] to cuts[j]
    u32 cuts[NLIM+1];
    cuts[0] = 0;
    while (scanf("%u",&l) == 1)
    {
        if (!l) break;
        scanf("%u",&n);
        assert(l < LLIM);
        assert(n < NLIM);
        for (u32 z = 1; z <= n; ++z) // read cut positions strictly increasing
        {
            scanf("%u",cuts+z);
            assert(cuts[z] > cuts[z-1]);
        }
        assert(cuts[n] < l);
        cuts[n+1] = l;
        // base cases, no cuts between so its done, no cost
        for (u32 i = 1; i <= n+1; ++i) cost[i-1][i] = 0;
        for (u32 cb = 2; cb <= n+1; ++cb) // cuts between (1 more than actual)
        {
            u32 beg = 0, end = cb;
            while (end <= n+1)
            {
                // find min cost to cut cuts[beg] to cuts[end]
                u32 min_cost = CASE_INFINITY;
                for (u32 cut = beg+1; cut < end; ++cut)
                    min_cost = std::min(min_cost,cost[beg][cut]+cost[cut][end]);
                cost[beg][end] = cuts[end] - cuts[beg] + min_cost;
                ++beg, ++end;
            }
        }
        printf("The minimum cutting is %u.\n",cost[0][n+1]);
    }
    return 0;
}
