#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    uint32_t n, i, j, v, source, vertex;
    int r;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break; // 0 terminates
        assert(n <= 100);
        // build graph
        std::vector<std::vector<uint32_t> > graph(n);
        for (;;)
        {
            r = scanf("%u",&i); // start vertex
            assert(r == 1);
            if (!i) break; // 0 terminates graph definition
            for (;;) // read 2nd vertices
            {
                r = scanf("%u",&j);
                assert(r == 1);
                if (!j) break; // 0 terminates end vertices
                graph[i-1].push_back(j-1); // indexing conversion from 1 to 0
            }
        }
        r = scanf("%u",&v); // number of queries
        assert(r == 1);
        while (v--)
        {
            r = scanf("%u",&source);
            assert(r == 1);
            --source; // fix indexing
            std::vector<bool> visited(n,false); // visited in DFS
            std::vector<uint32_t> stack(graph[source]);
            while (!stack.empty())
            {
                vertex = stack.back();
                stack.pop_back();
                if (!visited[vertex])
                {
                    visited[vertex] = true;
                    // append adjacent vertices to stack
                    for (auto z : graph[vertex])
                        stack.push_back(z);
                }
            }
            std::vector<uint32_t> unreachable; // find unreachable vertices
            for (i = 0; i < visited.size(); ++i)
                if (!visited[i]) unreachable.push_back(i+1);
            printf("%lu",unreachable.size()); // output results
            std::sort(unreachable.begin(),unreachable.end());
            for (auto z : unreachable)
                printf(" %u",z);
            printf("\n");
        }
    }
    return 0;
}
