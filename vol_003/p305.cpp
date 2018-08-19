#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
typedef uint32_t u32;
#define LIM 14
struct node { u32 n, l, r; }; // implicit list node

u32 bestm[LIM];
node list[LIM*2];

void list_init(u32 k)
{
    list[1] = {1,2*k,2};
    list[2*k] = {2*k,2*k-1,1};
    for (u32 i = 2; i < 2*k; ++i) list[i] = {i,i-1,i+1};
}

int main(int argc, char **argv)
{
    for (u32 i = 0; i < LIM; ++i) bestm[i] = 0;
    u32 k, m, p, bad, kill, kill_L, kill_R;
    while (scanf("%u",&k) == 1)
    {
        if (!k) break;
        assert(k < LIM);
        if (bestm[k]) printf("%u\n",bestm[k]); // calculated before
        else
        {
            m = k+1;
            for (;;++m)
            {
                list_init(k);
                p = 1; // list pointer
                bad = 0; // bad people selected, get to k before good person
                while (bad < k)
                {
//                    for (u32 z = 1; z < m; ++z) p = list[p].r; // advance
                    // advance efficiently so it works well with large m
                    // list has 2k - bad people so cycle is 2k - bad
                    for (u32 z = 0; z < (m-1)%(2*k-bad); ++z) p = list[p].r;
                    kill = p;
                    if (kill <= k) break; // good person
                    bad += 1;
                    p = list[p].r;
                    kill_L = list[kill].l;
                    kill_R = p;
                    list[kill_L].r = kill_R; // delete node
                    list[kill_R].l = kill_L;
                }
                if (bad == k) break; // selected all successfully
            }
            printf("%u\n",m);
            bestm[k] = m;
        }
    }
    return 0;
}
