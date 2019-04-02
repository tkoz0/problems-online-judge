#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
typedef uint32_t u32;

u32 cost[250][250]; // dp optimal cost
u32 quer[250][250]; // dp queries count
u32 f[250];

int main(int argc, char **argv)
{
    u32 n;
    while (scanf("%u",&n) == 1)
    {
        assert(n && n <= 250);
        for (u32 i = 0; i < n; ++i)
        {
            scanf("%u",f+i);
            cost[i][i] = 0; // dp base cases
            quer[i][i] = f[i];
        }
        for (u32 d = 1; d < n; ++d) // difference between range endpoints
        {
            for (u32 i = 0; i < n-d; ++i)
            {
                // cost is cost of subtrees + 1 edge per query to each
                // root does not contribute to cost
                // query count is number of queries to root plus subtree queries
                u32 j = i+d;
                // left as root
                cost[i][j] = quer[i+1][j] + cost[i+1][j];
                quer[i][j] = f[i] + quer[i+1][j];
                // right as root
                u32 cost_ = quer[i][j-1] + cost[i][j-1];
                if (cost_ < cost[i][j])
                {
                    cost[i][j] = cost_;
                    quer[i][j] = f[j] + quer[i][j-1];
                }
                // middles as root
                for (u32 m = i+1; m < j; ++m)
                {
                    cost_ = quer[i][m-1] + cost[i][m-1] +
                            quer[m+1][j] + cost[m+1][j];
                    if (cost_ < cost[i][j])
                    {
                        cost[i][j] = cost_;
                        quer[i][j] = f[m] + quer[i][m-1] + quer[m+1][j];
                    }
                }
            }
        }
        printf("%u\n",cost[0][n-1]);
    }
    return 0;
}
