#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <utility>
typedef uint32_t u32;
#define LIMIT 20000000

int main(int argc, char **argv)
{
    // odd only prime sieve
    u32 sievesize = (LIMIT+1)/2;
    bool *sieve = (bool*) calloc(sievesize,sizeof(bool));
    u32 d = 3;
    while (d*d <= LIMIT)
    {
        for (u32 i = (d*d)/2; i < sievesize; i += d)
            sieve[i] = true; // composite
        d += 2;
    }
    std::vector<std::pair<u32,u32> > twins;
    twins.push_back(std::make_pair(2,3));
    for (u32 i = 2; i < sievesize; ++i)
        if (!sieve[i-1] and !sieve[i])
            twins.push_back(std::make_pair(2*i-1,2*i+1));
    while (scanf("%u",&d) == 1)
    {
        assert(d < twins.size());
        printf("(%u, %u)\n",twins[d].first,twins[d].second);
    }
    return 0;
}
