#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <vector>

typedef uint32_t u32;
#define MAX_COORD 10000
#define MAX_BUILDINGS 5000

struct building
{
    u32 l, h, r;
    building(u32 l, u32 h, u32 r)
    {
        this->l = l;
        this->h = h;
        this->r = r;
    }
};

int main(int argc, char **argv)
{
    u32 L, H, R, prevL = 1; // minimum L value is 1 in problem specification
    std::vector<u32> height_map;
    // height map index 0 means between 0,1 coords, 1 means between 1,2, etc
    while (scanf("%u %u %u\n", &L, &H, &R) == 3)
    {
        assert(L < MAX_COORD and H < MAX_COORD and R < MAX_COORD);
        assert(L >= prevL); // should be sorted by left coordinate
        assert(L < R);
        prevL = L;
        // use this building to update height map
        while (height_map.size() < R)
            height_map.push_back(0);
        while (L != R) // save maximum height at each coordinate
        {
            height_map[L] = std::max(height_map[L], H);
            ++L;
        }
    }
    // solution output
    for (auto itr = height_map.begin(); itr != height_map.end(); )
    {
        u32 val = *itr; // search for unequal value (height changes)
        for (++itr;; ++itr)
        {
            if (itr == height_map.end()) goto done;
            if (*itr != val) break;
        }
        printf("%u %u ", (u32)(itr - height_map.begin()), *itr);
        continue;
        if (*itr < val) // height goes down, use previous index
            printf("%u %u ", (u32) (itr - height_map.begin() - 1), *itr);
        // height goes up, use current index
        else printf("%u %u ", (u32) (itr - height_map.begin()), *itr);
    }
    done:
    printf("%u %u\n", (u32) height_map.size(), 0); // height becomes zero at end
    return 0;
}
