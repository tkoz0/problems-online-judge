#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <unordered_map>

struct u32p_hash // a hash function that should be good enough for this problem
{
    size_t operator()(const std::pair<uint32_t,uint32_t>& k) const
    {
        return k.first * k.second;
    }
};

struct pq
{
    std::vector<std::pair<uint32_t,std::pair<uint32_t,uint32_t> > > _heap;
    std::unordered_map<std::pair<uint32_t,uint32_t>,uint32_t,
        u32p_hash> _index_of;
    pq(){}
    ~pq(){}
    void _swap(uint32_t a, uint32_t b)
    {
        auto tmp1 = _heap[a];
        _heap[a] = _heap[b];
        _heap[b] = tmp1;
        _index_of[_heap[a].second] = a;
        _index_of[_heap[b].second] = b;
    }
    void push(std::pair<uint32_t,uint32_t> item, uint32_t priority)
    {
        assert(_index_of.find(item) == _index_of.end());
        uint32_t i = _heap.size();
        _index_of[item] = i;
        _heap.push_back(std::make_pair(priority,item));
        while (i and _heap[(i-1)/2].first > _heap[i].first) // sift up
        {
            _swap(i,(i-1)/2);
            i = (i-1)/2;
        }
    }
    std::pair<uint32_t,uint32_t> pop()
    {
        assert(!_heap.empty());
        auto result = _heap[0];
        _heap[0] = _heap.back();
        _heap.pop_back();
        if (_heap.empty()) return result.second;
        _index_of[_heap[0].second] = 0;
        uint32_t i = 0;
        while (2*i+1 < _heap.size()) // has left, sift down loop
        {
            uint32_t si = i;
            if (_heap[2*i+1].first < _heap[si].first) si = 2*i+1;
            if (2*i+2 < _heap.size() and
                _heap[2*i+2].first < _heap[si].first) si = 2*i+2;
            if (si == i) break;
            _swap(i,si);
            i = si;
        }
        return result.second;
    }
    void decrease_priority(std::pair<uint32_t,uint32_t> item, uint32_t priority)
    {
        assert(_index_of.find(item) != _index_of.end());
        uint32_t i = _index_of[item];
//        assert(priority <= _heap[i].first);
        _heap[i].first = priority;
        while (i and _heap[(i-1)/2].first > _heap[i].first) // sift up
        {
            _swap(i,(i-1)/2);
            i = (i-1)/2;
        }
    }
    bool empty() const { return _heap.empty(); }
};

uint32_t maze[1000][1000];
uint32_t dist[1000][1000];

#define MIN(x,y) (x<y?x:y)

int main(int argc, char **argv)
{
    uint32_t count, N, M; // num cases, rows, cols
    scanf("%u",&count);
    while (count--)
    {
        scanf("%u%u",&N,&M);
        assert(N and N <= 999);
        assert(M and M <= 999);
        pq q;
        for (uint32_t i = 0; i < N; ++i)
            for (uint32_t j = 0; j < M; ++j)
            {
                scanf("%u",&maze[i][j]);
                dist[i][j] = -1; // infinity
                q.push(std::make_pair(i,j),-1);
            }
        // use dijkstra's algorithm to find distances, source is its value
        dist[0][0] = maze[0][0];
        q.decrease_priority(std::make_pair(0,0),dist[0][0]);
        while (!q.empty())
        {
for(auto z:q._heap)assert(z.first==dist[z.second.first][z.second.second]);
            std::pair<uint32_t,uint32_t> x = q.pop();
            uint32_t d2, dx = dist[x.first][x.second];
            if (x.first > 0) // up
            {
                d2 = dx+maze[x.first-1][x.second];
                if (d2 < dist[x.first-1][x.second])
                {
                    dist[x.first-1][x.second] = d2;
                    q.decrease_priority(
                        std::make_pair(x.first-1,x.second),d2);
                }
            }
            if (x.second > 0) // left
            {
                d2 = dx+maze[x.first][x.second-1];
                if (d2 < dist[x.first][x.second-1])
                {
                    dist[x.first][x.second] = d2;
                    q.decrease_priority(
                        std::make_pair(x.first,x.second-1),d2);
                }
            }
            if (x.first < N-1) // down
            {
                d2 = dx+maze[x.first+1][x.second];
                if (d2 < dist[x.first+1][x.second])
                {
                    dist[x.first+1][x.second] = d2;
                    q.decrease_priority(
                        std::make_pair(x.first+1,x.second),d2);
                }
            }
            if (x.second < M-1) // right
            {
                d2 = dx+maze[x.first][x.second+1];
                if (d2 < dist[x.first][x.second+1])
                {
                    dist[x.first][x.second+1] = d2;
                    q.decrease_priority(
                        std::make_pair(x.first,x.second+1),d2);
                }
            }
        }
        printf("%u\n",dist[N-1][M-1]); // distance to lower left corner
    }
    return 0;
}
