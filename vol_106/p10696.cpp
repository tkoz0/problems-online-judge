#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_map>

typedef uint32_t u32;

std::unordered_map<u32,u32> memo;
u32 f91(u32 N)
{
    auto itr = memo.find(N);
    if (itr != memo.end()) return itr->second;
    else
    {
        u32 ret;
        if (N <= 100) ret = f91(f91(N+11));
        else ret = N-10;
        memo[N] = ret;
        return ret;
    }
}

// nonrecursively, f91(N) = 91 if N<=100, otherwise N-10

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u",&N) == 1)
    {
        if (!N) break;
        printf("f91(%u) = %u\n",N,f91(N));
    }
    return 0;
}
