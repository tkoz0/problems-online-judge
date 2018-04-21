#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
typedef uint32_t u32;
typedef uint64_t u64;

u64 binom(u32 n, u32 m) // binomial coefficient calculator
{
    assert(n >= m);
    u64 value = 1, num = n, i;
    // this method works because n consecutive integers are divisible by n!
    for (i = 1; i <= std::min(m, n-m); ++i) value *= num--, value /= i;
    return value;
}

int main(int argc, char **argv)
{
    u32 n, m;
    while (scanf("%u %u", &n, &m) == 2)
    {
        if (!n and !m) break; // ends with 0 pair
        printf("%u things taken %u at a time is %lu exactly.\n",
                n, m, binom(n, m));
    }
}
