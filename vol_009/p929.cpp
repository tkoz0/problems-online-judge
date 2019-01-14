#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>

#define INFINITY 0xFFFFFFFFU

struct qitem { uint32_t priority, r, c; };
struct pos_t { uint32_t r, c; };

// 1 <= N, M <= 999
uint32_t maze[1000][1000];
uint32_t dist[1000][1000];
uint32_t index_of[1000][1000]; // position in heap
std::vector<qitem> heap;
uint32_t N, M;

void heap_swap(uint32_t i, uint32_t j)
{
    auto tmp1 = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp1;
    index_of[heap[i].r][heap[i].c] = i;
    index_of[heap[j].r][heap[j].c] = j;
}

pos_t heap_pop()
{
    assert(!heap.empty());
    pos_t result = {heap[0].r,heap[0].c};
    heap[0] = heap.back();
    heap.pop_back();
    if (heap.empty()) return result;
    index_of[heap[0].r][heap[0].c] = 0;
    uint32_t i = 0; // sift down
    while (2*i+1 < heap.size()) // has left child
    {
        uint32_t s = i; // index to swap with
        if (heap[2*i+1].priority < heap[s].priority) s = 2*i+1;
        if (2*i+2 < heap.size() and
            heap[2*i+2].priority < heap[s].priority) s = 2*i+2;
        if (s == i) break; // correct position
        heap_swap(i,s);
        i = s;
    }
    return result;
}

void heap_adjust(pos_t pos, uint32_t priority)
{
    uint32_t i = index_of[pos.r][pos.c];
// printf("i=%u,newp=%u,heapp=%u\n",i,priority,heap[i].priority);
    assert(priority <= heap[i].priority); // should decrease only
    heap[i].priority = priority; // sift up
    while (i and heap[(i-1)/2].priority > heap[i].priority)
    {
        heap_swap(i,(i-1)/2);
        i = (i-1)/2;
    }
}

int main(int argc, char **argv)
{
    int r;
    uint32_t cases;
    r = scanf("%u",&cases);
    assert(r == 1);
    while (cases--)
    {
        r = scanf("%u%u",&N,&M);
        assert(r == 2);
        assert(N and N <= 999);
        assert(M and M <= 999);
        heap.clear();
        for (uint32_t i = 0; i < N; ++i)
        {
            for (uint32_t j = 0; j < M; ++j)
            {
                r = scanf("%u",&(maze[i][j]));
//                assert(r == 1);
                dist[i][j] = INFINITY;
                index_of[i][j] = heap.size();
                heap.push_back({INFINITY,i,j});
            }
        }
        dist[0][0] = maze[0][0]; // source
        heap[0].priority = maze[0][0]; // heap still valid
// printf("__maze\n");
// for(uint32_t _1=0;_1<N;++_1)
// {
//     for(uint32_t _2=0;_2<M;++_2)printf("%u ",maze[_1][_2]);
//     printf("\n");
// }
// printf("--\n");
// printf("__dist\n");
// for(uint32_t _1=0;_1<N;++_1)
// {
//     for(uint32_t _2=0;_2<M;++_2)printf("%u ",dist[_1][_2]);
//     printf("\n");
// }
// printf("--\n");
// printf("__heap\n");
// for(auto h:heap)printf("%u(%u,%u) ",h.priority,h.r,h.c);
// printf("\n--\n");
        while (!heap.empty()) // dijkstra's algorithm main loop
        {
            pos_t pos = heap_pop();
            uint32_t d = dist[pos.r][pos.c], alt;
// printf("pop = %u(%u,%u)\n",d,pos.r,pos.c);
            assert(d != INFINITY);
            if (pos.r > 0) // up
            {
                alt = d+maze[pos.r-1][pos.c];
                if (alt < dist[pos.r-1][pos.c])
                {
                    dist[pos.r-1][pos.c] = alt;
                    heap_adjust({pos.r-1,pos.c},alt);
                }
            }
            if (pos.c > 0) // left
            {
                alt = d+maze[pos.r][pos.c-1];
                if (alt < dist[pos.r][pos.c-1])
                {
                    dist[pos.r][pos.c-1] = alt;
                    heap_adjust({pos.r,pos.c-1},alt);
                }
            }
            if (pos.r < N-1) // down
            {
                alt = d+maze[pos.r+1][pos.c];
                if (alt < dist[pos.r+1][pos.c])
                {
                    dist[pos.r+1][pos.c] = alt;
                    heap_adjust({pos.r+1,pos.c},alt);
                }
            }
            if (pos.c < M-1) // right
            {
                alt = d+maze[pos.r][pos.c+1];
                if (alt < dist[pos.r][pos.c+1])
                {
                    dist[pos.r][pos.c+1] = alt;
                    heap_adjust({pos.r,pos.c+1},alt);
                }
            }
// printf("--\n");
// printf("__dist\n");
// for(uint32_t _1=0;_1<N;++_1)
// {
//     for(uint32_t _2=0;_2<M;++_2)printf("%u ",dist[_1][_2]);
//     printf("\n");
// }
// printf("--\n");
// printf("__heap\n");
// for(auto h:heap)printf("%u(%u,%u) ",h.priority,h.r,h.c);
// printf("\n--\n");
        }
        printf("%u\n",dist[N-1][M-1]);
    }
    return 0;
}
