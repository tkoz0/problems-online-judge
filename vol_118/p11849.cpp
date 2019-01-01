#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <unordered_set>

int main(int argc, char **argv)
{
    uint32_t N, M, disc, dupes;
    std::unordered_set<uint32_t> data;
    int r;
    while (scanf("%u%u",&N,&M) == 2)
    {
        if (!N and !M) break; // end of input
        if (N > M) std::swap(N,M); // let N be smaller for less memory usage
        data.clear(); // build hash table of one persons discs
        while (N--)
        {
            r = scanf("%u",&disc);
            assert(r == 1);
            data.insert(disc);
        }
        dupes = 0; // count duplicates
        while (M--)
        {
            r = scanf("%u",&disc);
            assert(r == 1);
            if (data.find(disc) != data.end()) ++dupes;
        }
        printf("%u\n",dupes);
    }
    return 0;
}
