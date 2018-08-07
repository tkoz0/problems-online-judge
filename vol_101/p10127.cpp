#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
typedef uint32_t u32;

// these can be expensive to compute so cache values for repetitions
#include <unordered_map>
std::unordered_map<u32,u32> cache;

int main(int argc, char **argv)
{
    u32 n;
    while (scanf("%u",&n) == 1)
    {
        assert(n % 2 != 0 and n % 5 != 0);
        auto itr = cache.find(n); // check if value was computed before
        if (itr != cache.end())
        {
            printf("%u\n",itr->second);
            continue;
        }
        // not cached, must compute value
        u32 modn = 1 % n, ones = 1, add = 1;
        while (modn)
        {
            add = (add*10) % n; // modular addition
            modn = (modn+add) % n;
            ones += 1;
        }
        printf("%u\n",ones);
        cache[n] = ones;
    }
    return 0;
}
