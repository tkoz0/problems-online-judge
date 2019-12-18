#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
typedef uint32_t u32;
#define NODE_MAX 100

u32 G[NODE_MAX+1][NODE_MAX+1]; // adjacency list
u32 deg[NODE_MAX+1]; // vertex degrees
bool mark[NODE_MAX+1]; // mark unusable vertices
u32 backtrack[NODE_MAX+1][NODE_MAX+1]; // store mark indexes for backtracking
u32 stack[NODE_MAX+1]; // recursion stack containing vertices
u32 optimal[NODE_MAX+1]; // optimal independent set
u32 stack_i, optimal_len;

u32 m, n, k, u, v; // used in main, need n to be global

// recursive brute force independent set
void indset(u32 v)
{
    if (stack_i + (n-v) < optimal_len) return; // impossible to make better
    stack[stack_i++] = v; // pick for independent set
    u32 backtrack_len = 0;
    mark[v] = true; // mark nodes as unusable
    for (u32 i = 0; i < deg[v]; ++i)
        if (!mark[G[v][i]]) // save for backtrack the ones that change
        {
            mark[G[v][i]] = true;
            backtrack[v][backtrack_len++] = G[v][i];
        }
    // recurse on higher numbered vertex
    bool any_unmarked = false;
    for (u32 i = v+1; i <= n; ++i)
        if (!mark[i])
        {
            any_unmarked = true;
            indset(i);
        }
    if (!any_unmarked && stack_i > optimal_len) // unable to recurse
    {
//printf("found %u\n",stack_i);
        // here, consider the set to be maximal and save it if larger
        optimal_len = stack_i;
        for (u32 i = 0; i < stack_i; ++i)
            optimal[i] = stack[i];
    }
    // backtrack
    mark[v] = false;
    // unmark neighbors that were marked
    for (u32 i = 0; i < backtrack_len; ++i)
        mark[backtrack[v][i]] = false;
    --stack_i;
}

int main(int argc, char **argv)
{
    int r = scanf("%u",&m);
    assert(r == 1);
    while (m-- && scanf("%u%u",&n,&k) == 2)
    {
        assert(n && n <= NODE_MAX);
        memset(deg,0,sizeof(deg[0])*(n+1)); // zero degree initially
        memset(mark,0,sizeof(mark[0])*(n+1));
        while (k--) // read edges
        {
            r = scanf("%u%u",&u,&v);
            assert(r == 2);
            assert(u && u <= n && v && v <= n && u != v); // vertex nums
            G[u][deg[u]++] = v;
            G[v][deg[v]++] = u;
        }
        // pick starting vertex to try to find maximum independent set
        stack_i = 0;
        optimal_len = 0;
        for (k = 1; k <= n; ++k)
        {
//printf("start %u\n",k);
            stack[0] = k;
            indset(k);
        }
        assert(optimal_len);
        printf("%u\n",optimal_len);
        printf("%u",optimal[0]);
        for (k = 1; k < optimal_len; ++k) printf(" %u",optimal[k]);
        printf("\n");
    }
    return 0;
}
