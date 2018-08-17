#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
typedef uint32_t u32;
typedef std::unordered_set<u32> vset;
std::vector<vset> adj = std::vector<vset>(30001,vset());
u32 groupsize[30001];

int main(int argc, char **argv)
{
    u32 cases;
    int scanfr = scanf("%u",&cases);
    assert(scanfr == 1);
    vset group, group2, kgroup;
    while (cases--)
    {
        u32 N, M, A, B;
        scanfr = scanf("%u%u",&N,&M);
        assert(scanfr == 2);
        assert(N and N <= 30000);
        assert(M <= 500000);
        for (auto itr = adj.begin()+1; itr <= adj.begin()+N; ++itr)
            itr->clear(); // empty sets for adjacency
        while (M--) // read adjacency pairs
        {
            scanfr = scanf("%u%u",&A,&B);
            assert(scanfr == 2);
            assert(A and A <= N);
            assert(B and B <= N);
            assert(A != B);
            adj[A].insert(B);
            adj[B].insert(A);
        }
        for (u32 i = 1; i <= N; ++i)
        {
            // groupsize[i] = 1 + (adj[i] friends)
            //     + (people who are friends with 2 of those)
            // a friend of friend of the source must be able to reach all these
            // to be added
            group.clear(); // source + dist 1
            group.insert(i);
            for (u32 j : adj[i])
            {
                group.insert(j); // within distance 1
                for (u32 k : adj[j])
                {
                    // if all in group are also in kgroup then add k
                    kgroup.clear();
                    kgroup.insert(k);
                    for (u32 z1 : adj[k])
                    {
                        kgroup.insert(z1);
                        for (u32 z2 : adj[z1]) kgroup.insert(z2);
                    }
                    for (u32 z1 : group)
                        if (kgroup.find(z1) == kgroup.end()) goto skip;
                    group.insert(k);
                    skip:;
                }
            }
            groupsize[i] = group.size();
        }
        M = 0;
        for (u32 i = 1; i <= N; ++i) M = std::max(M,groupsize[i]);
        printf("%u\n",M);
    }
    return 0;
}
