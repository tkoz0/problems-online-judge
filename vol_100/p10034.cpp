#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>
typedef uint32_t u32;
typedef float fp;

struct edge { u32 u, v; fp w; }; // connects vertices u,v and has weight w

int main(int argc, char **argv)
{
    u32 cases;
    int r = scanf("%u",&cases);
    assert(r == 1);
    u32 num_points;
    std::vector<std::pair<fp,fp> > points;
    std::vector<edge> edges;
    std::vector<std::vector<u32> > sets(points.size()); // "disjoint sets"
    std::unordered_map<u32,u32> inset; // map vertex to which set it is in
    bool first = true;
    while (scanf("%u",&num_points) == 1)
    {
        assert(num_points and num_points <= 100);
        points.clear();
        while (num_points--) // read points
        {
            fp x, y;
            r = scanf("%f %f",&x,&y);
            assert(r == 2);
            points.push_back(std::make_pair(x,y));
        }
        // considerd a complete graph of the points, weights are distance
        // goal: compute the sum of edge weights on a minimum spanning tree
        // using kruskal's algorithm with a basic "disjoint sets" structure
        edges.clear(); // make each edge, sort u,v so we dont get v,u duplicated
        for (u32 u = 0; u != points.size(); ++u)
            for (u32 v = u+1; v != points.size(); ++v)
            {
                fp dx = points[u].first - points[v].first;
                fp dy = points[u].second - points[v].second;
                fp dist = sqrt(dx*dx + dy*dy);
                edges.push_back({u,v,dist});
            }
        std::sort(edges.begin(), edges.end(), // increasing order
                [](const edge& a, const edge& b) { return a.w < b.w; });
        // "disjoint sets", each vertex in their own set
        sets = std::vector<std::vector<u32> >(points.size());
        inset.clear();
        for (u32 p = 0; p != points.size(); ++p) // make set for each point
        {
            sets[p].push_back(p);
            inset[p] = p; // initial set the vertex is in
        }
        fp length = 0.0;
        for (edge e : edges)
        {
            u32 set1 = inset[e.u], set2 = inset[e.v];
            // vertices in same set, connection would form cycle
            if (set1 == set2) continue;
            length += e.w; // part of solution, add edge weights
            // form union of inset[e.u] and inset[e.v] (move latter into former)
            for (u32 p : sets[set2]) // move from set2 to set1
            {
                sets[set1].push_back(p);
                inset[p] = set1; // new set membership
            }
            sets[set2].clear(); // set2 to be removed
        }
        if (!first) printf("\n");
        printf("%.2f\n",length);
        first = false;
    }
    return 0;
}
